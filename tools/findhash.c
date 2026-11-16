// findhash —— 在文本/二进制里用「滑窗」找 CRC32(子串) == 目标值的那个名字
//
// 为什么需要它：常见做法是把二进制里的可读串整段取出来算 CRC32，
// 但字符串若紧凑存放（无 NUL 分隔），整段 CRC 与单个名字的 CRC 并不相等。
// 本工具对所有 ASCII 连续段内的每个子串（长度 3..MAXLEN）逐个算 CRC32。
//
// 用法: ./findhash <file> <target_hex> [maxlen]
// 例:   ./findhash scimitar 9e4c9ab2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint32_t crc_table[256];

static void crc_init(void) {
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t c = i;
        for (int k = 0; k < 8; k++)
            c = (c & 1) ? (0xEDB88320u ^ (c >> 1)) : (c >> 1);
        crc_table[i] = c;
    }
}

static uint32_t crc32_buf(const uint8_t *p, size_t n, uint32_t seed) {
    uint32_t c = seed;
    for (size_t i = 0; i < n; i++)
        c = crc_table[(c ^ p[i]) & 0xFF] ^ (c >> 8);
    return c;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "用法: %s <file> <target_hex> [maxlen]\n", argv[0]);
        return 2;
    }
    int maxlen = argc > 3 ? atoi(argv[3]) : 48;
    uint32_t target = (uint32_t)strtoul(argv[2], NULL, 16);

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("open"); return 1; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *d = malloc(n);
    if (!d || fread(d, 1, n, f) != (size_t)n) return 1;
    fclose(f);

    crc_init();
    long hits = 0;
    for (long i = 0; i < n; i++) {
        /* 只在可打印字符上开窗 */
        if (d[i] < 0x20 || d[i] > 0x7E) continue;
        uint32_t c = 0xFFFFFFFFu;
        for (int len = 1; len <= maxlen && i + len <= n; len++) {
            uint8_t b = d[i + len - 1];
            if (b < 0x20 || b > 0x7E) break;
            c = crc_table[(c ^ b) & 0xFF] ^ (c >> 8);
            if (len >= 3 && (c ^ 0xFFFFFFFFu) == target && c != 0) {
                printf("%#08lx  len=%d  \"%.*s\"\n", i, len, len, (char *)(d + i));
                hits++;
            }
        }
    }
    fprintf(stderr, "hits=%ld\n", hits);
    free(d);
    return 0;
}
