# artifacts —— 删除游戏前归档的不可再生产物

> **仓库现状（2026-11-16）：** 以下为历史记录；`game-binary/`、`ghidra-project/`、`diagnostic-reports/` 和 `../backup-saves-20261108/` 已清理，不包含在本仓库。涉及这些文件的命令须先自行准备对应合法资源。


游戏删除后，下列文件**无法从磁盘再生成**（要么需要那 214 MB 的 `scimitar`，要么需要游戏运行）。
全部只读留档，不参与日常流程。

| 文件 | 内容 | 可再生产性 |
| --- | --- | --- |
| `classhash.txt` | 类型注册表 486 条：`CRC32(类名) → 类名 → 注册调用点` | ❌ 需二进制。`InventorySaveData=0x28898cc6` 已交叉验证 |
| `addresses.txt` | 关键函数偏移（类型注册/存档魔数/动作/段布局） | ❌ 需二进制 |
| `actions.txt` | 262 条动作 `id → 名称` | ❌ 需二进制 |
| `scimitar.sha256` | 二进制哈希（用于确认版本基线） | ✅ 但哈希值本身需留档 |
| `diagnostic-reports/` | 3 份 `scimitar-*.ips` 崩溃报告 | ❌ 需重跑才能再产生 |
| `game-binary/` | `scimitar` + `libaegir_f.dylib` + `libmemorywrapper_f.dylib`（265 MB） | ❌ 需重装游戏；sha256 已核对一致 |

> ⚠️ `game-binary/Info.plist` 与 `Info.plist.bak-20261106` **都是改后状态**（mtime 同为
> 2026-11-06 11:44，仅差 `CFBundleVersion` 2 字节），**不是 App Store 原版**。
> 原签名已被 ad-hoc 重签覆盖，签名内的 Info.plist 哈希同时丢失，
> 所以"原版有没有某个键"（例如 `LSSupportsGameMode`）**无法从本目录证明**，只能重装后实测。

配套（在上级目录）：

- `../saveparse/acdb.py`：ACDB 容器解析器，**不依赖游戏**，可继续用于任何 `.sav`
- `../saveparse/samples/`：研究用存档样本（7 份）
- `../backup-saves-20261108/`：15 个 `.sav` + `ACShadows.ini` 完整备份
- `../GAME-RESEARCH-PLAYBOOK.md` / `../acst.md`：方法论与本作结论
- `decompiled/`：已反编译的存档函数与装备类（伪代码）
- `../tools/`：全部可复用工具

## 工具清单（换游戏可直接复用）

| 工具 | 用途 |
| --- | --- |
| `acdb.py` | 存档容器：`list` / `dump` / `raw` / `strings` / `diff` |
| `namemap.py` | 用二进制字符串表反查存档里的 CRC32 名字 |
| `classhash.py` | 从类型注册点建 `CRC32(类名) → 类名` 全表 |
| `findhash.c` | 滑窗找 `CRC32(任意子串)` 命中目标的名字 |
| `trydecomp.py` | 试探压缩算法（含手写 LZ4 block 解码器） |
| `dyld_rebase.py` | 独立解析 Mach-O rebase 表（绕开 Ghidra 的 10 万条上限） |
| `acstool` / `findxref` / `findimm` / `findcall` | Mach-O 指令级扫描 |
| `ghidra/DumpFunctions.java` | 定点反编译（`-noanalysis` 下可用） |
| `ghidra/FindSymbols.java` / `FindRefs.java` | 符号搜索 / 引用查询 |

## 已知硬边界（静态到此为止）

| 项 | 原因 |
| --- | --- |
| `0x9e4c9ab2` 等 83% 的标识符名 | 编译期哈希、字符串未输出 |
| 存档值的 TLV 变长解码 | 位打包、字段不对齐 |
| rec13/14/24/37 内容 | Oodle2 商业编码器 |
| 外观字段名 | 同第一条 |

再往下需要**重装游戏 + 运行时 hook**，静态分析已到极限。

## 删除游戏后仍然可做 / 不能再做

**仍然可做**
- 解析任意 ACDB 存档（`acdb.py` 全部子命令）
- 复用四个 Mach-O 工具与 `classhash.py` 到其他游戏
- 按 `addresses.txt` 在**同一版本**二进制上继续（前提是保留了二进制）

**不能再做**
- 定位装备字段的静态分析（需要 `scimitar`）
- 运行时 hook / 注入层验证（需要游戏本体）
- 重新生成 `classhash.txt`、`actions.txt`
- 读取 forge 资产

## 用这些产物继续研究（工具选型，2026-11-08 实测）

| 工具 | 用途 | 状态 |
| --- | --- | --- |
| `../tools/acstool` / `findxref` / `findimm` / `findcall` / `classhash.py` | 指令级精确扫描、地址归属、类名全表 | ✅ 已验证（486/486 命中） |
| `otool` / `nm` / `strings` | 段表、符号、字符串（`otool -tv` 地址无冒号，需行首锚定） | ✅ 系统自带 |
| REA MCP（`rea-agents` 6.8.0）+ Ghidra 12.1.4 | 反编译伪代码、xref、call graph、单函数分析 | ✅ 2026-11-09 打通（见下） |
| Hopper 6.6.2-demo | 手动反编译/图形视图 | ⚠️ demo 有会话时长限制，首次需人工过掉启动对话框 |

**Ghidra 安装要点（2026-11-09 实测）**

1. 只装 **12.1.x**：REA 6.8.0 的 verified 版本是 12.1.4，12.2 会被判 `unsupported`。
2. 官方 arm64 zip **不含** `os/mac_arm_64` 原生反编译器，必须本地构建：

```zsh
cd ~/tools/ghidra_12.1.4_PUBLIC/support/gradle
./gradlew Decompiler:linkDecompileMac_arm_64Executable \
          Decompiler:linkSleighMac_arm_64Executable
cp ../../Ghidra/Features/Decompiler/build/os/mac_arm_64/{decompile,sleigh} \
   ../../Ghidra/Features/Decompiler/os/mac_arm_64/
```

3. REA 进程只认环境变量（不读 shell 配置），必须写进 MCP 注册：

```json
"env": {
  "GHIDRA_INSTALL_DIR": "/Users/<user>/tools/ghidra_12.1.4_PUBLIC",
  "REA_GHIDRA_STARTUP_TIMEOUT_MS": "900000"
}
```

配置文件：`~/Library/Application Support/Trae CN/User/mcp.json`。改完需重启 REA 进程。

**验证记录**：`libmemorywrapper_f.dylib`（21 KB，arm64）→ `open_binary(provider_id="ghidra")`
→ `analyze_function(0x544)` → `procedure_pseudo_code` 返回
`void _AE_Mem_Alloc(void) { (*DAT_00004010)(); }`，全链路可用。

**两个使用约束**：
- REA 的 Ghidra provider 不接受 universal（fat）Mach-O，先用 `lipo -thin arm64` 取切片。
- Ghidra 对 dylib 的 image base 是 `0x0`，对可执行文件才是 `0x100000000`；
  查函数前先看错误里给出的 `Ghidra image base`，或用 `file-offset:0x...` 选择器。
- 214 MB 的 `scimitar` 会触发完整自动分析，耗时以十分钟计；改用定点反编译（见下）。

**定点反编译（推荐，2026-11-09 实测）**

```zsh
G=$HOME/tools/ghidra_12.1.4_PUBLIC
$G/support/analyzeHeadless /tmp/gproj ACShadows \
  -import artifacts/game-binary/scimitar -noanalysis \
  -scriptPath tools/ghidra -postScript DumpFunctions.java 0x1002fbe5c 0x1002d6984
```

- 导入 8 秒，三个函数（75/691/665 条指令）合计 **149 秒**，远低于全量分析。
- **关键坑**：只调用 `DecompInterface.decompileFunction()` 会得到
  `completed=true / hf!=null` 但 `getDecompiledFunction()==null`。
  必须先 `new DecompileOptions(); opts.grabFromProgram(currentProgram); di.setOptions(opts);`
  再 `toggleCCode(true)`，否则 C 输出为空。
- 已产出：`artifacts/decompiled/` 下三个存档函数的伪代码。
  其中 `0x1002fbe5c` 直接可见 `0x1004fa9957fbaa33`（存档魔数的 8 字节小端）。

**全量分析项目（后台跑，2026-11-09 启动）**

- 项目：`artifacts/ghidra-project`（`ACShadows.gpr` / `ACShadows.rep`）
- 日志：`/tmp/ghidra-full.log`，完成标志是 `Save succeeded for: /scimitar`
- 启动命令（独立会话，关掉终端也不影响）：

```zsh
GHIDRA_HEADLESS_MAXMEM=6G analyzeHeadless artifacts/ghidra-project ACShadows \
  -import artifacts/game-binary/scimitar -max-cpu 10 -analysisTimeoutPerFile 7200
```

- 分析完成后，任何查询都走 `-process`（秒级，不再分析）：

```zsh
analyzeHeadless artifacts/ghidra-project ACShadows -process scimitar -noanalysis \
  -scriptPath tools/ghidra -postScript DumpFunctions.java 0x1002fbe5c
```

- 已知限制：单文件分析是单线程的，`-max-cpu` 只用于多文件批处理。
- **实测（2026-11-09）**：总耗时 3007 秒（50 分钟），项目 3.5 GB；
  之后 `-process -noanalysis` 查询单个函数 **5.1 秒**。
- 耗时排行：`Objective-C Message Analyzer 933s`、`Stack 480s`、
  `Basic Constant Reference 423s`、`Data Reference 228s`、`Subroutine References 210s`、
  `Disassemble 仅 60s`。若要加速可禁 ObjC 分析器（省 15 分钟，但丢 ObjC 方法名）。
- **堆大小很关键**：上一轮 `-Xmx2G` 时 Disassemble 卡了 16 分钟没完成；
  改 `6G` 后同一阶段只需 60 秒——之前的"慢"主要是 GC 抖动，不是算法本身。

存档侧的结论最终必须回到 `acdb.py diff` 验证——反编译只给假设，字节差异才是证据。

## 删除时对应的磁盘项

| 路径 | 体积 | 说明 |
| --- | --- | --- |
| `/Volumes/LexarSSD/Applications/ACShadows/` | **151 GB** | 资源主体（app 内 `Resources` 符号链接指向这里） |
| `Assassin's Creed Shadows.app` | 265 MB | `Contents/MacOS` 含 `scimitar` + 两个 dylib |
| `~/Library/Caches/ac-inject/` | 482 MB | PSO 分片归档，离开游戏无意义（**2026-11-08 已删除**） |
| `~/Library/Autosave Information/saves/` | 4.8 MB | 15 个存档；备份已核对后**2026-11-08 已删除** |
| `~/Library/Logs/DiagnosticReports/scimitar-*.ips` | 117 KB | 已复制进本目录；**2026-11-08 已删除** |
