#!/usr/bin/env python3
"""trydecomp.py —— 试探存档"大对象"记录的压缩算法

背景（2026-11-09）:
  ACDB 记录头里 B == 0x40000 的记录是"大对象流"，
  载荷熵 ~7.9、gzip 比 ~1.0，说明已压缩；载荷首字节 0x40 很像 LZ4 block 的 token。

用法:
  ./trydecomp.py <payload.bin> [期望输出大小]

会依次尝试: LZ4 block / raw deflate / zlib / lzma / bz2，报告哪个成功。
"""
import sys
import zlib


def lz4_block(src, limit):
    """最小 LZ4 block 解码器。返回 bytes 或 None。"""
    out = bytearray()
    i = 0
    n = len(src)
    while i < n:
        token = src[i]
        i += 1
        lit = token >> 4
        if lit == 15:
            while True:
                if i >= n:
                    return None
                b = src[i]
                i += 1
                lit += b
                if b != 255:
                    break
        if i + lit > n:
            return None
        out += src[i:i + lit]
        i += lit
        if i >= n:
            break                      # 最后一个序列只有字面量
        if i + 2 > n:
            return None
        off = src[i] | (src[i + 1] << 8)
        i += 2
        if off == 0 or off > len(out):
            return None
        mlen = token & 0x0F
        if mlen == 15:
            while True:
                if i >= n:
                    return None
                b = src[i]
                i += 1
                mlen += b
                if b != 255:
                    break
        mlen += 4
        start = len(out) - off
        for k in range(mlen):
            out.append(out[start + k])
        if len(out) > limit:
            return None
    return bytes(out)


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    src = open(sys.argv[1], "rb").read()
    limit = int(sys.argv[2]) if len(sys.argv) > 2 else 0x40000
    print(f"输入 {len(src)} 字节，期望输出 {limit}")

    r = lz4_block(src, limit)
    if r:
        print(f"  LZ4 block  → 成功，输出 {len(r)} 字节")
        head = r[:64]
        print(f"    前64B: {head.hex(' ')}")
        printable = bytes(b if 32 <= b < 127 else 46 for b in head).decode()
        print(f"    ASCII: {printable}")
        open(sys.argv[1] + ".lz4.out", "wb").write(r)
        return
    print("  LZ4 block  → 失败")

    for name, fn in (
        ("raw deflate", lambda s: zlib.decompressobj(-15).decompress(s)),
        ("zlib", lambda s: zlib.decompress(s)),
    ):
        try:
            out = fn(src)
            print(f"  {name} → 成功，输出 {len(out)} 字节")
            return
        except Exception as e:
            print(f"  {name} → 失败 ({type(e).__name__})")

    import lzma
    try:
        out = lzma.decompress(src)
        print(f"  lzma → 成功，输出 {len(out)} 字节")
    except Exception:
        print("  lzma → 失败")


if __name__ == "__main__":
    main()
