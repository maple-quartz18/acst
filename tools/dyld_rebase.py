#!/usr/bin/env python3
"""dyld_rebase.py —— 独立解析 LC_DYLD_INFO_ONLY 的 rebase 表

为什么需要它：Ghidra 的 RebaseTable 对单条 opcode 的 count 有 100_000 硬上限
（private static final，无系统属性开关）。scimitar 有一条 opcode 要求 108193 次
rebase，直接抛异常 → **整个 LC_DYLD_INFO_ONLY 被跳过**（rebase/bind/lazy bind 全丢），
不是只丢最后 8193 条。本脚本绕开这个上限，把完整 rebase 地址表算出来。

用法:
  ./dyld_rebase.py <macho> [--by-segment] [--ghidra-script out.java]

输出: 每个 rebase 位置的 vmaddr（默认只给统计；--list 给全量）。
"""
import struct
import sys

LC_SEGMENT_64 = 0x19
LC_DYLD_INFO_ONLY = 0x80000022
LC_DYLD_INFO = 0x22

OP_SET_TYPE_IMM = 0x10
OP_SET_SEGMENT_AND_OFFSET_ULEB = 0x20
OP_ADD_ADDR_ULEB = 0x30
OP_ADD_ADDR_IMM_SCALED = 0x40
OP_DO_REBASE_IMM_TIMES = 0x50
OP_DO_REBASE_ULEB_TIMES = 0x60
OP_DO_REBASE_ADD_ADDR_ULEB = 0x70
OP_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB = 0x80
OP_DONE = 0x00


def uleb(buf, pos):
    result = 0
    shift = 0
    while True:
        b = buf[pos]
        pos += 1
        result |= (b & 0x7F) << shift
        if not (b & 0x80):
            return result, pos
        shift += 7


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    path = sys.argv[1]
    d = open(path, "rb").read()
    if struct.unpack_from("<I", d, 0)[0] != 0xFEEDFACF:
        raise SystemExit("不是 64 位 Mach-O")

    ncmds = struct.unpack_from("<I", d, 16)[0]
    off = 32
    segs = []          # (index, name, vmaddr, filesize)
    rebase_off = rebase_size = None
    for _ in range(ncmds):
        cmd, sz = struct.unpack_from("<II", d, off)
        if cmd == LC_SEGMENT_64:
            name = d[off + 8:off + 24].split(b"\0")[0].decode("latin-1")
            vm = struct.unpack_from("<Q", d, off + 24)[0]
            fsz = struct.unpack_from("<Q", d, off + 48)[0]
            segs.append((len(segs), name, vm, fsz))
        elif cmd in (LC_DYLD_INFO_ONLY, LC_DYLD_INFO):
            rebase_off, rebase_size = struct.unpack_from("<II", d, off + 8)
        off += sz

    if rebase_off is None or rebase_size == 0:
        raise SystemExit("没有 LC_DYLD_INFO rebase 表")
    buf = d[rebase_off:rebase_off + rebase_size]
    ptr = 8
    seg_index = 0
    seg_offset = 0
    addrs = []
    i = 0
    over_limit = 0
    while i < len(buf):
        b = buf[i]
        i += 1
        op = b & 0xF0
        imm = b & 0x0F
        if op == OP_DONE:
            break
        elif op == OP_SET_TYPE_IMM:
            pass
        elif op == OP_SET_SEGMENT_AND_OFFSET_ULEB:
            seg_index = imm
            seg_offset, i = uleb(buf, i)
        elif op == OP_ADD_ADDR_ULEB:
            v, i = uleb(buf, i)
            seg_offset += v
        elif op == OP_ADD_ADDR_IMM_SCALED:
            seg_offset += imm * ptr
        elif op == OP_DO_REBASE_IMM_TIMES:
            for _ in range(imm):
                addrs.append((seg_index, seg_offset))
                seg_offset += ptr
        elif op == OP_DO_REBASE_ULEB_TIMES:
            cnt, i = uleb(buf, i)
            if cnt > 100_000:
                over_limit += 1
            for _ in range(cnt):
                addrs.append((seg_index, seg_offset))
                seg_offset += ptr
        elif op == OP_DO_REBASE_ADD_ADDR_ULEB:
            addrs.append((seg_index, seg_offset))
            v, i = uleb(buf, i)
            seg_offset += v + ptr
        elif op == OP_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB:
            cnt, i = uleb(buf, i)
            skip, i = uleb(buf, i)
            if cnt > 100_000:
                over_limit += 1
            for _ in range(cnt):
                addrs.append((seg_index, seg_offset))
                seg_offset += skip + ptr
        else:
            raise SystemExit(f"未知 rebase opcode {op:#x} @ {i-1}")

    by_seg = {}
    for si, so in addrs:
        by_seg[si] = by_seg.get(si, 0) + 1
    print(f"rebase 条目: {len(addrs)}  超过单条 100k 上限的 opcode: {over_limit}")
    print(f"{'seg':>3} {'name':<16} {'vmaddr':>14} {'count':>8}")
    for si, name, vm, _fsz in segs:
        c = by_seg.get(si, 0)
        if c:
            print(f"{si:>3} {name:<16} {vm:#14x} {c:>8}")

    if "--list" in sys.argv:
        for si, so in addrs:
            vm = segs[si][2] if si < len(segs) else 0
            print(f"{vm + so:#x}")


if __name__ == "__main__":
    main()
