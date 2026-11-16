# Mac 游戏逆向 / 效能研究 Playbook

> 来源：Assassin's Creed Shadows（macOS）存档逆向 + 显存优化的完整实践（2026-10/11）。
> 目的：换一款 Mac 游戏时，按同一套流程与判据重跑，避免重犯已知错误。
> 配套：`acst/acst.md`（本作结论）、`acshadows-ios/agents.md`（注入层交接）、
> `acst/saveparse/acdb.py`、`acst/tools/*`（可复用工具源码）。

---

## 0. 四条总原则

1. **证据分级：静态证据 > 运行时实测 > 文档/社区推断。** 每条结论标注属于哪一级。
   社区文档只能是线索，不能当依据（本作 Ubisoft 官方写"5 档"，实测是 7 档）。
2. **结论必须带反证方式。** 写"X = Y"时同时写"如果 X≠Y，应该观察到什么"。
3. **任何 A/B 只允许一个变量。** 测量类实验还要额外固定位置与时长（见第 6 节）。
4. **静态走不通就换运行时，别硬啃。** 判据见 3.C7。

---

## 1. 阶段 A：摸底（先做，一小时以内）

| 查什么 | 怎么查 | 目的 |
| --- | --- | --- |
| bundle 结构 | `ls -R "*.app/Contents"`、`du -sh` | 主可执行文件、dylib 拆分、资源体积 |
| 可执行文件形态 | `file`、`otool -l`、`lipo -info` | 架构、`platform=1`(macOS)、min OS |
| 签名/硬化 | `codesign -dv --verbose=4` | 是否 hardened runtime、能否注入 |
| 沙盒 | `ls ~/Library/Containers/<bundleid>` | 决定数据目录在容器内还是 `~/Library/Autosave Information` |
| 配置/存档 | 游戏跑一次，按 mtime 找最近写入 | 别凭文档猜路径 |
| 引擎 | `strings` 找 `UnityEngine`/`Unreal`/自研特征 | 决定后续工具链 |
| 压缩/打包 | 大文件扩展名（`.forge`/`.pak`/`.bundle`） | 判断能否解包，值不值得解 |

**关键判断**：先确认"数据是明文还是打包"。打包且是商业压缩（如 Oodle2）时，
先算清收益再决定要不要碰（本作结论：解出来也推不出管线描述符，收益为零 → 不做）。

---

## 2. 阶段 B：静态工具箱（一次准备，跨游戏复用）

本项目的四个 C 工具都是"读 Mach-O 段表 + 扫指令"，不依赖具体游戏，换游戏只需换常量：

| 工具 | 用途 | 换游戏要改什么 |
| --- | --- | --- |
| `tools/acstool.c` | 通用：段表、反汇编窗口、`bl` 目标、立即数、动作名 | 无（自动读段表） |
| `tools/findxref.c` | 找引用某地址的 `ADRP+ADD` / `ADRP+LDR` site | 无，传目标地址 |
| `tools/findimm.c` | 扫 `MOVZ/MOVK` 立即数，定位"用到某个魔数"的函数 | 传 4 段 16 位立即数 |
| `tools/findcall.c` | 枚举所有 `bl <target>` 调用点 | 传目标函数地址 |

编译：`clang -O2 -o tools/<name> tools/<name>.c`。

**最通用的一招是 `findimm`**：任何格式都有一个"文件魔数"。
把魔数拆成 4 个 16 位半字去扫 `MOVZ/MOVK`，能直接落到读写该格式的函数里。
本作魔数 `33 AA FB 57 99 FA 04 10` → 立即数 `aa33 / 57fb / 99fa / 1004`，
命中三簇函数，一眼看出"哪里在写存档"。

**已知约束**：
- 现代 macOS 二进制用**链式指针（chained fixups）**，绝对指针在文件里不是绝对地址 →
  直接搜 8 字节指针会 0 命中。必须走 `ADRP+ADD`/`ADRP+LDR` 或立即数。
- `dladdr` 的"最近镜像"归属不可信（pc 略微越界会错归），按 `_dyld_get_image_name` 扫镜像名。
- Apple 版 `llvm-objdump --start-address/--stop-address` 会被忽略；用 `otool -tv` + 地址锚定。
  `otool` 输出地址是 16 位十六进制**且没有冒号**，`grep "10046df90:"` 不命中，要用行首锚定。

---

## 3. 阶段 C：存档格式逆向（本作主线，可照抄）

### C1 容器识别
看前 64 字节。先找**文件魔数**和**记录魔数**，再看 4 字节对齐的 u32 是否像"长度/条数"。
把每个 u32 与"它后面实际可解析的记录数"交叉验证，比凭直觉命名可靠。

### C2 记录扫描
不要按"头部记录数"循环解析——头部数字与实际魔数出现次数经常不等（本作 55 vs 61）。
正确做法：**全文扫记录魔数 + 结构校验**（本作的校验是 `+8..+14 == 030005000004`），
再用下一条魔数位置反推本条长度。

### C3 压缩判定（最贵的坑）
```
比值 = gzip(载荷) / 载荷
```
- 比值 ≈ 0.5–0.8 且解压成功 → 是压缩，去找算法。
- **比值 ≈ 0.94–1.0 且载荷内有连续可读 ASCII → 是未压缩的数值密集数据，不是压缩。**
- 比值 ≈ 1.0 且载荷熵很高 → 加密。

本作曾仅凭"gzip 比值≈1 + LZ4/deflate 解不开"就误判成 Oodle2，白绕了一大圈。
**加一条判据：解不开不等于压缩；先看明文密度。**

### C4 字段结构推断
改一个可控变量（换装备/加点/移动），另存一档，做差分。改多次 → 多份对照。

### C5 差分法：信号 vs 噪声（必须做对照组）
| 组 | 操作 | 作用 |
| --- | --- | --- |
| 信号 | 只改目标变量（如换帽子）后存档 | 找出"目标变量影响哪些字节" |
| 噪声 | **什么都不改**，直接再存一次 | 找出"每次存档都会变的元数据" |

**只有 (信号 − 噪声) 才是候选字段。** 本作没有对照组时，把 rec12 `+0x82e` 的
4 字节误判成帽子 ID；做了空存对照后发现它也变（`0x43efd9c1 → 0x43eefd14`），结论撤回。

工具：`./saveparse/acdb.py diff A.sav B.sav` 输出记录级差异 + 变化字节区间。

### C6 类型哈希 = CRC32（可复用的高价值发现）
序列化容器的每条记录常常带一个 4 字节类型哈希。**先试 CRC32(类名)**：
本作载荷 `+3` 处 4 字节 = `CRC32(类名)` 小端，`CRC32("InventorySaveData")=0x28898cc6` 精确命中。

命中后就能**离线建全表**：在二进制里枚举所有"类型注册"调用点（`findcall` 扫 `bl`），
解出每个调用点前面的类名常量，算 CRC32 → 得到 `哈希 → 类名`。
本作 486 个注册点，几分钟内翻译全档 55 条记录。**不需要运行时 hook。**

### C7 什么时候停止静态
出现以下任一情况就转运行时：
- 字段名在二进制里 0 命中，且**已确认是编译期哈希**（见 C8 的可解析率判据）。
- 类型值是编号（`0x0100068c`）而非字符串，且注册表里只有工厂指针。
- 记录 0 有"自描述类型字典"，但字典本身是紧凑二进制、无字符串名。
- 差分能定位"哪条记录"，但定位不到"记录内哪个字段"（信号被结构变化淹没）。

> 本作曾把"字段名 0 命中"归因于**链式指针**，这是错的：该二进制用的是老式
> `LC_DYLD_INFO_ONLY`（rebase 124 万条），不是 `LC_DYLD_CHAINED_FIXUPS`。
> 两种机制都会让"直接搜 8 字节绝对指针"失效，但根因不同，别混写。

### C8 名字哈希反查（本作 1998 处命中）
序列化流里的字段名常被编译期哈希成 4 字节。**先假设是 CRC32，用二进制的字符串表反查**：

```python
h2n = {zlib.crc32(s) & 0xffffffff: s for s in 二进制里的可读串}
命中 = [h for h in 存档里所有 4 字节窗口 if h in h2n]
```

本作 260,276 个字符串 → 反查 `ManualSave06` 命中 **1998 处**（随机期望 <0.01，
统计上不可能是巧合）。记录 0 的"不可读字典"当场全部翻译成
`SaveGameFile`/`ClassDataDesc`/`PropertyDataDesc`。

工具：`tools/namemap.py`（任意 Mach-O + 任意存档，`--rec` 指定记录、`--grep` 过滤）。

**什么时候该停手：先估可解析率。** 取一批同位置的哈希，看能翻译出多少：

| 可解析率 | 判断 |
| --- | --- |
| ~17%（本作实测） | 确实是名字哈希，但**83% 的标识符字符串从未输出**（constexpr 哈希）→ 单个解不出是正常的，别死磕 |
| ~0.006%（随机水平） | 找错方向了，根本不是 CRC32 |
| >90% | 恭喜，继续全量反查 |

### C9 从类描述符表直接读字段布局（不用逆序列化逻辑）
类型注册器里每个成员都对应一条**编译期描述符**，通常落在 `__DATA`（有文件备份，可直接读）。

本作实读结果（`LoadoutItemSaveData`，16 字节）：

| 成员 | 类型哈希 | 名字 | 偏移 | 宽度 |
| --- | --- | --- | --- | --- |
| `Slot` | `0x0c3c8f59` | `CRC32("Slot")` | `+0x00` | 8 |
| `ItemID` | `0x893a928f` | `CRC32("ItemID")` | `+0x08` | 8 |

**定位注册器的最快路径：类名字符串的 xref。** 注册器里一定有类名字面量，
`FindRefs(类名字符串地址)` 一步到位（本作 5 秒一次）：

```
"AssassinSaveGameMetaData" @ 0x10a8ee995 → FUN_1035afc48
"HubRedSaveMetaData"       @ 0x10a887f10 → FUN_101de72d8
```

注册器开头是 `RegisterType(obj, "ClassName", 0, CRC32(ClassName), this)`，
后面每个 `RegisterMember(obj, offset, &desc)` 就是一个字段。
**基类由单独一次调用注册**（本作 `FUN_101de7430`），所以派生类成员表不含基类字段。

**必须交叉验证**：拿成员表去对存档里的实际字节。本作 `HubRedSaveMetaData`
成员表只有两个 u32（`+0x78`/`+0x7c`），存档里它的值恰好是 `501, 654`——
对上才算表读对了。

### C10 容器内的"位打包数组"要说停
成员表能定到容器边界，但**容器内部常是位打包/变长合并的数组**，不是记录列表。
判据（本作 rec3 的 294 字节实测）：

- `00 00 <u16 len> 0b` 这类长度前缀**合法个数为 0**（同级已知字段区有 2 个）；
- 字节分布小值密集：`0x00`×33、`0x01`×20、`>0x80` 仅 17%；
- **一次逻辑改动分散在 6 处不连续字节**（换顶帽子）。

符合以上三条就不要再试图"按成员切开"，得去读容器序列化器本身（本作 `FUN_10079bea0`，
16 KB）——投入产出比明显下降，适合作为收尾点。

**跨平台移植复用一招**：把 Mac 可执行文件改写成 dylib 做移植时，新文件 `__TEXT`
与原文件**逐字节相同**（只差 Mach-O 头与 load commands）。本作 1.896 亿字节里
仅 3779 字节不同，抽查地址指令全等。所以**一份分析项目可同时服务原版与移植版**，
地址直接通用，不必为移植版重跑几十小时分析。

---

## 4. 阶段 D：配置文件 / 画质档位矩阵

不要在游戏外插值。**让游戏自己写出来：**

1. 备份当前配置。
2. 起一个"配置监视脚本"（本作 `acst/ini-watch.sh`）：只在**目标段**的指纹变化时存快照，
   忽略窗口位置/FOV 这类噪声（这些也会触发写盘，实测踩过）。
3. 在游戏内把每个预设从低到高各切一次，每次切完退出（退出时游戏会重写配置）。
4. 拼矩阵（本作 `acst/ini-matrix.sh`）：行 = 键，列 = 档位，`*` 标记跨档不同。
   **每列最大值就是该键的上限**——不是所有键都是 "0..N"，多数键有各自封顶值。

两条经验：
- 值常常就是档位序号（0 起），但不是所有键都这样（本作 `engine_textures` 中档跳变、高档封顶）。
- 跨 7 档完全不变的单段键，通常"本来就不该跟画质档走"，别当遗漏。

---

## 5. 阶段 E：运行时注入层

### E1 最小骨架
`DYLD_INSERT_LIBRARIES=./libxxx.dylib` + constructor 里装 hook。
macOS 上不需要关 SIP、不需要有效签名（adhoc 即可）——与 iOS 完全不同，别把 iOS 约束套过来。

### E2 开关语义（踩过的坑）
"默认全开"式开关（如 `ac_env_on(name, dflt)` 缺失即取默认）会让**任何一次没带环境变量的启动
都处于插桩状态**，测量数据被污染。新开关一律用**显式 opt-in**：
`getenv(name) != NULL && strcmp(v,"0") != 0`。

### E3 找 hook 锚点
按成本从低到高：
1. **字符串引用**（`findxref`）：日志/错误串 → 附近函数。
2. **魔数立即数**（`findimm`）：文件格式读写函数。
3. **类型注册调用簇**（`findcall`）：拿到类名 + 哈希表。
4. 反汇编回溯调用者，确认参数寄存器（`x0..x3`）语义后再 hook。

### E4 注入层卫生
- 日志分文件、限流（本作 `UNIMPL` 去重 + 累计计数，避免 2 万行/30 秒冲爆）。
- 每个统计都要有"非空自检"：本作 `TEXSTATS` 曾因为只挂到第一个 heap 类而静默变成 `total=1`，
  基于空统计做出的结论全部无效。
- 启动脚本加"已在运行则不重启"保护，避免两个实例抢占。

### E5 失焦鼠标保护（窗口化游戏的通用副作用）

**症状**：窗口模式下切到别的应用后，鼠标被拽回游戏窗口、点不动其他窗口，甚至光标消失。
原因是游戏每帧都在做"捕获鼠标"的三件事，而且**失焦后仍然继续做**：

| 游戏调用 | 作用 | 失焦时的正确处理 |
| --- | --- | --- |
| `CGWarpMouseCursorPosition(p)` | 把光标拉回窗口中心 | 直接返回 `kCGErrorSuccess`，不转发 |
| `CGAssociateMouseAndMouseCursorPosition(0)` | 解除光标与鼠标的关联 = 系统级锁鼠标 | 改写成 `1` 再转发 |
| `CGDisplayHideCursor` / `+[NSCursor hide]` | 隐藏光标 | 忽略；失焦时主动 `show` + `unhide` |

**做法**：interpose 三个 C 函数，再用 method swizzle 拦 `+[NSCursor hide]`；
只在失焦时改行为，并在检测到「前台 → 失焦」跳变时主动
`CGAssociate(1)` + `CGDisplayShowCursor` + `[NSCursor unhide]` 复位。
前台行为必须**完全不变**，否则会破坏游戏自身的光标逻辑。

取原实现**不能**用 `dlsym(RTLD_NEXT, …)`：一旦用了 `__DATA,__interpose`，
dyld 会把 `RTLD_NEXT` / `RTLD_DEFAULT` / 镜像句柄三种 dlsym 的返回值**全部改写**成
我们自己的替换函数（实测三个地址都等于替换函数，自指检查后全部判空）。
正确写法是解析目标镜像的 `LC_SYMTAB`，按符号名取 `n_value + slide`：

```c
// image_part 例如 "CoreGraphics.framework"
for (i = 0; i < _dyld_image_count(); i++) {
    if (!strstr(_dyld_get_image_name(i), image_part)) continue;
    mh = (struct mach_header_64 *)_dyld_get_image_header(i);
    slide = _dyld_get_image_vmaddr_slide(i);
    // 遍历 load_command 找到 LC_SYMTAB，扫 nlist_64：
    // (n_type & N_TYPE) == N_SECT && strcmp(strs + n_strx + 1, want) == 0
    //   → return (void *)(n_value + slide);   // Mach-O 符号名带前导下划线
}
```

另一个前提：`__DATA,__interpose` 里的 replacee 必须是**真实链接**进来的符号。
不链接该框架、靠 `-Wl,-U,_symbol` 悬空解析时，interpose 表拿到的不是可调用的原实现，
游戏会在第一次调用时直接 **SIGBUS**（实测 MetalFX 曝光纹理之后，exit 138）。

**三个坑**：
1. `dlsym(RTLD_NEXT, "CGWarpMouseCursorPosition")` 在 interpose 下会自指（见上），
   必须改用 `LC_SYMTAB` 解析，并保留"与自身地址相等即视为失败"的自检。
2. `+[NSCursor hide]` 是**类方法**，swizzle 时要传 `class_method = YES`；
   只 hook 实例方法会漏掉，且失败时必须打日志（本作靠 `钩子安装失败` 一行发现）。
3. 这类修复**自动化测不到**——只能验证日志（`失焦：恢复鼠标关联并显示光标`）
   和钩子安装成功，真实"失焦后能否点其他窗口"必须人工确认。

**替代焦点判定**：不必依赖 AppKit 的 `NSApplicationDidResignActiveNotification`。
用 `CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID)` 取
最前面的 `layer == 0` 窗口，比对 `kCGWindowOwnerPID` 是否等于 `getpid()`，结果缓存
250ms 即可在渲染线程每帧调用。好处：纯 C、线程安全、不需要链 AppKit。

**默认值**：在它来源的项目里是**默认开**（不需要显式设开关）。
新游戏照搬这套修复时**建议也保持默认开**：它只在 `gAppActive == NO` 时改变行为，
前台完全透传，不会影响游戏自己的光标逻辑；而"失焦后鼠标被锁死"是用户最先骂的体验问题，
默认关等于把这个坑留给每个后来者。要留反开关时，语义应是"关掉保护 = 恢复游戏原始行为"。

### E6 窗口切换 / 退出快捷键被禁（AppKit presentationOptions 与菜单项是两回事）

**症状**：游戏里按 `Cmd+Tab` 没反应；有时 `Cmd+W` / `Cmd+Q` 也没反应。
**这是两个完全不同的机制，不要混成一个开关改**：

| 快捷键 | 根因 | 在哪改 |
| --- | --- | --- |
| `Cmd+Tab` | `-[NSApplication setPresentationOptions:]` 带了 `NSApplicationPresentationDisableProcessSwitching (1 << 5 = 0x20)` | swizzle 该 setter，清掉 `0x20` |
| `Cmd+W` / `Cmd+Q` | 游戏用 `setMainMenu:` 重建了主菜单，**把标准 Close / Quit 菜单项删了**，并自己实现 `applicationShouldTerminate:` | presentationOptions 无关；只能自己插菜单项 |
| `Cmd+Opt+Esc` | `NSApplicationPresentationDisableForceQuit (1 << 6)` | 同上，按需清 |

**做法（Cmd+Tab）**：swizzle `-[NSApplication setPresentationOptions:]`，只清 `1 << 5`：

```c
opts &= ~(cd_uword)(1 << 5);   // 其它位（隐藏 Dock/菜单栏、DisableForceQuit）全部保留
```

再加一个**主队列 1 Hz 看门狗**兜底：AppKit 内部可能绕过 public setter 直接应用 options，
每秒钟读一次 `-presentationOptions`，若仍带 `0x20` 就再清一次并留一行日志。
（`[NSApp sharedApplication]` 只能在主队列调，用 `dispatch_source` 挂 `dispatch_get_main_queue()`。）

**三个坑**：
1. **只清 `1 << 5`**。顺手把 `HideMenuBar` / `AutoHideDock` 一起清掉会改变全屏观感，
   用户会以为画面坏了。其它位一律保留。
2. **不能只靠 swizzle**。实测 AppKit 在进入全屏的路径里可能直接应用 options，
   不经过 public setter；没有看门狗时表现为"刚进全屏 Cmd+Tab 又失效"，重进一次才好。
3. **`Cmd+W` / `Cmd+Q` 别用同意思路修**。补 `Cmd+Q` 可以插一个 action = `terminate:` 的菜单项
   （会走游戏自己的退出确认）；`Cmd+W` **不要**绑 `performClose:`——窗口关掉通常等于退出，
   容易误触丢进度，要绑就绑 `performMiniaturize:` 或干脆不补。

**默认值**：默认开，`<前缀>_KBD_GUARD=0` 关闭。它只放开"切走"的能力，
不替玩家做任何破坏性动作（不自动退出、不关窗），所以默认开是安全的。

---

## 6. 阶段 F：显存 / 性能测量方法学

**固定四件事，缺一不可：**

```
同一画质配置 + 同一游戏位置 + 同一等待时长 + 同一存档与角色数
```

最后一项是本作补上的：同一主页，无存档显示 2 个主角、读档只显示 1 个，
资产量不同，读数**不可比**。历史上的阶段（登录框/早期菜单）读数已全部作废。

口径要分清：
- `metal_alloc` = 已分配（分子）
- `heap.size / usedSize` = 堆口径
- placement heap vs 普通 allocation 归属
- 归档/缓存类（PSO archive）**不占显存**，别拿它算收益

反直觉结论也要记录：本作 `engine_textures=0`（最低）比 `=6` 更耗显存 880 MB，
因为池子太小导致反复驱逐+重载（累计纹理创建 49 万次），是**抖动不是驻留**。
结论改成"合理下限是 2"。

---

## 7. 坑清单（跨游戏通用，按踩坑成本排序）

| # | 坑 | 正确做法 |
| --- | --- | --- |
| 1 | 把"解不开的压缩"当成压缩 | 先算 gzip 比值 + 明文密度；比值≈1 且有可读串 = 未压缩 |
| 2 | 搜绝对指针 0 命中就以为没引用 | 链式指针下必须扫 `ADRP+ADD` / 立即数 |
| 3 | 没有噪声对照组 | 每次信号差分都配一次"零变化存档" |
| 4 | 把日志/遥测事件名当序列化字段名 | 看命名邻居：紧挨 `WaitXxx`/启动流程名的一律是事件名 |
| 5 | 统计静默失效还用它的数 | 每次用统计前先确认"总量非零、量级合理" |
| 6 | 跨阶段/跨存档比显存 | 固定四件事，写进结论里 |
| 7 | 信文档里的行号 | 一律 grep 锚点定位 |
| 8 | 静态啃不动硬啃 | 出现 3.C7 的任一信号就转运行时 hook |
| 9 | 商用压缩包强行解 | 先算"解出来能干什么"，推不出下游输入就不做 |
| 10 | 开关默认全开污染测量 | 新开关一律显式 opt-in |

---

## 8. Mac 平台通用问题清单（与具体游戏无关）

> 这份清单是"换任何一款 Mac 游戏都还会再遇到"的问题。
> **【实证】** = 本作真实踩过并有日志/字节级证据；**【通用】** = 业界通例，本作未直接触发，作为检查项。
> 按遇到概率排序，前四组基本必中。

### 8.1 启动与进程

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| `open` 启动后 cwd 是 `/` 【实证】 | `DYLD_INSERT_LIBRARIES=./lib.dylib` 加载失败 | 注入库路径一律给绝对路径；日志里先确认 `inject init` |
| 内嵌 WebKit 的孤儿 XPC 【实证】 | 第一次正常，**第二次启动登录框黑屏** | 启动前清理被 launchd 收养的孤儿 WebKit 进程（本作 `AC_WEBCLEAN`） |
| `atexit` 不执行 【实证】 | 退出后统计文件缺失、最后一段日志丢失 | 游戏多走 `abort`/私有退出路径；统计改为**定时节流落盘**，别依赖退出钩子 |
| 在线服务弹框抢焦点 【实证】 | `storeuid`/AMS 登录框盖在游戏画面上，游戏无法屏蔽 | 尽早判定"在线不可用"，直接走离线分支 |
| 启动视频/Logo/EULA 【实证】 | 每次启动浪费固定时间，自动化脚本等不到窗口 | 在二进制里找启动参数（本作 `nostartupvideo`、`fixeddt`），别改资源文件 |
| 没先验证"不注入也能启动" 【实证】 | 注入后异常时无法判断是游戏问题还是注入问题 | 先跑一遍纯原版拿到基线（本作结论：注入是增益不是前提），**再**上注入层 |
| 联网失败就走不下去 【实证】 | 启动即卡在登录/激活，进不了游戏 | 离线三处伪造：`connect` 只放行回环/`AF_UNIX`、`SCNetworkReachabilityGetFlags` 返回 0、`nw_path_get_status` 返回 `unsatisfied` |

### 8.2 签名、沙盒与权限

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 改 bundle 内 `Info.plist` 【实证】 | `invalid Info.plist (plist or signature have been modified)` → 重签 → 丢 TeamIdentifier → 整条认证链崩 | **一个字节都不改**；版本兼容放运行时 hook |
| ad-hoc 签名无身份 【实证】 | `errSecMissingEntitlement(-34018)` → 拿不到 ticket → 服务端 1008 → "无法连接互联网" | 侧载/重签必然发生，账号/内购/Keychain 从设计上划为不可用 |
| 注入了但没生效 【通用】 | 进程正常启动，日志里没有注入库 | 依次查：hardened runtime（`codesign -dv` 的 `flags`）、library validation、SIP、注入变量是否被剥离 |
| 沙盒开关导致数据搬家 【实证】 | 存档/配置路径在两个目录间切换，旧数据"消失" | 跑一次游戏按 mtime 重新定位，不要相信文档里的固定路径 |
| TCC 权限弹窗 【通用】 | 访问 Documents/Desktop/Downloads、屏幕录制、辅助功能、输入监控被拦 | 无 UI 的注入层不能假设已授权；先手动授权一次并记录到文档 |
| quarantine 属性 【通用】 | 下载/拷贝的 app 首次启动被拦或行为异常 | `xattr -dr com.apple.quarantine <app>` |
| 以为数据文件也要签名 【实证】 | 不敢改/搬 `.forge` 之类资源 | 数据文件不参与签名，随便搬；只有 Mach-O（含 dylib）需要重签 |
| 把 lldb attach 当默认能力 【实证】 | 换到不能 attach 的环境后完全失去观测手段 | Mac 上能 attach 是因为 SIP 关闭，属特权；调试能力要内置进注入层（日志/内存扫描） |

### 8.3 窗口、显示与输入

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 失焦鼠标捕获 | 切走后鼠标被拽回、点不动别的窗口 | 见 5.E5 |
| HiDPI 默认 2x 【实证】 | Retina 上 drawable 按 2x 渲染 = 像素量 4x，显存/带宽翻倍 | `contentsScale` 覆盖为 1.0；游戏若写回 2.0 就每帧再覆写 |
| 窗口未激活收不到键盘 【实证】 | 程序化发按键无效 | 先 `activate` 置前台再发；键盘导航比坐标点击稳 |
| 全屏/多显示器切换 【通用】 | 换屏后 drawable 尺寸/scale 变化，缓存的 screen 参数失效 | 监听窗口/屏幕变化失效缓存，不要一次性缓存到底 |
| App Nap 【通用】 | 后台窗口帧率/CPU 被系统压低，后台测的性能数字不可比 | 测性能必须前台；需要后台跑时声明活动状态 |
| 假 HID 设备不可行 【实证】 | `IOHIDUserDevice` 失败，root 与关 SIP 都无效 | 需要 Apple 私有 entitlement；改用**进程内伪造 GCController**（swizzle `+controllers`，引擎逐帧轮询时只要状态对即可） |
| 手柄回调不是必要路径 【实证】 | `pressedChangedHandler` 恒为 0，但输入生效 | 别抢 handler（会与游戏输入路径冲突），保证 `isPressed`/`value` 正确即可 |
| hook 挂在"首次事件"上 【实证】 | 首帧/首个 present 之前的调用全部漏掉 | 本作 `ac_present_hook` 直到第一次 scaler encode 才安装 → 之前 present 不受拦截；能提前就提前 |
| 每帧多取一个 drawable 【实证】 | 帧生成/插值方案需要第二个 drawable，池紧张时阻塞或取不到 | 先算清三缓冲预算，或同帧复用；别默认 drawable 无限 |
| 注入的 UI 挂错窗口 【实证】 | 窗口未建好时无处可挂，建好后覆盖层还在旧视图上 | 先兜底挂 key window 根视图，收到窗口建立通知后迁移 |

### 8.4 Metal / GPU

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 显存口径混淆 【实证】 | RSS 785 MB 被当成显存；`footprint` 与 `metal_alloc` 混用 | 显存看 `metal_alloc`（与 Metal HUD 对齐），主机内存看 `phys_footprint`；文件映射的干净页不算显存 |
| placement heap 读不到占用 【实证】 | `heap.usedSize` 恒为 0，`fill=0%` | type=1 的 heap 无此字段；改用存活纹理弱引用表按 `allocatedSize` 求和 |
| 同一分配计两遍 【实证】 | `other` 算出负数、buffer 体积翻倍 | `newBufferWithLength:` 内部会走 `:offset:` 变体，两个 hook 都要按 offset 去重 |
| usage 标志关掉无损压缩 【实证】 | 45% 纹理带 `ShaderWrite`/`PixelFormatView`，Apple GPU 压缩被关 | **注入层清标志必崩**（引擎真的会 `makeTextureView`）；只能改引擎内部 usage |
| 归档容量结论反复 【实证】 | `MTLBinaryArchive` 40 MB 被当硬上限 | 实测单片 287 MB；40 MB 只是切片阈值。载入失败必须显式计数，别静默新建 |
| Metal 归档跨 OS 版本 【实证】 | 升级后首次启动预热指标变差 | OS 更新会后台异步升级归档，首次回落 IR 重编属正常，别判成 hook 失效 |
| 能力判断靠猜 【实证】 | 以为有帧生成，实际没有 | 查导入符号：本作只有 `MTLFXTemporalScalerDescriptor`，无 `MTLFXFrameInterpolator` |
| 崩溃线程名误导 【实证】 | 崩溃线程叫 `USHttpEngine/Loading Thread`，实际与网络无关 | `abort` 是全局终止，先撞上的线程背锅；看调用栈不看线程名 |
| 帧率控制不是画质档 【实证】 | 锁帧键在所有预设里恒为 0 | `display_framerate` 是独立开关，与画质档无关 |
| 只挂到第一个实例类 【实证】 | 统计静默变成 `total=1`，后续实例全漏 | 引擎常有多套 heap/device 具体类；按类名集合逐个补挂，orig IMP 存在**类关联对象**里，别共用全局函数指针 |
| 拿归档占用算显存 【实证】 | 以为预热吃了几百 MB 显存 | `MTLBinaryArchive` 是文件映射的干净页，`metal_alloc≈0`；它换的是时间不是显存 |
| 缓存键随分片重置 【实证】 | 覆盖率虚高、`adds ≈ created`，预热等于没接 | 指纹/命中表必须**全局单文件**，切片只落盘不清空；首次升级要迁移旧键 |
| 用"总量/条数"估单条大小 【实证】 | 估算偏到 120 KB/条，几秒就误判写满 | 用**本次落盘增量 ÷ 新增条数**做 EWMA 并 clamp，别用累计值相除 |

### 8.5 网络与在线

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 误判为网络问题 【实证】 | 花大量时间查代理/DNS，实际是认证失败 | 顺序：应用层响应头（有 `Ubi-*` 类自家头 = 穿透成功）→ 签名/entitlement → 最后才是网络 |
| WebKit 登录页选择器 【实证】 | JS 注入登录不生效 | 先抓真实 DOM 再写选择器；页面结构随版本变，别硬编码 |
| 云存档覆盖 【实证】 | 本地替换的存档被云端回滚 | 替换/实验前关闭云同步 |

### 8.6 文件与路径

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 路径含空格/非 ASCII 【实证】 | 脚本静默失败（`~/Library/Autosave Information`） | 一律加引号；脚本里别用未引用的变量展开 |
| 大小写不敏感 APFS 【通用】 | 大小写不同的两个"不同"文件名实际是同一个 | 清单/匹配不要依赖大小写区分 |
| 嵌套目录漏文件 【实证】 | DLC 清单少了 `dlc_20/dlc_20/` 里的 18 个文件 | 用 `find -type f` 生成清单，不要用 `ls` |
| 跨平台/跨账号存档直接混用 【实证】 | 覆盖后读档报"存档已毁损 `0x82000002`" | PC 版是"36 字节壳 + 加密记录"、Mac 版是明文容器；只解外层壳不够，记录层仍绑账号密钥 |
| 把各种 UUID 混为一谈 【实证】 | 拿应用 ID 当账号 ID 去解密，必然失败 | 账号 `userId` / 服务空间 `spaceId` / 应用 `applicationId` / 实体 GUID 分开记录，别用一个字段猜 |

### 8.7 逆向与工具链

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| `dlsym(RTLD_NEXT)` 自指 【实证】 | interpose 的 `connect` 解析回自身，约 3300 层递归后 SIGILL | 取到后与自身函数地址比较，相等则走 `syscall(SYS_xxx)` 兜底；所有 interpose 都要做 |
| `dladdr` 归属错 【实证】 | pc 略微越界被归到相邻镜像，探针全体失效 | 按镜像名扫 `_dyld_get_image_name` |
| `otool` 地址格式 【实证】 | `grep "addr:"` 永不命中 | 地址是 16 位十六进制且无冒号，用行首锚定 |
| 全局查不到就以为不存在 【实证】 | 动作/对象管理器里找不到某 ID | manager 常按页面/场景**每实例一份**；页面没打开时任何 manager 都查不到 |
| 日志事件名当字段名 【实证】 | 把 `Rarity`/`VisualId` 等当成序列化字段 | 看命名邻居：紧挨启动流程名的都是日志/遥测事件 |
| hook 失败不报错 【实证】 | `ac_hook_method` 找不到方法只把原 IMP 置 NULL，进程照常跑 | 每个 hook 都要打"成功/失败"行；判断是否挂上**只能看日志**，不能看进程是否存活 |
| 日志没有崩溃安全路径 【实证】 | 进程异常退出时日志尾部正好缺最关键几行 | 全部走 stderr 就必然如此；关键状态用独立 fd/文件，按固定间隔刷盘 |
| 在游戏进程里查"文件能不能载入" 【实证】 | `archive=new` 分不清是文件坏了还是进程内时机问题 | 用独立小探针进程复核同一批文件（本作 `capN load`：25/25 载入成功），把变量隔离掉 |
| Metal 类型名/属性访问踩编译坑 【实证】 | `Depth16Unorm` 写法不对、`id` 上点语法撞多个同名方法 | 实际叫 `MTLPixelFormatDepth16Unorm`；descriptor 用强类型 `MTLTextureDescriptor *` 访问 |

### 8.8 资源打包与解包决策

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 商业压缩格式 【实证】 | 大文件是 `.forge`/`.pak`，内部 Oodle2（Kraken/Mermaid/Leviathan 家族） | 从二进制里的源码路径串判断算法族；商业编解码器无公开规范、非导出符号，`dlsym` 取不到 |
| 在压缩流里搜魔数 【实证】 | 搜 `MTLB` 得到一堆"假头"，`metal-lipo` 报 `bad minor version number` | 压缩数据里出现魔数是巧合，不能据此判断"包里有这个文件" |
| 解包前没算下游用途 【实证】 | 辛苦解出 metallib，发现推不出管线描述符（函数配对/像素格式/顶点布局只在运行时组装） | 先问"解出来能喂给谁"；喂不进下游输入就明确不做，别做成半成品 |
| 全量加载型引擎"少解压" 【实证】 | 启动期一次灌 200 MB+，按需加载没有空间 | 唯一成立方向是"解压结果落盘换下次启动时间"，属加载时间另一笔账，需先测占比 |
| 资源清单裁剪 【实证】 | 担心剥离 DLC 影响本体 | 清单剥离不影响本体（PSO 覆盖率差异在噪声内）；入口在包内部无法剥离，点进去弹"缺失内容"属可接受残留 |

### 8.9 跨平台移植差异（Mac ↔ iOS/iPad）

| 问题 | 症状 | 处理 |
| --- | --- | --- |
| 以为 `DYLD_INSERT_LIBRARIES` 到处可用 【实证】 | iOS 没有该机制，宿主 interpose 对后 `dlopen` 的 dylib 也无效 | 改 fishhook 式改写 `__la_symbol_ptr`/`__nl_symbol_ptr`，在依赖框架的 constructor 里做 |
| 把 Mac 的签名宽松度带过去 【实证】 | Mac 上 ad-hoc + 无 hardened runtime 就能跑 | iOS 必须整包签名；侧载必然丢身份，账号/内购/Keychain 全划为不可用 |
| 依赖 lldb 调试 【实证】 | iOS 上 `get-task-allow` 与丢 entitlement 冲突，无法 attach | 注入层内置内存扫描（分段 `ReadMemory` + `bytes.find`）与文件日志 |
| UI 框架不存在 【实证】 | macOS 用 AppKit，iOS 没有 | 需要手写 AppKit 子集映射到 UIKit；同名类冲突要单独排查 |
| 输入框架不可移植 【实证】 | iOS 有 TouchController 私有框架，Mac 没有 | 只借"验收方法"不借实现；伪造 `GCController` 是两端都稳的主方案 |
| 按 Mac 读数外推 iPad 预算 【实证】 | iPad 带宽不到 Mac 一半 | 显存/带宽按底线数据算；纹理 usage 标志带来的 45% 压缩损失实打实吃帧率 |

---

## 9. 新游戏开工清单（可直接复制）

```zsh
# 0) 建工作目录
mkdir -p <game>/saveparse/samples <game>/tools

# 1) 摸底
APP="/Applications/<Game>.app"
file "$APP/Contents/MacOS/"*
otool -l "$APP/Contents/MacOS/<bin>" | grep -A4 LC_SEGMENT_64 | head -40
codesign -dv --verbose=4 "$APP" 2>&1 | head

# 2) 跑一次游戏，找"最近写入"的配置文件/存档
find "$HOME/Library" -newermt "-10 minutes" -type f 2>/dev/null | grep -iv cache | head -40

# 3) 容器/记录
xxd -l 64 <save>
LC_ALL=C grep -a -c $'<记录魔数>' <save>        # 记录条数
python3 -c 'import gzip,sys;d=open(sys.argv[1],"rb").read();print(len(gzip.compress(d))/len(d))' <payload>

# 4) 差分
python3 saveparse/acdb.py diff A.sav B.sav

# 5) 静态工具
clang -O2 -o tools/findimm tools/findimm.c
./tools/findimm <bin> <imm0> <imm1> <imm2> <imm3>

# 6) 注入层
./build.sh
AC_XXX=1 ./ac-run.sh ./libinject.dylib
```

**需要为本作之外的游戏替换的常量只有三类**：
① 文件/记录魔数；② 关键函数地址（类型注册、读写入口）；③ 哈希函数
（CRC32 是常见默认，命中不了再试 FNV-1a / xxHash / Murmur）。

**交付物结构建议**（与本仓库一致）：
```
<game>/
  research.md            # 结论 + 证据等级 + 反证方式
  saveparse/*.py         # 容器/记录解析（list/dump/raw/strings/diff 五件套）
  tools/*.c              # Mach-O 通用工具
  samples/               # 只读样本（原始档另存备份）
  PLAYBOOK.md            # 本文件（复制一份，按新游戏补差异）
```
