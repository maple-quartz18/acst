#!/usr/bin/env python3
"""classhash.py —— 从 Mach-O 静态枚举类型注册点，建立 CRC32(类名) -> 类名 表

用法:
  ./classhash.py <macho> <register_fn_vm> [--min N]

原理（2026-11-07 在本作验证）:
  存档记录载荷 +3 处 4 字节 = CRC32(类名)（小端）。
  二进制里每个类型注册调用 `bl <register_fn>` 前面都有一条 ADRP+ADD 指向类名字符串，
  因此扫出全部调用点、回溯解析字符串，即可离线建表，不需要运行时 hook。

输出: `hash<TAB>name<TAB>callsite`，按 hash 升序。
"""
import sys
import zlib
import struct

SEG = 0x19


def load(path):
    d = open(path, "rb").read()
    if struct.unpack_from("<I", d, 0)[0] != 0xFEEDFACF:
        raise SystemExit("不是 64 位 Mach-O")
    ncmds = struct.unpack_from("<I", d, 16)[0]
    off = 32
    segs = []
    for _ in range(ncmds):
        cmd, sz = struct.unpack_from("<II", d, off)
        if cmd == SEG:
            name = d[off + 8:off + 24].split(b"\0")[0].decode("latin-1")
            vm, vsz = struct.unpack_from("<QQ", d, off + 24)
            foff, fsz = struct.unpack_from("<QQ", d, off + 40)
            segs.append((name, vm, vsz, foff, fsz))
        off += sz
    return d, segs


def v2o(segs, addr):
    for _n, vm, vsz, foff, fsz in segs:
        if vm <= addr < vm + min(vsz, fsz if fsz else vsz):
            o = foff + (addr - vm)
            return o
    return None


def cstr(d, segs, addr, maxlen=128):
    o = v2o(segs, addr)
    if o is None:
        return None
    end = d.find(b"\0", o)
    if end < 0 or end - o < 2 or end - o > maxlen:
        return None
    s = d[o:end]
    if any(b < 0x20 or b > 0x7E for b in s):
        return None
    return s.decode("latin-1")


def sx(v, bits):
    m = 1 << (bits - 1)
    return (v ^ m) - m


def adrp_target(pc, w):
    rd = w & 0x1F
    imm = ((w >> 5) & 0x7FFFF) << 2 | ((w >> 29) & 0x3)
    return rd, ((pc & ~0xFFF) + (sx(imm, 21) << 12))


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    path, reg = sys.argv[1], int(sys.argv[2], 0)
    d, segs = load(path)
    text = next((s for s in segs if s[0] == "__TEXT"), None)
    if not text:
        raise SystemExit("找不到 __TEXT")
    _n, vm0, vsz, foff, fsz = text

    bl_sites = []
    for q in range(foff, foff + fsz - 4, 4):
        w = struct.unpack_from("<I", d, q)[0]
        if (w & 0xFC000000) != 0x94000000:
            continue
        imm = sx(w & 0x3FFFFFF, 26)
        pc = vm0 + (q - foff)
        if pc + (imm << 2) == reg:
            bl_sites.append(pc)

    rows, miss = [], 0
    for pc in bl_sites:
        q = foff + (pc - vm0)
        name = None
        # 调用点前 16 条指令内找 ADRP+ADD（rd 相同、ADD 的 rn == ADRP 的 rd）
        for k in range(1, 17):
            a = q - 4 * k
            if a < foff:
                break
            w2 = struct.unpack_from("<I", d, a)[0]
            if (w2 & 0x7F800000) != 0x11000000:      # ADD (imm), 64-bit
                continue
            sf = (w2 >> 31) & 1
            if not sf:
                continue
            rd = w2 & 0x1F
            rn = (w2 >> 5) & 0x1F
            imm12 = (w2 >> 10) & 0xFFF
            for j in range(k + 1, min(k + 6, 17)):
                b = q - 4 * j
                if b < foff:
                    break
                w1 = struct.unpack_from("<I", d, b)[0]
                if (w1 & 0x9F000000) != 0x90000000:  # ADRP
                    continue
                rd1, tgt1 = adrp_target(vm0 + (b - foff), w1)
                if rd1 == rn and rd == rd1:
                    s = cstr(d, segs, tgt1 + imm12)
                    if s:
                        name = s
                break
            if name:
                break
        if not name:
            miss += 1
            continue
        rows.append((zlib.crc32(name.encode()) & 0xFFFFFFFF, name, pc))

    rows.sort()
    for h, n, pc in rows:
        print(f"{h:08x}\t{n}\t{pc:#x}")
    print(f"# callsites={len(bl_sites)} resolved={len(rows)} miss={miss}", file=sys.stderr)


if __name__ == "__main__":
    main()
