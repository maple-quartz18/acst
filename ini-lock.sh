#!/bin/zsh
# ini-lock.sh —— 锁住 ACShadows.ini，防止游戏进程退出时把它改回去
#   ./ini-lock.sh on    上锁（chflags uchg，连属主也改不动，除非先解锁）
#   ./ini-lock.sh off   解锁
#   ./ini-lock.sh status
# 用途：固定某一组画质值做 A/B，避免游戏在退出/切档时覆盖掉被测配置。
set -u
INI="$HOME/Documents/ACShadows.ini"

case "${1:-status}" in
  on)
    chflags uchg "$INI" || { echo "上锁失败"; exit 1 }
    echo "已上锁: $(ls -lO "$INI" | awk '{print $5, $6}')"
    ;;
  off)
    chflags nouchg "$INI" || { echo "解锁失败"; exit 1 }
    echo "已解锁"
    ;;
  status)
    flags=$(ls -lO "$INI" | awk '{print $5}')
    if [[ "$flags" == *uchg* ]]; then echo "当前: 已锁 (uchg)"
    else echo "当前: 未锁 ($flags)"; fi
    ;;
  *)
    echo "用法: $0 on|off|status"; exit 2 ;;
esac
