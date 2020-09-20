# 如何使用LLDB调试程序

## 概述

**为什么使用 LLDB 而不是 GDB?**

调试 C 程序，第一个想到的就是 LLDB。然而 GDB 在 macOS 上有很多问题，比如处于安全性考虑，如果一个进程要访问另一个进程的内存空间，需要提供 codesign 签名。解决了签名问题，又出现无法加载动态库、找不到调试信息的问题，对此众说纷纭，总而言之，GDB 对新版本的 macOS 支持的不好，而苹果也不准备提供定制版本，因为有更好的替代者，LLDB。

**LLDB 命令的语法有其通用结构**

```
<command> [<subcommand> [<subcommand>...]] <action> [-options [option-value]] [argument [argument...]]
```

其中：
- `<command>`(命令) 和 `<subcommand>`(子命令)：LLDB 调试命令的名称。命令和子命令按层级结构来排列：一个命令对象为跟随其的子命令对象创建一个上下文，子命令又为其子命令创建一个上下文，依此类推。
- `<action>`：我们想在前面的命令序列的上下文中执行的一些操作。
- `<options>`：行为修改器 (action modifiers)。通常带有一些值。
- `<argument>`：根据使用的命令的上下文来表示各种不同的东西。

## 用 LLDB 来调试一段 C 程序

### 0. 编译代码

先把 C 程序编译成可执行文件，一定要记得带 `-g` 参数。

```bash
gcc -g null.c -o null
```

### 1. 指定需要调试的程序

```bash
lldb null
```

对于运行中的程序，可以：

```bash
lldb                            # 先启动 lldb
process attach --pid 123        # 通过进程号，简写：pro att -p 123
process attach --name Safari    # 通过应用名，简写：pro att -n Safari
```

### 2. 设置断点

看代码：`l` or `list`

```bash
l                   # =list
list ArrayUtils.c   # 看其他文件
l 3                 # 看前3行
l main              # 看main函数
```

下断点：`breakpoint`

```bash
# 根据文件名和行号下断点
(lldb) breakpoint set --file DebugDemo.c --line 10

# 根据函数名下断点
# C函数
(lldb) breakpoint set --name main

# C++类方法
(lldb) breakpoint set --method foo
```

设置别名简化上述命令：

```bash
# 比如下面的这条命令
(lldb) breakpoint set --file DebugDemo.c --line 10

# 你就可以写这样的别名
(lldb) command alias bfl breakpoint set -f %1 -l %2

# 使用的时候就像这样就好了
(lldb) bfl DebugDemo.c 10
```

### 3. 编辑断点

```bash
(lldb) breakpoint list          # 查看断点列表
(lldb) breakpoint disable 2     # 禁用断点
(lldb) breakpoint enable 2      # 启用断点
(lldb) breakpoint delete 1      # 删除断点
```

### 4. 启动 debug

```bash
(lldb) run              # run命令就是启动程序
(lldb) next             # 下一步 (next 或 n)
(lldb) step             # 步入(step 或 s)
(lldb) finish           # 步出(finish)
(lldb) continue         # 继续执行到下一个断点停, 后面没有断点的话就跑完了（continue 或 c）
```

查看变量、跳帧查看变量：

```bash
# 使用po或p
(lldb) po result_array  # po一般用来输出指针指向的那个对象
(lldb) p result_array   # p一般用来输出基础变量。普通数组两者都可用

(lldb) bt               # 查看所有帧(bt)
(lldb) frame select 1   # 跳帧（frame select）
(lldb) frame variable   # 查看当前帧中所有变量的值（frame variable）
```


---

参考：
[1] [使用LLDB调试程序](https://casatwy.com/shi-yong-lldbdiao-shi-cheng-xu.html)
[2] [LLDB调试器使用简介](http://southpeak.github.io/2015/01/25/tool-lldb/)

