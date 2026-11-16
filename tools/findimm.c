// findimm —— 在 Mach-O __TEXT 中找 MOVZ/MOVK 立即数为指定 16 位值的指令
//
// 用法: findimm <macho> <hex16> [hex16 ...]
// 输出: "code_vm  指令  寄存器  移位"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint8_t *gD; static size_t gN;
static uint64_t gVm, gOff, gSz;

static uint32_t rd32(size_t o) { return *(uint32_t *)(gD + o); }
static uint64_t rd64(size_t o) { return *(uint64_t *)(gD + o); }

int main(int argc, char **argv)
{
    if (argc < 3) { fprintf(stderr, "用法: %s <macho> <hex16> ...\n", argv[0]); return 2; }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("open"); return 1; }
    fseek(f, 0, SEEK_END); gN = ftell(f); fseek(f, 0, SEEK_SET);
    gD = malloc(gN); if (fread(gD, 1, gN, f) != gN) return 1; fclose(f);
    if (rd32(0) != 0xfeedfacf) { fprintf(stderr, "不是 64 位 Mach-O\n"); return 1; }
    uint32_t ncmds = rd32(16); size_t off = 32;
    for (uint32_t i = 0; i < ncmds; i++) {
        uint32_t cmd = rd32(off), sz = rd32(off + 4);
        if (cmd == 0x19) {
            char nm[17]; memcpy(nm, gD + off + 8, 16); nm[16] = 0;
            if (!strcmp(nm, "__TEXT")) { gVm = rd64(off + 24); gOff = rd64(off + 40); gSz = rd64(off + 48); }
        }
        off += sz;
    }
    if (!gSz) { fprintf(stderr, "找不到 __TEXT\n"); return 1; }

    int nvals = argc - 2;
    uint16_t *vals = calloc(nvals, sizeof(uint16_t));
    for (int i = 0; i < nvals; i++) vals[i] = (uint16_t)strtoul(argv[i + 2], NULL, 16);

    for (size_t q = gOff; q + 4 <= gOff + gSz; q += 4) {
        uint32_t w = rd32(q);
        uint32_t op = w & 0x7F800000u;
        int isz = (op == 0x52800000u);   // MOVZ (32/64 由 sf 区分)
        int isk = (op == 0x72800000u);   // MOVK
        if (!isz && !isk) continue;
        uint16_t imm = (w >> 5) & 0xFFFF;
        for (int i = 0; i < nvals; i++) {
            if (imm == vals[i]) {
                uint32_t rd = w & 0x1F, hw = (w >> 21) & 3;
                printf("%#llx  %s%s x%u,#%#x<<%u\n",
                       (unsigned long long)(gVm + (q - gOff)),
                       isz ? "MOVZ" : "MOVK", (w & 0x80000000u) ? "64" : "32",
                       rd, imm, hw * 16);
                break;
            }
        }
    }
    return 0;
}
