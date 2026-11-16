#!/usr/bin/env python3
"""ACDB 存档容器解析（只解容器，不解压记录体）

用法:
  ./acdb.py list  <file.sav>
  ./acdb.py dump  <file.sav> <记录序号> [--hex]
  ./acdb.py raw   <file.sav> <记录序号> <输出路径>

已确认的结构（2026-11-07，ManualSave06.sav 实测）:
  文件头 0x24 字节: AC DB FE 00 | 头长 | 版本 | 记录数 | id | 固定 GUID | ...
  记录:
    +0x00  8 字节魔数 33 AA FB 57 99 FA 04 10
    +0x08  u16 03 00, u16 05 00          （版本，恒定）
    +0x0C  u16 00 04, u8 00, u8 flag     flag=0 原始 / flag=1 压缩
    +0x10  u32 A                          flag=0: 载荷长度 ; flag=1: 记录载荷长度
    +0x14  u32 B                          flag=1: 逻辑容量（0x40000 表示大对象流）
    +0x18  u32 checksum
    +0x1C  u32 类型/版本（如 0x3400068c）
    flag=0: 头部 36 字节，载荷为原始数据
    flag=1: 头部 44 字节，载荷为序列化数据（实测未压缩：内部可直接读到 TLV 字段名）
    B == 0x40000 的记录是“大对象”流，载荷同样未压缩。
"""
import struct
import sys

MAGIC = bytes.fromhex("33aafb5799fa0410")
HDR_RAW = 36
HDR_COMP = 44


def parse(path):
    data = open(path, "rb").read()
    if data[:4] != b"\xac\xdb\xfe\x00":
        raise SystemExit("不是 ACDB 容器")
    version = struct.unpack_from("<I", data, 0x08)[0]
    nrec = struct.unpack_from("<I", data, 0x0C)[0]
    save_id = data[0x10:0x14].hex()
    offs = []
    i = 0
    while True:
        j = data.find(MAGIC, i)
        if j < 0:
            break
        if data[j + 8:j + 14] == bytes.fromhex("030005000004"):
            offs.append(j)
        i = j + 1
    recs = []
    for k, o in enumerate(offs):
        end = offs[k + 1] if k + 1 < len(offs) else len(data)
        size = end - o
        flag = data[o + 15]
        a, b, chk, typ = struct.unpack_from("<IIII", data, o + 16)
        hdr = HDR_COMP if flag else HDR_RAW
        if flag == 0:
            kind = "raw"
        elif b == 0x40000:
            kind = "data-big"
        elif a + HDR_COMP == size:
            kind = "data"
        else:
            kind = "data?"
        recs.append(dict(i=k, off=o, size=size, flag=flag, a=a, b=b,
                         chk=chk, type=typ, hdr=hdr, kind=kind))
    return dict(path=path, data=data, version=version, nrec=nrec,
                save_id=save_id, recs=recs, real=len(offs))


def cmd_list(path):
    c = parse(path)
    print(f"{path}\n  版本={c['version']}  头部记录数={c['nrec']}  实际记录={len(c['recs'])}"
          f"  id={c['save_id']}  大小={len(c['data'])}")
    print(f"  {'#':>2} {'offset':>8} {'size':>6} {'flag':>4} {'A(comp)':>8} "
          f"{'B(raw)':>8} {'type':>10}  kind")
    for r in c["recs"]:
        print(f"  {r['i']:>2} {r['off']:#08x} {r['size']:>6} {r['flag']:>4} "
              f"{r['a']:>8} {r['b']:>8} {r['type']:>#10x}  {r['kind']}")
    tot = sum(r["b"] for r in c["recs"] if r["flag"])
    print(f"  压缩记录解压总量（含多块按上限估）: {tot} 字节")


def cmd_dump(path, idx, hexdump):
    c = parse(path)
    r = c["recs"][idx]
    payload = c["data"][r["off"] + r["hdr"]:r["off"] + r["size"]]
    print(f"记录 {idx}: {r}")
    print(f"载荷 {len(payload)} 字节")
    if hexdump:
        for i in range(0, len(payload), 16):
            chunk = payload[i:i + 16]
            print(f"{i:06x}  {chunk.hex(' '):<47}  "
                  + "".join(chr(b) if 32 <= b < 127 else "." for b in chunk))


def cmd_raw(path, idx, out):
    c = parse(path)
    r = c["recs"][idx]
    payload = c["data"][r["off"] + r["hdr"]:r["off"] + r["size"]]
    open(out, "wb").write(payload)
    print(f"写出 {out}: {len(payload)} 字节 ({r['kind']})")


def payload_of(c, r):
    return c["data"][r["off"] + r["hdr"]:r["off"] + r["size"]]


def cmd_strings(path, idx=None):
    """列出记录内长度 >=4 的可读 ASCII 串及载荷内偏移。"""
    import re
    c = parse(path)
    recs = [c["recs"][idx]] if idx is not None else c["recs"]
    for r in recs:
        p = payload_of(c, r)
        hits = [(m.start(), m.group().decode("latin-1"))
                for m in re.finditer(rb"[ -~]{4,}", p)]
        if not hits:
            continue
        print(f"记录 {r['i']} (type={r['type']:#x} len={len(p)}):")
        for off, s in hits:
            print(f"  +{off:#06x}  {s[:80]}")


def cmd_diff(pa, pb):
    """按记录序号对比两份存档，报告记录尺寸/类型差异与变化字节区间。"""
    a, b = parse(pa), parse(pb)
    print(f"A={pa} 记录={len(a['recs'])}  B={pb} 记录={len(b['recs'])}")
    n = max(len(a["recs"]), len(b["recs"]))
    for i in range(n):
        ra = a["recs"][i] if i < len(a["recs"]) else None
        rb = b["recs"][i] if i < len(b["recs"]) else None
        if not ra or not rb:
            print(f"记录 {i:02d}: 只在一侧存在")
            continue
        pa_ = payload_of(a, ra)
        pb_ = payload_of(b, rb)
        if pa_ == pb_:
            continue
        # 记录级差异
        tag = "尺寸不同" if len(pa_) != len(pb_) else "内容不同"
        print(f"记录 {i:02d} {tag}: type {ra['type']:#x} -> {rb['type']:#x}, "
              f"len {len(pa_)} -> {len(pb_)}")
        # 变化字节区间（按较短长度比较，最长输出 8 段）
        m = min(len(pa_), len(pb_))
        runs = []
        start = None
        for k in range(m):
            if pa_[k] != pb_[k]:
                if start is None:
                    start = k
            else:
                if start is not None:
                    runs.append((start, k))
                    start = None
        if start is not None:
            runs.append((start, m))
        for s, e in runs[:8]:
            ctx = pa_[max(0, s - 8):s]
            print(f"    +{s:#06x}..{e:#06x} ({e - s}B)  A前文={ctx!r}")
        if len(runs) > 8:
            print(f"    … 共 {len(runs)} 段变化")


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    cmd, path = sys.argv[1], sys.argv[2]
    if cmd == "list":
        cmd_list(path)
    elif cmd == "dump":
        cmd_dump(path, int(sys.argv[3]), "--hex" in sys.argv)
    elif cmd == "raw":
        cmd_raw(path, int(sys.argv[3]), sys.argv[4])
    elif cmd == "strings":
        cmd_strings(path, int(sys.argv[3]) if len(sys.argv) > 3 else None)
    elif cmd == "diff":
        cmd_diff(path, sys.argv[3])
    else:
        raise SystemExit(__doc__)


if __name__ == "__main__":
    main()
