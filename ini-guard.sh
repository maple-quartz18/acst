#!/bin/zsh
# ini-guard.sh —— 监控游戏进程有没有动 ACShadows.ini
#   ./ini-guard.sh <游戏pid> [轮询秒数，默认 2]
# 每轮检查 sha256 / mtime / 文件锁标志，只在**发生变化**时记一行，
# 并明确标注是谁动的（我们没动，那就只能是游戏）。日志: acst/logs/ini-guard-<pid>.log
set -u
PID=${1:?用法: $0 <游戏pid> [轮询秒]}
INTERVAL=${2:-2}
INI="$HOME/Documents/ACShadows.ini"
LOGDIR="/Volumes/LexarSSD/Applications/acst/logs"
mkdir -p "$LOGDIR"
LOG="$LOGDIR/ini-guard-$PID.log"

sha() { shasum -a 256 "$INI" 2>/dev/null | cut -d' ' -f1; }
flags() { ls -lO "$INI" 2>/dev/null | awk '{print $5}'; }
texval() { tr -d '\r' < "$INI" 2>/dev/null | awk -F= '/^engine_textures=/{print $2}'; }

last_sha=$(sha); last_flags=$(flags)
{
  echo "=== 开始监控 pid=$PID  ${$(date +%H:%M:%S)} ==="
  echo "基线 sha=${last_sha[1,16]} flags=$last_flags engine_textures=$(texval)"
} >> "$LOG"

while kill -0 "$PID" 2>/dev/null; do
  sleep "$INTERVAL"
  cur_sha=$(sha); cur_flags=$(flags)
  if [[ "$cur_sha" != "$last_sha" ]]; then
    echo "[$(date +%H:%M:%S)] ⚠️ 文件被改写 sha=${cur_sha[1,16]} engine_textures=$(texval)" >> "$LOG"
    last_sha=$cur_sha
  fi
  if [[ "$cur_flags" != "$last_flags" ]]; then
    echo "[$(date +%H:%M:%S)] ⚠️ 锁标志变化 flags=$last_flags -> $cur_flags" >> "$LOG"
    last_flags=$cur_flags
  fi
done

echo "=== 进程 $PID 已退出 $(date +%H:%M:%S)；终态 sha=$(sha | cut -c1-16) engine_textures=$(texval) ===" >> "$LOG"
