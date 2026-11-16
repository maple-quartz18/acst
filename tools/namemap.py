#!/usr/bin/env python3
"""namemap.py —— 用二进制字符串表反查存档里出现的 CRC32 名字

原理（2026-11-09 实测）:
  存档把属性/类名以 CRC32(name) 的 4 字节小端形式存下来，不存字符串。
  因此把待分析二进制的所有可读 ASCII 串算一遍 CRC32，就能反向翻译存档内容。

用法:
  ./namemap.py <macho> <file.sav> [--rec N] [--align] [--grep 正则]

  --rec N     只看第 N 条记录（默认全部）
  --align     只按 4 字节对齐扫描（更快，可能漏）
  --grep RE   只显示名字匹配该正则的条目

依赖: 无（标准库）
"""
import re
import struct
import sys
import zlib

MAGIC = bytes.fromhex("33aafb5799fa0410")


def build_dict(macho):
    d = open(macho, "rb").read()
    table = {}
    for m in re.finditer(rb"[ -~]{4,80}", d):
        s = m.group()
        table.setdefault(zlib.crc32(s) & 0xFFFFFFFF, s.decode("latin-1"))
    return table


def records(sav):
    data = open(sav, "rb").read()
    offs = []
    i = 0
    while True:
        j = data.find(MAGIC, i)
        if j < 0:
            break
        if data[j + 8:j + 14] == bytes.fromhex("030005000004"):
            offs.append(j)
        i = j + 1
    out = []
    for k, o in enumerate(offs):
        end = offs[k + 1] if k + 1 < len(offs) else len(data)
        flag = data[o + 15]
        hdr = 44 if flag else 36
        out.append((k, o, o + hdr, end))
    return data, out


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    macho, sav = sys.argv[1], sys.argv[2]
    only = None
    step = 1
    pat = None
    for i, a in enumerate(sys.argv):
        if a == "--rec":
            only = int(sys.argv[i + 1])
        elif a == "--align":
            step = 4
        elif a == "--grep":
            pat = re.compile(sys.argv[i + 1], re.I)

    table = build_dict(macho)
    print(f"# 名字表 {len(table)} 条", file=sys.stderr)
    data, recs = records(sav)

    for idx, start, body, end in recs:
        if only is not None and idx != only:
            continue
        pos = body
        hits = []
        while pos + 4 <= end:
            h = struct.unpack_from("<I", data, pos)[0]
            name = table.get(h)
            if name:
                hits.append((pos - body, name))
            pos += step
        if not hits:
            continue
        if pat:
            hits = [x for x in hits if pat.search(x[1])]
            if not hits:
                continue
        print(f"\n=== rec{idx} (载荷 {end - body} 字节) 命中 {len(hits)} ===")
        for off, name in hits:
            print(f"  +{off:#07x}  {name}")


if __name__ == "__main__":
    main()
