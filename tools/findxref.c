// findxref —— 在 Mach-O 的 __TEXT 中查找 ADRP(+ADD/LDR) 对被引用字符串的代码位置
//
// 用法: findxref <macho> <字符串> [...]
// 输出: 每条命中一行 "code_vm  指令对类型  字符串"
//
// 只读；用于定位“谁在用某个字段/信号名”，再配合 acstool fn / w 反汇编。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint8_t *gData;
static size_t gSize;
static uint64_t gTextVm, gTextOff, gTextSize;
static uint64_t gDataVm, gDataOff, gDataSize;
static uint64_t gLinkOff, gLinkSize;

static uint32_t rd32(size_t o) { return *(uint32_t *)(gData + o); }
static uint64_t rd64(size_t o) { return *(uint64_t *)(gData + o); }

static int load_macho(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) { perror("open"); return 0; }
    fseek(f, 0, SEEK_END); gSize = ftell(f); fseek(f, 0, SEEK_SET);
    gData = malloc(gSize);
    if (fread(gData, 1, gSize, f) != gSize) { fclose(f); return 0; }
    fclose(f);

    if (rd32(0) != 0xfeedfacf) { fprintf(stderr, "不是 64 位 Mach-O\n"); return 0; }
    uint32_t ncmds = rd32(16);
    size_t off = 32;
    gTextVm = gTextOff = gTextSize = 0;
    gDataVm = gDataOff = gDataSize = 0;
    for (uint32_t i = 0; i < ncmds; i++) {
        uint32_t cmd = rd32(off), sz = rd32(off + 4);
        if (cmd == 0x19) {  // LC_SEGMENT_64
            char nm[17];
            memcpy(nm, gData + off + 8, 16);
            nm[16] = 0;
            uint64_t vm = rd64(off + 24), foff = rd64(off + 40), fsz = rd64(off + 48);
            fprintf(stderr, "seg %-16s vm=%#llx off=%#llx size=%#llx\n", nm,
                    (unsigned long long)vm, (unsigned long long)foff,
                    (unsigned long long)fsz);
            if (!strcmp(nm, "__TEXT")) { gTextVm = vm; gTextOff = foff; gTextSize = fsz; }
            if (!strcmp(nm, "__DATA_CONST")) { gDataVm = vm; gDataOff = foff; gDataSize = fsz; }
        }
        off += sz;
    }
    if (!gTextSize) { fprintf(stderr, "找不到 __TEXT\n"); return 0; }
    return 1;
}

static int64_t se21(uint64_t v)
{
    if (v & (1ull << 20)) return (int64_t)(v | ~((1ull << 21) - 1));
    return (int64_t)v;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "用法: %s <macho> <字符串> [...]\n", argv[0]);
        return 2;
    }
    if (!load_macho(argv[1])) return 1;

    for (int a = 2; a < argc; a++) {
        const char *needle = argv[a];
        size_t nl = strlen(needle);
        size_t found = 0;
        // 在 __cstring 区域（属于 __TEXT）里找字符串
        for (size_t p = gTextOff; p + nl + 1 < gTextOff + gTextSize; p++) {
            if (gData[p] != (uint8_t)needle[0]) continue;
            if (memcmp(gData + p, needle, nl) || gData[p + nl] != 0) continue;
            uint64_t svm = gTextVm + (p - gTextOff);
            int hits = 0;
            // 扫 __TEXT 的代码区（跳过数据段范围）；按 4 字节对齐
            for (size_t q = gTextOff; q + 16 < gTextOff + gTextSize; q += 4) {
                uint32_t w = rd32(q);
                if ((w & 0x9F000000u) != 0x90000000u) continue;  // ADRP
                uint32_t rd = w & 0x1F;
                uint64_t immlo = (w >> 29) & 3;
                uint64_t immhi = (w >> 5) & 0x7FFFF;
                int64_t imm = se21((immhi << 2) | immlo) << 12;
                uint64_t pcv = gTextVm + (q - gTextOff);
                uint64_t page = (pcv & ~0xFFFull) + (uint64_t)imm;
                for (int k = 1; k <= 4; k++) {
                    size_t q2 = q + 4 * k;
                    if (q2 + 4 > gTextOff + gTextSize) break;
                    uint32_t w2 = rd32(q2);
                    // ADD (immediate) 64-bit: 1001 0001 ...
                    if ((w2 & 0x7F800000u) == 0x11000000u && (w2 & 0x80000000u) &&
                        ((w2 >> 5) & 0x1F) == rd) {
                        uint64_t imm12 = (w2 >> 10) & 0xFFF;
                        if (page + imm12 == svm) {
                            printf("%#llx  ADRP+ADD  %s\n",
                                   (unsigned long long)(gTextVm + (q - gTextOff)), needle);
                            hits++;
                        }
                    }
                    // LDR (literal) 64-bit: 0x58000000
                    if ((w2 & 0xFF000000u) == 0x58000000u && ((w2 >> 5) & 0x1F) == rd) {
                        int64_t imm19 = (int32_t)((w2 >> 5) & 0x7FFFF);
                        if (imm19 & (1 << 18)) imm19 |= ~((1ll << 19) - 1);
                        uint64_t addr = (gTextVm + (q2 - gTextOff)) + (imm19 << 2);
                        if (addr == svm) {
                            printf("%#llx  ADRP+LDR  %s\n",
                                   (unsigned long long)(gTextVm + (q - gTextOff)), needle);
                            hits++;
                        }
                    }
                }
            }
            printf("# %s: str@%#llx hits=%d\n", needle, (unsigned long long)svm, hits);
            found++;
            if (found > 8) break;
        }
        if (!found) printf("# %s: 未找到字符串\n", needle);
    }
    return 0;
}
