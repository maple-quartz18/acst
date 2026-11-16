// acstool —— scimitar(macOS) 静态分析单文件工具
//
// 编译: clang -O2 -o acstool acstool.c
// 用法: ./acstool [--bin <路径>] <子命令> [参数]
//
// 子命令:
//   info                        段布局（__TEXT/__DATA_CONST/__DATA 的 vmaddr 与大小）
//   s     <子串> [--max N]      在 __TEXT 中找 ASCII 字符串，输出其 vmaddr（供 str 用）
//   fn    <addr>...             查地址所属函数起点与偏移
//   fn    --range <lo> <hi>     列出区间内的所有函数起点
//   str   <vmaddr>              ADRP+ADD 指向该地址的引用点（字符串/全局变量 xref）
//   bl    <vmaddr>              BL 调用该地址的调用点（直接调用者）
//   imm   <hex>                 装载 32 位常量的 movz+movk 序列位置
//   vtable <vmaddr> [count]     按 8 字节指针 dump 虚表槽位（默认 24 项）
//
// 镜像基址与段偏移全部从 Mach-O 头读取，不硬编码；ASLR 无关（均为相对基址）。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEFAULT_BIN "/Volumes/LexarSSD/Applications/Assassin's Creed Shadows.app/Contents/MacOS/scimitar"

typedef struct {
    char name[17];
    uint64_t vmaddr, vmsize, fileoff, filesize;
} Seg;

static uint8_t *gFile;
static size_t gSize;
static Seg gSeg[32];
static int gNSeg;
static uint64_t gTextVm, gTextOff, gTextSize;
static uint32_t gFsOff, gFsSize;   // LC_FUNCTION_STARTS 的 dataoff/datasize
static const char *gBin = DEFAULT_BIN;

static void die(const char *m) { perror(m); exit(1); }

static void load(void)
{
    int fd = open(gBin, O_RDONLY);
    if (fd < 0) die(gBin);
    struct stat st;
    if (fstat(fd, &st)) die("fstat");
    gSize = st.st_size;
    gFile = mmap(NULL, gSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (gFile == MAP_FAILED) die("mmap");
    close(fd);
    if (*(uint32_t *)gFile != 0xfeedfacf) {
        fprintf(stderr, "不是 64 位 Mach-O: %s\n", gBin);
        exit(1);
    }
}

static void parse(void)
{
    uint32_t ncmds = *(uint32_t *)(gFile + 16);
    size_t off = 32;
    for (uint32_t i = 0; i < ncmds; i++) {
        uint32_t cmd = *(uint32_t *)(gFile + off);
        uint32_t cmdsize = *(uint32_t *)(gFile + off + 4);
        if (cmdsize < 8) break;
        if (cmd == 0x19 && gNSeg < 32) {          // LC_SEGMENT_64
            Seg *s = &gSeg[gNSeg++];
            memcpy(s->name, gFile + off + 8, 16);
            s->name[16] = '\0';
            s->vmaddr   = *(uint64_t *)(gFile + off + 24);
            s->vmsize   = *(uint64_t *)(gFile + off + 32);
            s->fileoff  = *(uint64_t *)(gFile + off + 40);
            s->filesize = *(uint64_t *)(gFile + off + 48);
        } else if (cmd == 0x26) {                 // LC_FUNCTION_STARTS
            gFsOff  = *(uint32_t *)(gFile + off + 8);
            gFsSize = *(uint32_t *)(gFile + off + 12);
        }
        off += cmdsize;
    }
    for (int i = 0; i < gNSeg; i++) {
        if (!strcmp(gSeg[i].name, "__TEXT")) {
            gTextVm   = gSeg[i].vmaddr;
            gTextOff  = gSeg[i].fileoff;
            gTextSize = gSeg[i].filesize;
        }
    }
    if (!gTextSize) {
        fprintf(stderr, "找不到 __TEXT 段\n");
        exit(1);
    }
}

static long vm2off(uint64_t a)
{
    for (int i = 0; i < gNSeg; i++) {
        if (a >= gSeg[i].vmaddr && a < gSeg[i].vmaddr + gSeg[i].vmsize)
            return (long)(gSeg[i].fileoff + (a - gSeg[i].vmaddr));
    }
    return -1;
}

static int inText(uint64_t a) { return a >= gTextVm && a < gTextVm + gTextSize; }

// ---- 函数起点表 ----
static uint64_t *gStarts;
static size_t gNStarts;

static void build_starts(void)
{
    if (gStarts) return;            // 只构建一次（main 与 cmd_info 都会调用）
    if (!gFsSize) {
        fprintf(stderr, "该二进制没有 LC_FUNCTION_STARTS\n");
        exit(1);
    }
    size_t cap = 1 << 16;
    gStarts = malloc(cap * sizeof(uint64_t));
    if (!gStarts) die("malloc");
    const uint8_t *buf = gFile + gFsOff;
    size_t i = 0;
    uint64_t addr = gTextVm;
    while (i < gFsSize) {
        uint64_t delta = 0;
        int shift = 0;
        for (;;) {
            if (i >= gFsSize) goto done;
            uint8_t b = buf[i++];
            delta |= (uint64_t)(b & 0x7f) << shift;
            if (!(b & 0x80)) break;
            shift += 7;
        }
        if (delta == 0) break;
        addr += delta;
        if (gNStarts == cap) {                 // 动态扩容，避免截断
            cap *= 2;
            gStarts = realloc(gStarts, cap * sizeof(uint64_t));
            if (!gStarts) die("realloc");
        }
        gStarts[gNStarts++] = addr;
    }
done:
    return;
}

static uint64_t fn_of(uint64_t a)
{
    size_t lo = 0, hi = gNStarts;
    while (lo < hi) {                 // 找最后一个 <= a
        size_t mid = (lo + hi) / 2;
        if (gStarts[mid] <= a) lo = mid + 1; else hi = mid;
    }
    return lo ? gStarts[lo - 1] : 0;
}

// ---- 指令扫描 ----
static uint32_t word_at(size_t off) { return *(uint32_t *)(gFile + gTextOff + off); }

static void cmd_info(void)
{
    printf("镜像: %s\n", gBin);
    printf("文件大小: %zu 字节\n", gSize);
    for (int i = 0; i < gNSeg; i++)
        printf("  %-16s vm=0x%llx vmsize=0x%llx fileoff=0x%llx filesize=0x%llx\n",
               gSeg[i].name,
               (unsigned long long)gSeg[i].vmaddr, (unsigned long long)gSeg[i].vmsize,
               (unsigned long long)gSeg[i].fileoff, (unsigned long long)gSeg[i].filesize);
    printf("__TEXT: vm=0x%llx size=0x%llx(%llu) fileoff=0x%llx\n",
           (unsigned long long)gTextVm, (unsigned long long)gTextSize,
           (unsigned long long)gTextSize, (unsigned long long)gTextOff);
    if (gFsSize) {
        build_starts();
        printf("函数起点: %zu 个（LC_FUNCTION_STARTS）\n", gNStarts);
    }
}

static void cmd_s(const char *needle, int maxout)
{
    size_t n = strlen(needle);
    int hits = 0;
    for (size_t off = 0; off + n <= gTextSize; off++) {
        if (gFile[gTextOff + off] != (uint8_t)needle[0]) continue;
        if (memcmp(gFile + gTextOff + off, needle, n)) continue;
        printf("0x%llx  %.60s\n", (unsigned long long)(gTextVm + off),
               (char *)(gFile + gTextOff + off));
        if (++hits >= maxout) break;
    }
    printf("total %d\n", hits);
}

static void cmd_fn(int argc, char **argv)
{
    build_starts();
    printf("函数起点总数: %zu\n", gNStarts);
    if (argc >= 2 && !strcmp(argv[0], "--range")) {
        uint64_t lo = strtoull(argv[1], NULL, 16), hi = strtoull(argv[2], NULL, 16);
        for (size_t i = 0; i < gNStarts; i++)
            if (gStarts[i] >= lo && gStarts[i] <= hi)
                printf("0x%llx\n", (unsigned long long)gStarts[i]);
        return;
    }
    for (int i = 0; i < argc; i++) {
        uint64_t q = strtoull(argv[i], NULL, 16);
        uint64_t s = fn_of(q);
        if (s) printf("0x%llx -> fn 0x%llx  off +0x%llx\n",
                      (unsigned long long)q, (unsigned long long)s,
                      (unsigned long long)(q - s));
        else   printf("0x%llx -> (不在任何函数内)\n", (unsigned long long)q);
    }
}

static void cmd_str(uint64_t target)
{
    uint64_t tpage = target & ~0xFFFULL;
    uint32_t tlow = (uint32_t)(target & 0xFFF);
    int found = 0;
    for (size_t off = 0; off + 8 <= gTextSize; off += 4) {
        uint32_t w = word_at(off);
        if ((w & 0x9F000000u) != 0x90000000u) continue;       // ADRP
        int64_t imm = (int64_t)((w >> 5) & 0x7FFFF) << 2 | ((w >> 29) & 3);
        if (imm & (1 << 20)) imm -= (1 << 21);                // 21 位有符号
        uint64_t pc = gTextVm + off;
        uint64_t page = (pc & ~0xFFFULL) + (uint64_t)(imm << 12);
        if (page != tpage) continue;
        uint32_t rd = w & 31;
        uint32_t w2 = word_at(off + 4);
        uint32_t rn = (w2 >> 5) & 31, rd2 = w2 & 31;

        // 形态 1：ADRP + ADD → 取地址（字符串/全局变量地址）
        if (((w2 & 0xFF800000u) == 0x91000000u) && rn == rd && rd2 == rd) {
            uint64_t addr = page + ((w2 >> 10) & 0xFFF);
            if (addr == target) {
                printf("ADDR file=0x%zx vm=0x%llx fn=0x%llx  adrp=0x%08x add=0x%08x\n",
                       off, (unsigned long long)pc,
                       (unsigned long long)fn_of(pc), w, w2);
                found++;
            }
            continue;
        }
        // 形态 2：ADRP + LDR → 解引用该全局（读取指针/值）
        if (((w2 & 0xFFC00000u) == 0xF9400000u) && rn == rd) {   // LDR Xt,[Xn,#imm12]
            uint32_t imm12 = (w2 >> 10) & 0xFFF;
            if (imm12 * 8 == tlow) {
                printf("LOAD file=0x%zx vm=0x%llx fn=0x%llx  ldr x%u,[x%u,#0x%x]\n",
                       off, (unsigned long long)pc,
                       (unsigned long long)fn_of(pc), rd2, rn, imm12 * 8);
                found++;
            }
            continue;
        }
        // 形态 3：ADRP + LDR W（32 位读）
        if (((w2 & 0xFFC00000u) == 0xB9400000u) && rn == rd) {
            uint32_t imm12 = (w2 >> 10) & 0xFFF;
            if (imm12 * 4 == tlow) {
                printf("LOAD32 file=0x%zx vm=0x%llx fn=0x%llx  ldr w%u,[x%u,#0x%x]\n",
                       off, (unsigned long long)pc,
                       (unsigned long long)fn_of(pc), rd2, rn, imm12 * 4);
                found++;
            }
            continue;
        }
    }
    printf("total %d\n", found);
}

// 原始指令字转储，并解析 ADRP 的目标页（用于人工核对全局变量地址）
static void cmd_w(uint64_t vm, int count)
{
    long o = vm2off(vm);
    if (o < 0 || !inText(vm)) {
        printf("0x%llx 不在 __TEXT 内\n", (unsigned long long)vm);
        return;
    }
    for (int i = 0; i < count; i++) {
        uint32_t w = *(uint32_t *)(gFile + o + i * 4);
        uint64_t pc = vm + i * 4;
        char extra[96] = "";
        if ((w & 0x9F000000u) == 0x90000000u) {          // ADRP
            int64_t imm = (int64_t)((w >> 5) & 0x7FFFF) << 2 | ((w >> 29) & 3);
            if (imm & (1 << 20)) imm -= (1 << 21);
            uint64_t page = (pc & ~0xFFFULL) + (uint64_t)(imm << 12);
            uint32_t w2 = *(uint32_t *)(gFile + o + i * 4 + 4);
            uint32_t imm12 = (w2 >> 10) & 0xFFF;
            if ((w2 & 0xFF800000u) == 0x91000000u) {
                snprintf(extra, sizeof extra, "  -> x%u = 0x%llx (adrp+add 0x%llx)",
                         w & 31, (unsigned long long)(page + imm12), (unsigned long long)page);
            } else if ((w2 & 0xFFC00000u) == 0xF9400000u) {
                snprintf(extra, sizeof extra, "  -> ldr from 0x%llx",
                         (unsigned long long)(page + imm12 * 8));
            } else if ((w2 & 0xFFC00000u) == 0xB9400000u) {
                snprintf(extra, sizeof extra, "  -> ldr32 from 0x%llx",
                         (unsigned long long)(page + imm12 * 4));
            } else {
                snprintf(extra, sizeof extra, "  -> page 0x%llx", (unsigned long long)page);
            }
        } else if ((w & 0xFC000000u) == 0x94000000u) {   // BL
            int64_t imm = (int64_t)(w & 0x03FFFFFF);
            if (imm & (1 << 25)) imm -= (1 << 26);
            snprintf(extra, sizeof extra, "  -> bl 0x%llx", (unsigned long long)(pc + (imm << 2)));
        }
        printf("0x%llx  %08x%s\n", (unsigned long long)pc, w, extra);
    }
}

// 反查动作注册表：对所有 BL <registry> 的调用点，向前扫描所属函数，
// 提取 ADRP+ADD 指向的可打印字符串与 movz+movk 组成的 32 位 id。
static const char *str_at(uint64_t vm, char *buf, size_t cap)
{
    long o = vm2off(vm);
    if (o < 0) return NULL;
    size_t n = 0;
    while (n + 1 < cap) {
        uint8_t c = gFile[o + n];
        if (c < 0x20 || c > 0x7e) break;
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    return n >= 3 ? buf : NULL;
}

static void cmd_actions(uint64_t registry)
{
    char s[128];
    int found = 0;
    for (size_t off = 0; off + 4 <= gTextSize; off += 4) {
        uint32_t w = word_at(off);
        if ((w & 0xFC000000u) != 0x94000000u) continue;      // BL
        int64_t imm = (int64_t)(w & 0x03FFFFFF);
        if (imm & (1 << 25)) imm -= (1 << 26);
        uint64_t pc = gTextVm + off;
        if (pc + (uint64_t)(imm << 2) != registry) continue;

        uint64_t fstart = fn_of(pc);
        uint64_t bestStr = 0, bestId = 0;
        for (uint64_t a = fstart; a + 8 <= pc; a += 4) {
            uint32_t x = *(uint32_t *)(gFile + vm2off(a));
            uint32_t x2 = *(uint32_t *)(gFile + vm2off(a) + 4);
            // ADRP + ADD → 字符串地址
            if ((x & 0x9F000000u) == 0x90000000u &&
                ((x2 & 0xFF800000u) == 0x91000000u)) {
                int64_t im = (int64_t)((x >> 5) & 0x7FFFF) << 2 | ((x >> 29) & 3);
                if (im & (1 << 20)) im -= (1 << 21);
                uint64_t page = (a & ~0xFFFULL) + (uint64_t)(im << 12);
                uint64_t t = page + ((x2 >> 10) & 0xFFF);
                if (inText(t) && str_at(t, s, sizeof s)) bestStr = t;
            }
            // movz w,#imm16 + movk w,#imm16,lsl16
            if ((x & 0xFFE00000u) == 0x52800000u &&
                (x2 & 0xFFE00000u) == 0x72A00000u &&
                (x & 31) == (x2 & 31)) {
                uint32_t lo = (x >> 5) & 0xFFFF, hi = (x2 >> 5) & 0xFFFF;
                bestId = (hi << 16) | lo;
            }
        }
        char nm[128] = "";
        if (bestStr) str_at(bestStr, nm, sizeof nm);
        printf("0x%08llx  %-40s  (id site 0x%llx)\n", (unsigned long long)bestId, nm,
               (unsigned long long)pc);
        found++;
    }
    printf("total %d\n", found);
}

static void cmd_bl(uint64_t target)
{
    int found = 0;
    for (size_t off = 0; off + 4 <= gTextSize; off += 4) {
        uint32_t w = word_at(off);
        if ((w & 0xFC000000u) != 0x94000000u) continue;       // BL
        int64_t imm = (int64_t)(w & 0x03FFFFFF);
        if (imm & (1 << 25)) imm -= (1 << 26);
        uint64_t pc = gTextVm + off;
        if (pc + (uint64_t)(imm << 2) == target)
            printf("BL vm=0x%llx fn=0x%llx\n", (unsigned long long)pc,
                   (unsigned long long)fn_of(pc)), found++;
    }
    printf("total %d\n", found);
}

static void cmd_imm(uint32_t value)
{
    uint32_t lo = value & 0xFFFF, hi = (value >> 16) & 0xFFFF;
    uint32_t movz = 0x52800000u | (lo << 5);                  // movz wN,#lo
    uint32_t movk = 0x72A00000u | (hi << 5);                  // movk wN,#hi,lsl 16
    int found = 0;
    for (size_t off = 0; off + 8 <= gTextSize; off += 4) {
        uint32_t w = word_at(off);
        if ((w & 0xFFFFFFE0u) != (movz & 0xFFFFFFE0u)) continue;
        uint32_t w2 = word_at(off + 4);
        if ((w2 & 0xFFFFFFE0u) != (movk & 0xFFFFFFE0u)) continue;
        if ((w & 31) != (w2 & 31)) continue;
        printf("IMM vm=0x%llx fn=0x%llx reg=w%u\n",
               (unsigned long long)(gTextVm + off),
               (unsigned long long)fn_of(gTextVm + off), w & 31);
        found++;
    }
    printf("total %d\n", found);
}

static void cmd_vtable(uint64_t vm, int count)
{
    long o = vm2off(vm);
    if (o < 0) {
        printf("0x%llx 不在任何段内\n", (unsigned long long)vm);
        return;
    }
    printf("vtable @0x%llx fileoff=0x%lx\n", (unsigned long long)vm, o);
    for (int i = 0; i < count; i++) {
        uint64_t w = *(uint64_t *)(gFile + o + i * 8);
        const char *tag = "";
        if (inText(w)) tag = "TEXT";
        else if (w == 0) tag = "-";
        printf("  [+0x%02x/%2d] 0x%016llx %s", i * 8, i, (unsigned long long)w, tag);
        if (inText(w)) printf("  fn=0x%llx", (unsigned long long)fn_of(w));
        printf("\n");
    }
}

static int usage(void)
{
    fprintf(stderr,
        "用法: acstool [--bin <路径>] <子命令> [参数]\n"
        "  info\n"
        "  s     <子串> [--max N]\n"
        "  fn    <addr>... | --range <lo> <hi>\n"
        "  str   <vmaddr>\n"
        "  bl    <vmaddr>\n"
        "  imm   <hex>\n"
        "  vtable <vmaddr> [count]\n");
    return 2;
}

int main(int argc, char **argv)
{
    int i = 1;
    if (i < argc && !strcmp(argv[i], "--bin")) {
        if (i + 1 >= argc) return usage();
        gBin = argv[i + 1];
        i += 2;
    }
    if (i >= argc) return usage();
    const char *cmd = argv[i++];
    int n = argc - i;
    char **rest = argv + i;

    load();
    parse();
    if (gFsSize) build_starts();     // 各子命令都要用 fn_of 做归属标注

    if (!strcmp(cmd, "info")) {
        cmd_info();
    } else if (!strcmp(cmd, "s")) {
        if (n < 1) return usage();
        int maxout = 200;
        for (int k = 1; k < n; k++)
            if (!strcmp(rest[k], "--max") && k + 1 < n) maxout = atoi(rest[k + 1]);
        cmd_s(rest[0], maxout);
    } else if (!strcmp(cmd, "fn")) {
        if (n < 1) return usage();
        cmd_fn(n, rest);
    } else if (!strcmp(cmd, "str")) {
        if (n < 1) return usage();
        cmd_str(strtoull(rest[0], NULL, 16));
    } else if (!strcmp(cmd, "bl")) {
        if (n < 1) return usage();
        cmd_bl(strtoull(rest[0], NULL, 16));
    } else if (!strcmp(cmd, "imm")) {
        if (n < 1) return usage();
        cmd_imm((uint32_t)strtoul(rest[0], NULL, 16));
    } else if (!strcmp(cmd, "actions")) {
        if (n < 1) return usage();
        cmd_actions(strtoull(rest[0], NULL, 16));
    } else if (!strcmp(cmd, "w")) {
        if (n < 1) return usage();
        cmd_w(strtoull(rest[0], NULL, 16), n >= 2 ? atoi(rest[1]) : 16);
    } else if (!strcmp(cmd, "vtable")) {
        if (n < 1) return usage();
        cmd_vtable(strtoull(rest[0], NULL, 16), n >= 2 ? atoi(rest[1]) : 24);
    } else {
        return usage();
    }
    return 0;
}
