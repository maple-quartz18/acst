#!/bin/zsh
# 盯住 ACShadows.ini 的**画质段**：只有 [Scalability_Custom] 或其 Profile 变化时才存快照。
# 窗口位置、FOV、音量等无关字段变了不触发——否则拖一下窗口就多一份噪声快照。
# 快照名取文件内 Profile 值；同名但内容不同则追加时间戳。
# 用法: ./ini-watch.sh [最大快照数] [超时秒]
set -u

INI="$HOME/Documents/ACShadows.ini"
OUT="/Volumes/LexarSSD/Applications/acst/ini-presets"
MAX=${1:-14}
TIMEOUT=${2:-3600}

mkdir -p "$OUT"
echo "监视: $INI（只看 [Scalability_Custom] + Profile）"
echo "输出: $OUT   上限: $MAX 份 / $TIMEOUT 秒"

# 画质指纹：Profile 行 + Scalability_Custom 段的全部键值
quality_fp() {
    awk '
        /^\[Scalability_Custom\]/ {inblock=1; print; next}
        /^\[/ {inblock=0}
        /^Profile=/ {print}
        inblock {print}
    ' "$INI" 2>/dev/null | shasum -a 256 | cut -d' ' -f1
}

profile_of() {
    awk -F= '/^Profile=/{gsub(/[ \r]/,"",$2); print $2}' "$INI" 2>/dev/null
}

last=""
count=0
start=$(date +%s)

snap() {
    local fp profile dst
    fp=$(quality_fp)
    [ -z "$fp" ] && return 1
    [ "$fp" = "$last" ] && return 1
    last="$fp"
    profile=$(profile_of); [ -z "$profile" ] && profile="unknown"
    # 用「画质指纹前 8 位」命名：同一套画质只会存在一份快照，
    # 窗口位置/FOV 之类的无关字段变化不会再多存（这类变化指纹里不含）。
    dst="$OUT/${profile}-${fp[1,8]}.ini"
    if [ -f "$dst" ]; then
        printf '[%s] 画质指纹 %s 已存在，跳过\n' "$(date +%H:%M:%S)" "${fp[1,8]}"
        return 0
    fi
    cp -p "$INI" "$dst"
    count=$((count + 1))
    printf '[%s] 快照 #%d  profile=%-16s -> %s\n' "$(date +%H:%M:%S)" "$count" "$profile" "$(basename "$dst")"
}

snap   # 基线

while [ "$count" -lt "$MAX" ]; do
    if [ $(($(date +%s) - start)) -ge "$TIMEOUT" ]; then
        echo "超时退出（$TIMEOUT 秒，已收 $count 份）"
        break
    fi
    snap
    sleep 3
done

echo "共 $count 份快照："
ls -1 "$OUT" | tail -15
