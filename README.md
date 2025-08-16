# TsMixinTool

A UE5 plugin for the PuerTS plugin. Provides two modes to automatically initialize the `JsEnv` via the plugin's subsystem and allows generating TypeScript scripts with a single click.

## Usage

1. Copy the `TsMixinTool` folder to `{ProjectName}\Plugins`.  
2. Compile the project and enable the plugin.  
3. Copy all files from `TsMixinTool\Content\COPY_TO_TS_ROOT` to your TypeScript root folder.  
4. Create a Blueprint from a custom C++ class or a UE class.  
5. In Blueprints:  
   - **Default mode**: Create functions that start with `TS_`.  
   - **Manager mode**: Create Event Dispatchers that start with `TS_`, then call the `Register to Ts Manager` node (usually the first one in `BeginPlay`).  
6. Right-click a Blueprint → `Generate TS Script`.  
7. Implement the generated TS script and compile it to JS.


# TsMixinTool

一个用于 PuerTS 的 UE5 插件，提供通过插件的 Subsystem 自动初始化 `JsEnv`的功能，并有两种模式管理TS脚本加载，可一键生成 TypeScript 脚本。

## 使用方法

1. 将 `TsMixinTool` 文件夹复制到 `{ProjectName}\Plugins`。  
2. 编译项目并启用插件。  
3. 将 `TsMixinTool\Content\COPY_TO_TS_ROOT` 下的所有文件复制到你的 TypeScript 根目录。  
4. 从自定义 C++ 类或 UE 类创建蓝图。  
5. 在蓝图中：  
   - **默认模式**：创建以 `TS_` 开头的函数。  
   - **Manager 模式**：创建以 `TS_` 开头的事件分发器（Event Dispatcher），然后调用 `Register to Ts Manager` 节点（通常放在 `BeginPlay` 的第一个节点）。  
6. 右键蓝图 → 选择 `Generate TS Script`。  
7. 实现生成的 TS 脚本并编译为 JS。