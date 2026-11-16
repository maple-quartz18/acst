#!/bin/zsh
# 把 ini-presets/ 下的快照拼成「键 × 预设」矩阵。
# 用法: ./ini-matrix.sh [目录]
set -u

OUT="${1:-/Volumes/LexarSSD/Applications/acst/ini-presets}"
[ -d "$OUT" ] || { echo "目录不存在: $OUT"; exit 1; }

python3 - "$OUT" <<'EOF'
import sys, os, glob, re

out = sys.argv[1]
# 实测有 6 档（官方文章只写 5 档，以实测为准）；不同版本/语言的 Profile 名可能不同，
# 这里按从低到高排队，未列出的名字排在最后按字母序。
order = ["lowest", "low", "medium", "high", "veryhigh", "very_high", "ultra",
         "extreme", "highest", "macos_custom"]

def profile_of(path):
    for line in open(path, encoding="utf-8", errors="ignore"):
        m = re.match(r"\s*Profile\s*=\s*(\S+)", line)
        if m:
            return m.group(1)
    return "unknown"

def read_kv(path):
    d = {}
    for line in open(path, encoding="utf-8", errors="ignore"):
        line = line.strip()
        if not line or line.startswith(("[", "#", ";")):
            continue
        if "=" in line:
            k, v = line.split("=", 1)
            d[k.strip()] = v.strip()
    return d

files = sorted(glob.glob(os.path.join(out, "*.ini")))
if not files:
    print("没有快照")
    sys.exit(0)

snaps = [(profile_of(f), f, read_kv(f)) for f in files]
def rank(p):
    return order.index(p) if p in order else len(order)
snaps.sort(key=lambda s: (rank(s[0]), s[1]))
cols = [(p, os.path.basename(f)) for p, f, _ in snaps]
keys = sorted({k for _, _, kv in snaps for k in kv})

print(f"快照 {len(snaps)} 份：" + "  ".join(f"{p}({n})" for p, n in cols))
print()
w = max(len(k) for k in keys) + 2
print("键".ljust(w) + "".join(p.ljust(12) for p, _ in cols))
print("-" * (w + 12 * len(cols)))
for k in keys:
    vals = [kv.get(k, "—") for _, _, kv in snaps]
    # 全部相同就不标，有差异才在行尾提醒
    mark = "" if len({v for v in vals if v != "—"}) <= 1 else "  *"
    print(k.ljust(w) + "".join(str(v).ljust(12) for v in vals) + mark)
print()
print("* = 该键在不同预设间取值不同；最大值即该键的上限。")
EOF
