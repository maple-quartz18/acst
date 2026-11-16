# 存档研究（ACST / ACDB 容器）

本文记录对 **Assassin's Creed Shadows（macOS 版）** 存档格式、PC 版存档差异、
以及 ACSaveTool（ACST）实测的结论。所有结论来自本机实测与字节级比对。

---

## 1. 存档位置

### 1.1 当前生效（关闭 App Sandbox 之后）

```
~/Library/Autosave Information/saves/
```

内容（截至 2026-11-06，11 个存档 + 1 个配置）：

| 文件 | 说明 |
| --- | --- |
| `AutoSave01.sav` … `AutoSave05.sav` | 自动存档 5 个 |
| `ManualSave01.sav` … `ManualSave06.sav` | 手动存档 6 个（早期文档写 4 个，已过时） |
| `Options.sav` | 设置（含图形/操作选项快照） |

### 1.2 旧沙盒路径（已废弃）

```
~/Library/Containers/com.ubisoft.assassinscreed.Red.mobile/Data/Library/Autosave Information/saves/
```

**这个路径只在一种情况下存在**：从 App Store 全新下载、带正版收据（`_MASReceipt`）、
包体完整未被破坏的游戏。也就是说，沙盒是由「正版收据 + 未改动的签名」共同授予的，
不是游戏本身的固定属性。

本机已关闭 App Sandbox（改了 `Info.plist` 并 ad-hoc 重签），收据与签名的一致性被破坏，
所以沙盒容器不再启用，该目录为空。**不要再往这里放存档。**

推论：本机存档落在 `~/Library/Autosave Information/`（1.1）而**不是**容器内，
是"改过包体"的直接结果。排查别人机器上的存档位置时，先确认其包体是否原封未动。

### 1.3 配置

```
~/Documents/ACShadows.ini      # 生效配置（FOVScale、raytracing_mode 等）
```

容器内的 `Data/Documents/ACShadows.ini` 已不是当前使用的那份——原因同 1.2，
容器本身已不启用。

**路径规则总结**：包体原封（正版收据 + 未改签名）→ 数据在 `~/Library/Containers/<bundleid>/Data/…`；
包体被改过（关沙盒、重签）→ 数据回落到 `~/Library/…` 与 `~/Documents/`。

### 1.3.1 `[Scalability_Custom]` 键位含义

画质项都在 `[Scalability_Custom]` 里，`Profile=macos_custom` 表示走这张表。
数值含义是**档位**（0 最低、越大越高），不是开关。

| 键 | 含义 | 依据 |
| --- | --- | --- |
| `terrain_gpuscatter` | **物体散落密度**（GPU 提撒/散布，决定地表物件数量） | 用户确认（2026-11-06） |
| `engine_textures` | **纹理流送池大小**：决定纹理流送的内存分配，同时影响纹理品质与显存占用；**高及以上建议 12 GB 显存** | 用户确认（2026-11-07） |
| `display_framerate` | 游戏内锁帧上限（0 = 不锁） | 用户确认（2026-11-07） |
| `lighting_gi` | 光追 GI 独立开关，不受档位影响 | 用户确认（2026-11-07） |
| `terrain_virtualtexture` | 地形虚拟纹理档位 | 推断（名称直读） |
| `engine_spatialloading` | **加载距离**：调整物体开始加载的距离，**对 GPU 使用率有显著影响**（值越小加载越近、GPU 越省） | 用户确认（2026-11-07） |
| `geometry_micropoly` | **虚拟几何体渲染的显存容量**，游戏内只有 3 档（低/中/高）；**较低设置可能导致物体异常** | 用户确认（2026-11-07） |
| `geometry` | **绘制距离**：调整游戏世界的绘制距离，**不包含微多边形几何体**（微多边形走 `geometry_micropoly`），**对 GPU 使用率有显著影响** | 用户确认（2026-11-07，单变量实验：只拉高该项，ini 里唯一变化的就是 `geometry=0→6`） |
| `character` / `character_hairstrands` | 角色精度 / 毛发 | 推断 |
| `lighting_*` / `raytracing_*` / `shading_*` | 光照、光追、后处理、雾、云 | 推断 |

**当前实测快照（2026-11-06 23:32，已随存档备份）**：除
`character=6`、`engine_textures=6`、`terrain_virtualtexture=3`、`engine_spatialloading=1` 外，
其余（含 `terrain_gpuscatter`）全部为 `0`，即**散落密度已经压到最低档**。

对本项目的意义：`terrain_gpuscatter=0` 说明"物体散落"这条线已经没油水了——
它同时是 compute PSO 和实例数据的主要来源之一，调到 0 后 compute 侧只剩 2411 条左右。
再想降载/降显存，方向不在这个键上（实测显存主体是 placement heap 里的 buffer，见
`mac/inject/README.md` 8.3）。

**尚未确认**：各键的上限值（用户指出**每个键的上限不一样**，不是统一的 0–4）、
以及改 ini 后是否需要重启才生效。

### 1.3.2 上限怎么确定（2026-11-06 查证结论：公开资料没有）

查过的来源与结论：

| 来源 | 拿到什么 | 没拿到什么 |
| --- | --- | --- |
| Ubisoft 官方问答（hksource 那篇） | 写的是 **5 档**：低 / 中 / 高 / 非常高 / 超高 | 每档对应到 ini 的具体数值；**档数本身与实际不符** |
| 游戏内实测 | **实际是 6 档**（用户确认，2026-11-06） | 各档英文 Profile 名待采集 |
| PCGamingWiki | PC 端 ini 路径 `%USERPROFILE%\Documents\Assassin's Creed Shadows\ACShadows.ini`；画质选项有截图 | 键名与取值范围 |
| 各类画质优化指南 | 定性描述（如 "Scatter Density：High 性价比高"） | 数值范围 |
| 本机 `scimitar` 二进制 | 有 `ultra`/`VeryHigh` 等预设标识 | **键名一个都没有**（`terrain_gpuscatter` 命中 0） |

键名不在主二进制里，也不在 `Contents/Resources` 的明文文件中——最可能在
`DataMacOS_boot_*.forge` 内（Oodle2 压缩，见 `mac/inject/README.md` 10.5，已决定不解）。

### 1.3.3 实测矩阵：7 档 × 全部画质键（2026-11-07 采集完成）

游戏内切一遍预设、监视器自动落快照，即可让游戏自己把每个键的值写出来。
**实际是 7 档，不是 6 档**（Ubisoft 文章写 5 档，用户最初也说 6 档，实测为 7）：

```
macos_ultralow=0  macos_verylow=1  macos_low=2  macos_medium=3
macos_high=4      macos_veryhigh=5 macos_ultrahigh=6          ← 值就是档位序号，0 起
```

按档位从低到高排列（列 = ultralow → ultrahigh）：

| 键 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 规律 |
|---|---|---|---|---|---|---|---|---|
| `terrain_gpuscatter`（物体散落密度） | 0 | 1 | 2 | 3 | 4 | 5 | 6 | **严格线性**，值=档位 |
| `character` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 线性 |
| `geometry` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 线性 |
| `engine_spatialloading` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 线性 |
| `lighting_shadows` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 线性 |
| `effects_vfx` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 线性 |
| `engine_textures` | 0 | 1 | 2 | **5** | 6 | 6 | 6 | **中档跳变，高档封顶** |
| `effects_water` | 0 | 1 | 2 | 3 | 4 | 5 | **5** | 最高档也停在 5 |
| `lighting` | 0 | 1 | 2 | 3 | 4 | 4 | **4** | 上限 4 |
| `lighting_lights` | 0 | 0 | 0 | 1 | 2 | 2 | **4** | 稀疏 |
| `shading_clouds` | 0 | 0 | 1 | 2 | 2 | 3 | 4 | 稀疏 |
| `shading_posteffects` | 0 | 1 | 1 | 1 | 2 | 2 | 2 | 上限 2 |
| `shading_volumetricfog` | 0 | 0 | 1 | 1 | 2 | 3 | 4 | |
| `terrain_virtualtexture` | 0 | 0 | 1 | 1 | 2 | 3 | 3 | 上限 3 |
| `geometry_micropoly` | 0 | 0 | 0 | 0 | 1 | 1 | 2 | 只在 high 以上开 |
| `character_hairstrands` | 0 | 0 | 0 | 0 | 0 | 5 | 6 | 只在最高两档开 |
| `raytracing_world` / `raytracing_gi` | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 中档以下全关 |
| `raytracing_mode` | 1 | **0** | 1 | 1 | 1 | 1 | 1 | **不是档位**，见下 |
| `engine_physics` | 0 | 0 | 0 | 1 | 2 | 3 | 4 | 上限 4 |
| `display_framerate` | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 全档 0，像是独立开关 |

**两个反直觉发现**

1. `raytracing_mode` 在 **verylow 是 0、其它档（含 ultralow）都是 1**。它不是"越高越好"的档位，
   更像枚举（0=关 / 1=开某种实现）。判据是 `raytracing_world`/`raytracing_gi` 在 ultralow
   仍是 0——所以 ultralow 虽然有 `mode=1`，实际没有光追内容。
2. `character_hairstrands` 在 veryhigh=5、ultrahigh=6，值直接等于档位。这个键正常应是 0–3 的
   毛发档位，跟随档位跳到 5/6 说明**它只是被预设整体赋值，并不代表真有 6 级毛发**。

**对本项目的直接用处**

- `engine_textures` 是**纹理流送池的显存预算**，不是"画质等级"。这解释了它为什么在 high(4)
  就封顶到 6：池子到 high 就不再变大，再往上不增加预算。官方口径"高及以上建议 12 GB 显存"
  与本机实测 `recommendedMaxWorkingSetSize ≈ 12.1 GB` 正好对上——**high 就是为 12 GB 机器设的档**。
- 所以想真正压显存，**唯一有效的方向是把 `engine_textures` 往下调**：
  `6 → 5`（medium）是第一级台阶，`5 → 2`（low）是第二级。从 ultrahigh 降到 high 一字节都不省。
- `terrain_gpuscatter` 已确认是物体散落密度且严格线性，当前自定义档取 0（最低）。
- 其余键多为"上限低于最高档"（water≤5、lighting≤4、posteffects≤2、virtualtexture≤3），
  所以"把某键拉到 6"在多数键上无效，游戏会另找默认值。

**和显存实测的交叉验证**：注入层在该配置下测到 placement heap 占总分配约 90%
（方法见 `mac/inject/README.md` 8.3；具体数值见下方 WhiteRoom 实测表）。若纹理池的档位
真的决定预算，把 `engine_textures` 从 6 调到 5/2 应当让 `metal_alloc` 明显下降
——**这是一个可以直接 A/B 验证的假设**，判据是同一阶段（WhiteRoom 或同一存档位置）
同一等待时长下的 `TEXSTATS live metal_alloc` 差值。

**显存实测（同一时点，进入主页 WhiteRoom 之后）**

| 配置 | metal_alloc | footprint | live heaps | heap 容量 |
| --- | --- | --- | --- | --- |
| `engine_textures=0`（其余全 0） | **7953 MB** | 12248 MB（超 12 GB 工作集） | 4127 | 7431 MB |
| `engine_textures=6`（其余全 0） | **7073 MB** | 11793 MB | 2797 | 6551 MB |

两次都是启动后约 120 秒、进入 WhiteRoom 后的读数，配置只差这一个键。

**WhiteRoom 到底加载了什么（2026-11-07 静态查证，未启动游戏）**

现象（用户观察）：**有存档时只摆出存档里活跃的那一个主角；无存档时出现两个主角**。下面是对
「默认存档」的查证结果。

**查证到的资源与符号**

| 项 | 证据 |
| --- | --- |
| 磁盘上没有默认存档文件 | `~/Library/Autosave Information/saves/` 只有 11 个 `.sav` + `Options.sav`；`~/Library/Application Support/` 下无任何游戏目录 |
| WhiteRoom 是独立真实世界 | `DataMacOS_WhiteRoom.forge` 450 MB、`_patch_01` 80 MB、`_nav` 1.1 MB、`_floor`/`_metal`；`scimitar` 里有启动参数 `enablewhiteroom`、加载状态机步骤 `ActivateWhiteroomDataLayers` |
| `AnimusRoom` 是误导项（旧结论已作废） | `DataMacOS_AnimusRoom.forge` 仅 992 KB；二进制里的 `Animus` 绝大多数是 Ubisoft Animus Hub 的接口错误码（`ANIMUS-9`/`ANIMUS-10`、`LIVE_HUB_*`），与这个房间无关 |
| 主菜单按存档元数据展示角色 | 反射类型名 `HubPlayerVisualsSaveMetaData`、`HubBuildTagsSaveMetaData`、`HubRedSaveMetaData`（`scimitar` 偏移约 176655499 起） |
| 不存在「默认存档」命名 | 全量检索 `DefaultSave` / `PrebuiltSave` / `TemplateSave` / `PreviewSave` / `EmptySave`，命中 **0** |
| 主角是「主/次」二元结构 | UI 动作名 `BlacksmithChangeToPrimaryCharacter` / `BlacksmithChangeToSecondaryCharacter`（偏移约 176615598）；Hub 界面分组 `Protagonists {}` |
| 世界内有书签 | `DataMacOS_WhiteRoom.forge` 偏移约 2 391 414 处有明文串 `WhiteroomBookmark`（引擎 bookmarks 即世界内的出生/检查点标记） |
| 房间贴图作业 | `DataMacOS_WhiteRoom_metal.forge` 只有一个作业族 `job_GFX_Whiteroom_Mesh_Unlit_VideoSource_*`，说明这个 640 KB 分片只负责房间里的视频/屏幕面片，不含角色着色器 |

**判定**

- **不是磁盘存档文件**（确定，置信度高）：磁盘上没有任何候选文件，且无存档时游戏照样能进 WhiteRoom。
- **不是 `DataMacOS_AnimusRoom.forge`**（确定，置信度高）：该文件只有 992 KB，且 `Animus` 指的是 Hub。
- **「默认存档」这个词是误称**（置信度中高）：最可能是 **WhiteRoom 世界 + Hub 层组合出的内置默认展示态**——
  世界里有主角展示位（`WhiteroomBookmark`、双主角结构），Hub 再用 `HubPlayerVisualsSaveMetaData`
  决定"读得到存档就只显示活跃的那一个、读不到就保留默认的两个"。
  静态层面无法进一步区分「两个实体是世界预置」还是「Hub 运行时按默认参数生成」（forge 资产为 Oodle2 压缩，
  无明文文件名/实体名，主角名 `Naoe`/`Yasuke`/`弥助`/`奈緒江` 在 WhiteRoom 系 forge 中均零命中）。
- **能否替换**：不能靠替换存档文件来换；能换的只有存档里那个"活跃主角"的展示（即正常读档）。
  两个主角的默认展示属于世界/UI 内容，改它要动 forge 资产，本项目不做。
- **显存含义**：WhiteRoom 的 7 GB **不是"引擎空载地板"，而是「地板 + 1~2 个主角的全套资产」**
  （人物模型、服装、毛发、角色纹理都算在里面）。所以 1 个与 2 个主角的读数不可比。

**两条必须遵守的纪律**

1. **A/B 必须固定存档与角色数**——「有存档 = 1 个主角」与「无存档 = 2 个主角」的占用不可比；
   删档、换档、新建档之后再测，数字会变，别当成画质设置的效果。
2. 上表两局用的是同一存档、同一角色（1 个主角），因此 880 MB 的差值来自 `engine_textures` 本身，结论成立。
   表中两条读数应理解为「WhiteRoom + 1 个主角」条件下的数字。

结论：**`engine_textures=0` 比 6 更耗显存**。池子压到最小会让引擎反复驱逐+重载纹理
（该局累计纹理创建 49 万次 / 910 GB「分配过」，是抖动不是驻留），heap 也不回收。
所以 **0 不是"最省"，而是"抖动"；合理下限是 2（low）**，要省显存应在 2/5/6 之间比。

### ⚠️ 测量方法学（2026-11-07，必须记住）

历史上一批显存数字取自更早的阶段（登录/警告框时期），**与 WhiteRoom、游戏内都不可比，已全部作废删除**。
现在只保留上表这两个同条件读数。任何 A/B 必须固定四件事：

```
同一画质配置 + 同一游戏位置 + 同一等待时长 + 同一存档与角色数
```

角色数一栏是 2026-11-07 静态查证后补的：WhiteRoom 无存档时默认展示两个主角、读档后只展示活跃的那个，
两者占用的角色资产不同（见上一节），所以不记角色数的显存读数一律不可比。

阶段划分：

| 阶段 | 是否已测 |
| --- | --- |
| 离线警告框 / 早期菜单（无人物走动） | 旧数据，已作废 |
| **主页 WhiteRoom（1 个主角）** | ✅ 上表两个读数 |
| 主页 WhiteRoom（无存档 = 2 个主角） | ❌ 尚未单独测量 |
| 游戏世界（读档后实际游玩） | ❌ **尚未测量** |



**四个"显著影响硬件"的键（均已用户确认）**

| 键 | 游戏内名称 | 作用面 | 降到最低的后果 |
| --- | --- | --- | --- |
| `engine_textures` | 纹理流送池 | **显存** | 纹理糊，不破坏几何 |
| `engine_spatialloading` | 加载距离 | **GPU**（流式加载半径） | 远处物体 pop-in，不破坏几何 |
| `geometry` | **绘制距离** | **GPU**（draw 数 / 几何吞吐） | 远处物体不绘制，不破坏几何 |
| `geometry_micropoly` | 微多边形（虚拟几何体） | **显存**（仅 3 档） | ⚠️ **可能物体渲染异常** |

**`geometry` 的确认过程（单变量实验，2026-11-07）**：基线 `geometry=0 / terrain=0`，
游戏内只把"绘制距离"拉到最高后退出，ini 唯一变化为 `geometry=0→6`，`terrain` 恒为 0。

**`geometry_micropoly` 的 3 档与矩阵完全吻合**：实测取值为 `0 0 0 0 1 1 2`，
只有 **0/1/2 三个值**（low 及以下=0、high/veryhigh=1、ultrahigh=2），
与游戏内的低/中/高三档一一对应。这也是"我们的矩阵抓取是可信的"的一个独立佐证。

⚠️ 该键**不建议盲目压到 0**：用户确认低档可能导致物体渲染异常（虚拟几何体的显存池不够）。
它是"省显存但有视觉风险"的键，与 `engine_textures`（只降清晰度、不破坏几何）性质不同。

对 iPad 的意义：iPad 是带宽受限设备，加载距离直接决定同时在场景里的物体数量与 draw 数，
`engine_spatialloading=0` 应当作为 iPad 侧的**默认起点**；再往上加会先撞 GPU 而不是显存。

**7 档全一致 = 预设根本没碰过的键（共 23 个）**

| 分组 | 键 | 说明 |
| --- | --- | --- |
| `[Display]` / `[Options]`（21 个） | `WindowPosX/Y`、`Fullscreen*`、`Windowed*`、`RefreshRate=120`、`VSyncMode=1`、`WindowMode=0`、`HDREnabled=0`、`KeepStandardAspect=0`、`FOVScale=0.9`、`AutoFOV=1`、`AdapterVendorID/DeviceID=0`、`MonitorDesc` 空、`LastUsed*Mode=0`、`WindowMaximised=0`、`DisplayIndex=0` | 显示/窗口/FOV，**本来就不该跟画质档走**，切档不会重置它们（FOVScale 实测跨 8 份快照恒为 0.9） |
| `[Scalability_Custom]`（**只有 2 个**） | `display_framerate=0`、`lighting_gi=0` | 这两才是"画质键但预设从不赋值" |

这 2 个键的真实含义（**用户确认，2026-11-07**，推翻先前"遗留死键"的猜测）：

| 键 | 含义 | 判读 |
| --- | --- | --- |
| `display_framerate` | **游戏内锁帧上限**（0 = 不锁） | 与画质档无关，是独立帧率控制；想锁 60/120 就写对应数值 |
| `lighting_gi` | **光追 GI 的独立开关**，不被档位影响 | 与 `raytracing_gi`（跟随档位 0→3）是两条不同路径：一个手动全局开关，一个按档位缩放 |

**对本项目的意义**：`lighting_gi=1` 能在**任何档位**下强开光追 GI，属于"画质白送/性能白亏"的开关；
当前自定义档为 0，说明没开。反过来，这也是排查"为什么某档有间接光差异"时必须先看的键
——不能只盯 `raytracing_gi`。

**可行且便宜的办法：让游戏自己写出来。** 已确认游戏退出时会重写 `ACShadows.ini`
（mtime 比存档晚一分钟）。已备好两个脚本：

| 脚本 | 作用 |
| --- | --- |
| `acst/ini-watch.sh [最大份数] [超时秒]` | 盯住 `[Scalability_Custom]` + `Profile` 的指纹；只在该段变化时存快照，文件名 `<Profile>-<指纹前8位>.ini`（同一套画质只会有一份，窗口位置/FOV 之类的噪声不会触发） |
| `acst/ini-matrix.sh` | 把快照拼成「键 × 预设」矩阵，行尾 `*` 表示该键跨预设取值不同 |

```zsh
cd /Volumes/LexarSSD/Applications/acst
./ini-watch.sh 14 3600 &     # 后台盯盘（会先存一份当前基线）
# 然后在游戏里把 6 档预设从低到高各切一次，每次切完退出
./ini-matrix.sh              # 拼表
```

跑完 6 次即可拼出完整的"键 × 档位"矩阵；**每列的最大值就是该键的上限**。
**注意**：`Profile` 会从 `macos_custom` 变成预设名，说明自定义档被预设覆盖——
要保留当前自定义配置，先备份（已在 `backup-saves-20261106-233411/ACShadows.ini`）。

**已知噪声（已处理）**：游戏不只退出时写 ini——改 FOV、拖窗口也会写。实测 23:54 那次
`FOVScale` 1.0→0.9、窗口位置变化就触发过一次误存，所以指纹只算画质段，不算这些字段。

### 1.3.3 另一个容易搞错的点

`[Scalability]` 里的 `Profile` 只是"当前用的是哪套"的标签，**真正生效的是
`[Scalability_Custom]` 段里的键值**。切到预设后这个段会被整体重写，
所以"改 ini 强行插值"只有在 `Profile=macos_custom` 时才可能被采纳——尚未验证游戏启动时会不会
用它覆盖；若要验证，改一个明显字段（如 `terrain_gpuscatter=4`）看画面散落密度是否变化。

### 1.4 没有三件套

Windows 版是 `ACShadows[ManualSave0N].save` + `.save.upload` + `.save.delete` 三个文件；
**Mac 版每个槽位只有一个 `.sav`**，没有 upload/delete 旁文件，也没有 `ACShadows[...]` 命名。

---

## 2. Mac 存档格式：明文 ACDB 容器

`xxd` 头部（`ManualSave01.sav`）：

```
00000000: acdb fe00 3600 0000 0400 0000 3700 0000  ....6.......7...
00000010: 5200 995e 7118 01aa 1d7d 9f91 e589 0000  R..^q....}......
00000020: 24f7 0800 33aa fb57 99fa 0410 0300 0500  $...3..W........
00000030: 0004 0001 5334 0000 0000 0400 27d0 7340  ....S4......'.s@
```

### 2.1 头部字段

| 偏移 | 值 | 含义（推断） |
| --- | --- | --- |
| 0x00 | `AC DB FE 00` | 容器魔数（0x00FEDBAC） |
| 0x04 | 54 (0x36) | 头部/版本长度 |
| 0x08 | 4 | 版本号 |
| 0x0C | 52–55 | **记录条数** |
| 0x10 | 4 字节 | 存档 ID / 时间相关（每个档不同） |
| 0x14 | `71 18 01 AA 1D 7D 9F 91` | **固定 GUID，所有存档一致** |
| 0x1C | ~34–35k | 计数类字段 |
| 0x20 | ~570–590k | 逻辑大小类字段 |
| 0x24 起 | — | 记录流 |

### 2.2 记录流

每条记录以固定 8 字节魔数开头：

```
33 AA FB 57 99 FA 04 10
```

`ManualSave03.sav` 里有 **61 处**该魔数（对应 55 条记录 + 其他出现），
候选 PC 档里有 **58 处**。记录内部结构：

```
33 AA FB 57 99 FA 04 10 | 03 00 05 00 | 00 04 00 01 | <id/len> | ...
```

Mac 档第一条：`... | 53 34 00 00 | 00 00 04 00 | 27 D0 73 40 8C 06 00 34 4D 88 1C 61 ...`
PC 解密档第一条：`... | 65 34 00 00 | 00 00 04 00 | 5A EB D6 A2 8C 06 00 34 5F 88 1C 09 ...`

两者在 `8C 06 00 34` 位置结构相同，但 id/长度与后续数据不同。

记录体内可见**明文**字段名，例如 `PlayerLevel`（`ManualSave02.sav` 0x261F5 附近）。

---

## 3. PC 存档与 Mac 存档的差异

来源样本：`~/Downloads/100% SaveFile New Game Plus GOLD KATANAS Altair-720230/ACShadows[ManualSave02].save`
（1,054,433 字节）

### 3.1 外层

```
00000000: 2400 0000 0000 0000 ... (36 字节头)
00000020: 0000 0000 f6a0 361e db75 5169 ...  ← 0x24 起为密文
```

- PC：**36 字节头 + 加密数据**
- Mac：**直接是 ACDB 容器**（无外层加密壳）

### 3.2 ACST 处理后

用 ACST 处理（Decryption ID 自动检测、Encryption ID 留空）后，同一文件在 `0x24` 之后
出现 `00 00 00 00 AC DB FE 00 36 00 00 00 ...`，即 **ACDB 魔数出现在 0x28**。

说明：ACST 只解开了外层（36 字节壳），**记录体仍然保持 PC 侧格式**。

### 3.3 结构差异汇总

| 项 | PC 转换档 | Mac 原档 |
| --- | --- | --- |
| 容器魔数 | `AC DB FE 00` @0x28 | `AC DB FE 00` @0x00 |
| 0x10 字段 | `17 DB 98 22` | `52 00 99 5E` |
| 记录魔数出现次数 | 58 | 61 |
| 记录条数 | 52 | 55 |
| 明文 `PlayerLevel` | **无** | 有 |
| 可读 token 交集 | **仅 22 个**（且多为巧合串，如 `===`、`<Unknown>`） | — |
| 文件大小 | 1.05 MB | 168 KB |

---

## 4. 实测：直接替换会被判损坏

按 mod 页面思路（转换 → 改名 → 覆盖对应槽位）在 Mac 上试过：

1. 从解密结果里从 `0x28` 截取 ACDB，写成 `ManualSave03.sav`
2. 覆盖 `~/Library/Autosave Information/saves/ManualSave03.sav`
3. 启动游戏 → 读档界面右上角报错：

```
儲存檔已毀損
0x82000002
```

同界面里用户自己的档正常（`痛苦與承諾 / 2026-10-25 20:25:16 / 1 小时 40 分 12 秒 / 奈緒江 Lv4 / 和泉攝津`）。

**结论**：`0x82000002` 不是头部字段问题（改 0x10/0x0C 无用），而是记录体内容校验失败：
候选档的记录仍按 PC 侧账号密钥加密/混淆，Mac 版读的是明文 ACDB 记录。

---

## 5. ACST（ACSaveTool）事实

来源：`linuslin0/ACST`，release 2.6.1，`ACSaveTool_x64.exe`（Windows 10+ x64，需 Wine/CrossOver）。

README 要点：

- 功能是 **在不同 encryption ID 之间转换存档**，不是编辑器
- 支持作品列表包含 **Assassin's Creed Shadows**，其 ID 类型为 **Account ID**
- 流程：打开存档 → 选/自动识别游戏 → 填 Decryption ID（或勾 Detect）→ 填 Encryption ID → Convert
- 转换前会把原文件备份到 `acst_backup/`
- 提示转换后启动游戏前要临时关闭云存档同步

本机验证：

- 在本机 CrossOver（`/Applications/CrossOver Preview.app`）用 `WINE11` 容器运行
- 输出日志：`推測遊戲名稱: Assassin's Creed Shadows ... 完成`（0.024s）
- 说明**游戏识别没问题**，问题在 ID 与记录格式

### 5.1 Ubisoft Account ID（本机）

从游戏 WebKit 缓存中 `/v3/users/me` 的响应里找到：

```
userId:        79ffe174-90e6-4c67-9c32-72162eb84dc6
username:      Frank3333322222
nameOnPlatform: brave.cactus
```

注意不要混用：

- `spaceId=0a706b37-4b88-4437-b8f4-4ed2458c9518`、`applicationId=20adeb9c-6dad-404e-af1e-b12b4594e86e` 是服务空间/应用 ID
- 存档 `PlayerLevel` 附近的 `b4b8daec-…` / `4c4db86e-…` 是实体/存档 GUID

---

## 6. 为什么"换个账号 ID 再转换"也救不了

ACST 的输出仍然是 **PC 布局**（外层 36 字节壳 + 加密记录）。Mac 版要的是
**无壳 + 明文记录** 的 ACDB。换句话说：

- 换 encryption ID：改的是 PC 外层/记录密钥 → 输出还是 PC 档
- 想给 Mac 用：要么拿 Mac 原生存档，要么重写一个"PC 记录解密 → Mac ACDB 重打包"的转换器

目前**未发现** ACST 提供"输出为明文 ACDB"的选项。

---

## 7. 安全与回滚

改动前备份（均已存在）：

| 备份 | 内容 |
| --- | --- |
| `acst/backup-saves-20261031-224221/` | 最初 9 个 `.sav` |
| `acst/backup-saves-20261106-233411/` | **11 个 `.sav` + `Options.sav` + `ACShadows.ini`**（2026-11-06 23:34，12 个 sav 全部 sha256 校验一致） |
| `acst/backup-unsandbox-*/` | 迁移到新目录前的 `Options.sav` |
| `acst/backup-webkit-*/` | WebKit 缓存（含登录会话） |

整目录回滚：

```zsh
cp -p "/Volumes/LexarSSD/Applications/acst/backup-saves-20261106-233411"/*.sav \
      "$HOME/Library/Autosave Information/saves/"
```

单档回滚示例：

```zsh
cp "/Volumes/LexarSSD/Applications/acst/backup-saves-20261031-224221/ManualSave03.sav" \
   "$HOME/Library/Autosave Information/saves/ManualSave03.sav"
```

---

## 8. 可复现命令

```zsh
# 看头部
xxd -l 64 "$HOME/Library/Autosave Information/saves/ManualSave01.sav"

# 数记录魔数
LC_ALL=C grep -a -c $'\x33\xaa\xfb\x57\x99\xfa\x04\x10' <file>

# 提取 ACST 解密后的 ACDB（magic 在 0x28）
python3 - <<'EOF'
data = open("ACShadows[ManualSave02].save", "rb").read()
i = data.find(b"\xac\xdb\xfe\x00")
open("ManualSave03_candidate.sav", "wb").write(data[i:])
EOF
```

---

## 9. 记录内部结构（2026-11-07 实测，`saveparse/acdb.py`）

### 9.1 记录头两种形态

魔数之后：

| 偏移（相对记录起点） | 字段 | 说明 |
| --- | --- | --- |
| +0x08 | `03 00 05 00` | 版本，恒定；`acdb.py` 用它过滤误命中 |
| +0x0C | `00 04 00 <flag>` | `flag=0` 原始体 / `flag=1` 序列化体 |
| +0x10 | u32 A | `flag=0`=载荷长度；`flag=1`=载荷长度 |
| +0x14 | u32 B | `flag=1` 的逻辑容量；`B==0x40000` 表示"大对象流" |
| +0x18 | u32 | checksum |
| +0x1C | u32 | 类型值，形如 `0xNN00068c` |
| 头部长度 | — | `flag=0` → 36 字节；`flag=1` → 44 字节 |

### 9.2 载荷**大多未压缩**（推翻早期 Oodle 假设）

早期因为 `gzip` 比值 ≈0.94–1.0、LZ4/deflate 都解不开，曾判定记录体是 Oodle2 压缩。
**这个结论只对了一小部分**，准确表述是：

| 载荷首字节 | 记录数 | 性质 |
| --- | --- | --- |
| `0x00` | 27 | **明文**序列化流，内部可直接读到 `PlayerLevel`、GUID、属性名哈希 |
| `0x40` | 4 | **Oodle2 压缩**（rec13/14/24/37），静态解不开，见 9.10 |

绝大多数记录是数值密集的原始序列化数据：gzip 比值≈1.0 是因为数值密集，
而不是压缩——判据是**内部能否读到明文**（详见 9.10 的判定表）。

### 9.3 类名哈希 = CRC32(类名)

载荷 **+3** 起 4 字节是类名 CRC32（小端）。验证：

```
CRC32("InventorySaveData") = 0x28898cc6   # 与档内字节精确匹配
```

于是静态枚举二进制里所有"类型注册"调用点，就能建出 `哈希 → 类名` 表，
再反查每条记录的类名——**不需要运行时 hook**。

枚举方式：`tools/findcall`（`bl` imm26 扫描）定位所有对类型注册函数
`0x10046df90` 的调用（本作 486 处），配合 Python 解出每处的类名常量 + CRC32。

### 9.4 已翻译的记录类名（ManualSave06 样本）

| 记录 | 类名 |
| --- | --- |
| 0 | `SaveGameFile`（自描述类型字典：`ClassDataDesc`/`PropertyDataDesc`/`EnumDataDesc`/`TypeDataDesc`） |
| 3 | `AssassinSaveGameMetaData` |
| 12 | `AssassinProgressionSaveData`（含 `InventorySaveData` / `MultiLoadoutSaveData`） |
| 22 | `EngineSaveGameData` |
| 40 | `OnlineGameSaveData` |
| 59 | `WorldLogicCompletionSaveDataObject` |
| — | `EngineSaveGameMetaData` / `AssassinCommunitySaveData` 等 |

**注意（2026-11-09 已推翻）**：早期认为「记录 0 是紧凑二进制、无字符串字段名，静态路径到此为止」。
实际是 **CRC32(名字) 哈希表**，用二进制的字符串表反查就能完整翻译（见 9.6）。

### 9.5 差分法：信号 vs 噪声

定位"某个操作改了哪些字节"的正确姿势是**两两差分 + 噪声对照**：

| 差分 | 含义 | 结果 |
| --- | --- | --- |
| `ManualSave07 → 08`（换帽子） | 信号 | rec3=209B / rec22=299B / rec59=91B 变化 |
| `ManualSave08 → 09`（什么都不做，空存） | 噪声 | 同样三条记录也变（1–3B） |

**没有噪声对照就会把"每次存档都会变的元数据"误判成装备字段。**
本项目就因此撤回过一次结论：曾把 rec12 `+0x82e` 的 4 字节当成帽子 ID，
跨五份存档发现空存也会变（`0x43efd9c1 → 0x43eefd14`），已作废。

### 9.6 装备 schema 已解出（2026-11-09，Ghidra 反编译）

**装备槽位描述符**：`FUN_101d36244` 在静态初始化时构造 6 个槽位描述符：

| 槽位 | 描述符全局 | 标志 (param_3,param_4) | 含义 |
| --- | --- | --- | --- |
| `Body` | `DAT_10d438860` | 1,1 | 身体护甲（带 Level） |
| `Head` | `DAT_10d4388a0` | 1,1 | 头部护甲（带 Level） |
| `WeaponSlot1` | `DAT_10d4388e0` | 1,1 | 主武器（带 Level） |
| `WeaponSlot2` | `DAT_10d438920` | 1,1 | 副武器（带 Level） |
| `Horse` | `DAT_10d438960` | 0,0 | **坐骑**（无 Level） |
| `Trinket` | `DAT_10d4389a0` | 0,0 | **饰品/护符**（无 Level） |

坐骑与饰品不参与等级成长，所以 `+0x2b`（序列化 Level 的开关）为 0。
这条差异是用户确认的游戏内事实（2026-11-09），与反编译结果完全吻合。

**描述符构造器** `FUN_101d375f4(out, slotName, f1, f2)`，每条 0x38 字节：

```
+0x00  "Rarity"
+0x08  "Id"
+0x10  "Stats"
+0x18  "Level"
+0x20  "VisualId"
+0x28  u8 恒 1        （消费侧：用 Rarity）
+0x29  u8 恒 1        （消费侧：用 Id）
+0x2a  u8 恒 1        （消费侧：用 Stats）
+0x2b  u8 = param_3   （消费侧：用 Level；角色槽=1，Horse/Trinket=0）
+0x2c  u8 = param_4
+0x30  char* slotName
```

**消费侧** `FUN_101d378d0(..., descriptor, ...)` 按 `+0x28~+0x2b` 的开关，
用 `FUN_101d38870(out, descriptor+0x30, descriptor+offset)` 组合成键——
即**「槽位名 + 属性描述符」的键值对**。

**存档用 CRC32(名字) 作键**（2026-11-09 实测，决定性）：
把 `scimitar` 全部 260,276 个可读串算 CRC32，反查存档，`ManualSave06` 命中 1998 处。
记录 0 的"紧凑二进制"其实就是哈希表，翻译后即是完整类型字典：

```
+0x00014  SaveGameFile
+0x00075  Platform
+0x00113  ClassDataDesc         +0x0013b  PropertyDataDesc
+0x00449  LoadoutSaveData       +0x00c40  ItemSlotsAttributesSaveData
+0x00e65  MultiLoadoutSaveData  +0x01e80  LoadoutItemSaveData
```

**rec12（`AssassinProgressionSaveData`）内的库存层级**（`tools/namemap.py --rec 12`）：

```
+0x00316  InventoryProgressionSaveData
+0x00326  InventorySaveData
+0x0032f  ItemDataSaveData
+0x00343  InventoryItemInstanceSaveData
+0x0036a  InventoryCategorization
+0x0038d  InventoryItemAttributesSaveData
+0x003a0  ItemSlotsAttributesSaveDataMapping
+0x0041f  ItemStateData
+0x006b1  LoadoutItemSaveData
```

`LoadoutItemSaveData` 类型哈希出现在载荷 `+0x6b1`（`12 6a ee 52` → `0x52ee6a12`），
即装备槽的实际数据块。

### 9.7 `LoadoutItemSaveData` 字段布局已还原（2026-11-09）

**类描述符**（`scimitar` 的 `__DATA`，位于 `0x10d5d7ec0`，有文件备份可直接读）：

```
+0x00  &memberA (Slot 描述符)
+0x08  &memberB (ItemID 描述符)
+0x10  &memberA (成员数组基址，步长 0x58)
+0x28  0x52ee6a12_00000001   类哈希 + 版本 1
+0x30  0x10                  结构体大小 = 16 字节
+0x68  FUN_1033aeba4         注册器（把成员挂到 struct+8 / struct+0）
+0x88  FUN_1033aec6c         构造器
+0xA8  FUN_107efef14         序列化器
```

**成员描述符**（每个 0x58 字节，紧邻存放）：

| 成员 | 描述符地址 | 类型哈希 | 名字 | 结构内偏移 | 宽度 |
| --- | --- | --- | --- | --- | --- |
| memberB | `0x10c5c8908` | `0x0c3c8f59` | **`Slot`** | `+0x00` | 8 |
| memberA | `0x10c5c88b0` | `0x893a928f` | **`ItemID`** | `+0x08` | 8 |

**名字来源**：`CRC32("Slot") = 0x0c3c8f59`、`CRC32("ItemID") = 0x893a928f`，
与二进制里找不到这些字符串并不矛盾——成员标识符在编译时就被哈希，字符串本身被优化掉了。
判定方法：拿常见标识符词表逐个算 CRC32 碰撞（`Slot`、`ItemID` 都是一次命中）。

**最终结构**（`LoadoutItemSaveData`，16 字节）：

```c
struct LoadoutItemSaveData {
    ??? Slot;      // +0x00, 8 字节
    uint64_t ItemID; // +0x08, 8 字节
};
```

**存档中的实例**：`rec12` 里有 3 个（`+0x6b1` / `+0x2e48` / `+0x5aa9`），
每个都以类哈希 `12 6a ee 52` 开头，紧随其后是 Slot 字段的类型标记
`b2 9a 4c 9e`（`0x9e4c9ab2`，名字仍未破解），再是 8 字节值。
三个实例的标记与值顺序不一致，说明编码是**变长/打包 TLV**，不是固定偏移。

### 9.8 名哈希破译的边界（2026-11-09）

`0x9e4c9ab2`（`Slot` 成员的元素类型，类大小 12 字节）**未能破解**。已排除的可能：

| 方法 | 结果 |
| --- | --- |
| 三个二进制全部可读串算 CRC32 | 0 命中 |
| 滑窗扫描（任意子串 3..48 字符，`tools/findhash`） | 0 命中 |
| 常见标识符 1~5 层组合（约 180 万种） | 0 命中 |
| 大小写变体 / `m_` `C` `U` `F` 前缀 / 终止符 / 长度前缀 | 0 命中 |
| 模板写法（`Array<Slot>` 等） / 父类名拼接 / 版本后缀 | 0 命中 |

**为什么破解不了（诊断结论）**：

统计 19,592 个 `+0x08` 非零的成员描述符，用二进制字符串表反查，
可解析率只有 **17.0%**（随机基线约 0.006%）。所以：

- 该字段**确实是名字哈希**（17% 远高于随机）；
- 但 **83% 的标识符在编译期就被哈希、字符串从未输出**（constexpr 化后被优化掉）；
- `Entity` / `UIString` / `SoundInstanceLegacy` 这类能解析的，是因为它们另外还作为日志/UI 字符串存在。

`0x9e4c9ab2` 属于那 83%，**静态不可恢复**——除非用词表暴力猜中原本的标识符。

**它不影响已知结论**：`Slot` 字段的元素类型是 12 字节结构体，
这个事实来自类描述符的 `+0x10 = 0x0C`，与名字无关。

**已经付出的工具**：`tools/findhash`（滑窗 CRC32 搜索，C 实现），
换任何"字符串紧凑存放"的二进制都能复用来找哈希对应的名字。

### 9.9 rec3 的换帽落点（2026-11-09 实测）

`rec3 = AssassinSaveGameMetaData`（489 字节）。流结构是
`[属性名哈希:4][值...]` 的序列，所以能直接用名字哈希定位字段：

```
+0x0003  AssassinSaveGameMetaData   (类哈希，记录 +3 处)
+0x000f  Location
+0x0013  UIString                   (Location 的值就是 UIString)
+0x003f  UIStringEx
+0x0080  PlayerLevel
+0x009d  DifficultyMode
+0x00ab  AppPlayTime
+0x00af  AppPlayTimeSaveData
+0x01d9  HubRedSaveMetaData         → 值 = f5 01 00 00 8e 02 00 00 (501, 654)
```

**换帽实际改动的位置**（M07 帽A → M08 帽B；M09 与 M08 全同）：

| 位置 | M07 | M08 | 形态 |
| --- | --- | --- | --- |
| `+0x00f9` | `b2` | `2e 31 00` | 值变长 +2 字节 |
| `+0x0196` | `13` | (删除) | 值消失 −1 字节 |
| `+0x0175` | `cb 44 88` | `43 45 48` | 原地变化 |
| `+0x0182` | `15` | `14` | 原地变化 |
| `+0x01c7` | `01` | `02` | 原地变化 |
| `+0x01d1` | `08 e0 92` | `00 40 90` | 原地变化 |

其中 `+0x00f9` 与 `+0x0196` 是**净增长 +1 字节**（488 → 489），
其余是定长位段变化——说明这一段是**位打包 + 变长整数**混合编码，字段不按字节对齐。

**重要否证**：`HubRedSaveMetaData`（`+0x1d9`）在两版里**完全相同**，
所以它不是外观数据；真正的外观字段落在 `+0x00b3..+0x01d9` 这段约 298 字节里。

**为什么这段的名字查不到**：该区间内所有 4 字节窗口都匹配不到可读字符串，
说明这些属性名属于 9.8 那 83%「编译期哈希、字符串未输出」的标识符。
`namemap` 在这里只能给出偏移，给不出名字。

### 9.10 rec13/14/24/37 的压缩标记（2026-11-09 实测）

**载荷首字节就是压缩标记**。对全部 61 条记录统计：

```
首字节 0x00 → 27 条，全部能查到 3~4 个属性名哈希（明文）
首字节 0x40 →  4 条（rec13/14/24/37），查不到名字（压缩）
```

两组完全不重叠，判定成立。

| 记录 | 类 | 载荷 | B（解压后） | 压缩比 |
| --- | --- | --- | --- | --- |
| rec13 | ? | 38,743 | 262,144 | 14.8% |
| rec14 | ? | 11,672 | 262,144 | 4.5% |
| rec24 | ? | 7,245 | 179,669 | 4.0% |
| rec37 | ? | 7,907 | 80,344 | 9.8% |

记录头 `B` 字段对这几条正好是**解压后大小**（rec13/14 恰好 0x40000 = 256 KB 分块）。

**已排除的算法**（`tools/trydecomp.py`，四个记录全部失败）：
LZ4 block、raw deflate、zlib、lzma、bz2。
`scimitar` 静态链接 **Oodle2**（字符串里有 `OodleLZ_Decompress` ×14、
`newlz_arrays_*.cpp`），且 Oodle 无公开格式规范、非导出符号，
**这些记录静态解不开**。

**对结论的影响**：无。装备布局（`LoadoutItemSaveData` 16 字节）、
槽位 schema、rec3 的外观落点都来自明文记录（rec0/3/12），不依赖这四条压缩流。

### 9.11 元数据类的成员表与流格式（2026-11-09）

**定位方法**：类名字符串的 xref 直接给出注册器（5 秒一次）。

```
"AssassinSaveGameMetaData" @ 0x10a8ee995 → FUN_1035afc48
"HubRedSaveMetaData"       @ 0x10a887f10 → FUN_101de72d8
```

**`AssassinSaveGameMetaData` 成员表**（`FUN_10046df90` 注册类名后按序注册）：

| 结构内偏移 | 注册方式 | 备注 |
| --- | --- | --- |
| `+0x10` | `FUN_10097a268` | 特殊类型 |
| `+0x28` / `+0x30` | `FUN_10079bea0` | 容器类（数组/映射） |
| `+0x78` / `+0x80` / `+0x88` | `FUN_10079bea0` | 同上，共用一组类型描述符 |
| `+0x90` / `+0x98` | `FUN_101473810` | |
| `+0xa0` | `FUN_10020b7b8` | 容器（带元素类型） |
| `+0xa8` | `FUN_10018b974(obj, 0xedb19556, …)` | **`DifficultyMode`** |
| `+0xac` / `+0xb0` | `FUN_10020a3e8` | |

`FUN_101de7430` 在开头调用，是**注册基类**——`Location`/`PlayerLevel`/`AppPlayTime`/
`UIString` 等属性来自基类，不在本表内。

**`HubRedSaveMetaData` 成员表**（只有 2 个）：

| 偏移 | 注册方式 |
| --- | --- |
| `+0x10` / `+0x18` / `+0x60` | `FUN_10079bea0` |
| `+0x78` / `+0x7c` | `FUN_10020a3e8`（两个 u32） |

**交叉验证成立**：rec3 尾部 `HubRedSaveMetaData` 的值是 8 字节
`f5 01 00 00 8e 02 00 00` = `501, 654`，正好对应 `+0x78` / `+0x7c` 两个 u32。
**说明"注册器成员表 → 存档字段"这条路径是可靠的。**

**流格式（部分解出）**：

```
[属性名哈希:4][值...]
```

- 值是**嵌套对象**时，直接跟其**类型哈希**。例：`Location`(`+0xf`) → `UIString`(`+0x13`)
- 叶子值带长度前缀：`00 00 <u16 长度> 0b <数据>`。
  例：`PlayerLevel` 后是 `00 00 07 00 0b`（长度 7）、`UIString` 后是 `00 00 16 00 0b`（长度 0x16）

有了成员表，就能把 `+0x00b3..+0x01d9` 那 298 字节按 `+0x10`/`+0x28`/`+0x78` 等
容器成员逐段切开，不必再猜名字。

**实测：切分卡在"容器内元素编码"（2026-11-09）**

试按上面的 TLV 规则走查 `+0xb3..+0x1d9`（294 字节），结果：

```
`00 00 <u16 len> 0b` 模式：出现 1 次，长度合法 0 个
对照 0x00..0xb3（已知字段区，179 字节）：同模式出现 2 次
```

**这段不遵循叶子值的长度前缀格式。** 字节统计佐证它是位打包数组：

| 指标 | 值 |
| --- | --- |
| 最高频字节 | `0x00`×33、`0x01`×20、`0x05`×18、`0x0b`×8 |
| `>0x80` 占比 | 17% |
| 长度 | 294（不是常见元素尺寸的整数倍） |

再加上实测事实：**一次换帽改动分散在 6 处**
（`+0xf9` / `+0x175` / `+0x182` / `+0x196` / `+0x1c7` / `+0x1d1`），
不是连续一段——这与"某条记录整体替换"不符，只符合"位段被重新打包"。

结论：**成员表能定位容器边界，但容器内部的元素编码还没解出来**。

### 9.12 仍未解决

- **容器内元素编码**（唯一的剩余技术阻塞）：`FUN_10079bea0`（16 KB）是数组编码的
  唯一定义处，需逐段读反编译代码才能解出。这是 rec3 外观数据与 rec12 库存值提取的共同前提。
- `0x9e4c9ab2` 的标识符名（静态不可达，见 9.8）。
- 存档里 `Slot`/`ItemID` 的实际值提取：依赖上面第一条。
- 外观（帽子等 cosmetic）不落在 `rec12`，而在 `rec3 = AssassinSaveGameMetaData`
  的 Hub 视觉元数据区（`0xfd..0x1e7`，`HubRedSaveMetaData` 在 `+0x1d9`）。
  判据：`rec12` 换帽只变 8 字节（其中 3 字节空存也变），而 `rec3` 变 210 字节、空存只变 1 字节。
- rec13/14/24/37 的内容（Oodle2 压缩，静态不可解，见 9.10）。

### 9.13 工具用法

```zsh
./acdb.py list    <file.sav>                 # 全部记录：偏移/尺寸/flag/长度/类型/kind
./acdb.py dump    <file.sav> <n> [--hex]     # 单条记录载荷
./acdb.py raw     <file.sav> <n> <out>       # 导出载荷
./acdb.py strings <file.sav> [n]             # 记录内可读串 + 偏移
./acdb.py diff    <A.sav> <B.sav>            # 记录级差异 + 变化字节区间
./tools/namemap.py <scimitar> <file.sav> [--rec N] [--grep RE]
                                             # 用二进制字符串表反查存档里的 CRC32 名字
./tools/findhash <binary> <hash_hex> [maxlen]  # 滑窗找 CRC32(任意子串)==目标 的名字
```

## 10. 待办

### 已完成（2026-11-09）

- [x] 差分两份同账号不同进度的 Mac 存档，摸出 ACDB 记录类型表（第 9 节）
- [x] 确认记录体压缩状态：27 条明文 + 4 条 Oodle2 压缩（9.2 / 9.10）
- [x] 建立 `哈希 → 类名` 表（CRC32 反查，`tools/classhash.py`）
- [x] 用 Ghidra 反编译解出装备槽位 schema（Body/Head/WeaponSlot1/2/Horse/Trinket）
- [x] 确认存档以 CRC32(名字) 为键，可全量翻译（`tools/namemap.py`）
- [x] `LoadoutItemSaveData` 字段布局：16 字节 = `{Slot@0, ItemID@8}`（9.7）
- [x] rec3 换帽落点定位到 6 个字节（9.9）
- [x] 元数据类成员表：`AssassinSaveGameMetaData` / `HubRedSaveMetaData`（9.11）
- [x] 流格式：`[名字哈希][嵌套类型哈希 | 00 00 len 0b 值]`（9.11）
- [x] 成员表交叉验证：`HubRedSaveMetaData` 两个 u32 对上 501/654（9.11）
- [x] 确认 294 字节区域是位打包数组，非记录列表（9.11 末）

### 剩下的都是硬边界

| 项 | 原因 | 需要的条件 |
| --- | --- | --- |
| **容器内元素编码**（唯一阻塞） | 位打包，规则在 `FUN_10079bea0`（16 KB） | 逐段读反编译代码 |
| `0x9e4c9ab2` 等 83% 的标识符名 | 编译期哈希、字符串未输出 | 猜中原始标识符，或运行时读 bss 描述符 |
| `Slot`/`ItemID` 实际值提取 | 依赖容器元素编码 | 同上 |
| rec13/14/24/37 内容 | Oodle2 商业编码器 | 游戏运行时的 `OodleLZ_Decompress` |
| 外观数据字段名 | 同第一条 | 同第一条 |

### 可选方向

- [ ] 评估写一个 PC→Mac 转换器（需先逆出 PC 记录加密方案）
- [ ] 或改走"Mac 原生存档"路线（明文容器，改名即用，无需转换）
