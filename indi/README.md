# INDI 核心库

[![Linux](https://github.com/indilib/indi/actions/workflows/linux.yml/badge.svg)](https://github.com/indilib/indi/actions)
[![Debian Packages](https://github.com/indilib/indi/actions/workflows/linux-packages.yml/badge.svg)](https://github.com/indilib/indi/actions)
[![MacOS](https://github.com/indilib/indi/actions/workflows/macos.yml/badge.svg)](https://github.com/indilib/indi/actions)
[![Visual Studio](https://github.com/indilib/indi/actions/workflows/windows-visual.yml/badge.svg)](https://github.com/indilib/indi/actions)
[![MinGW](https://github.com/indilib/indi/actions/workflows/windows-mingw.yml/badge.svg)](https://github.com/indilib/indi/actions)
[![PyIndi](https://github.com/indilib/indi/actions/workflows/linux-pyindi.yml/badge.svg)](https://github.com/indilib/indi/actions)

INDI 是一个用于天文仪器控制的标准。INDI 库是 [仪器中立设备接口协议](http://www.clearskyinstitute.com/INDI/INDI.pdf) 的一个开源 POSIX 实现。

INDI 核心库由以下组件组成：

1. INDI 服务器。
2. INDI 核心驱动：与设备通信的硬件驱动。支持许多设备，包括：

- 赤道仪
- CCD、CMOS、网络摄像头、单反相机（佳能、尼康、索尼、宾得等）。
- 调焦器
- 滤镜轮
- 自适应光学
- 圆顶
- GPS
- 气象站
- 控制器
- 辅助设备（开关、看门狗、继电器、光源、测量设备等）。

3. 客户端库：跨平台的 POSIX 和基于 Qt5 的客户端库。这些客户端库可以嵌入到第三方应用程序中，用于与 INDI 服务器和设备通信。

INDI 核心设备驱动默认随 INDI 库一起提供。

INDI 第三方驱动可在 [专用的第三方仓库](https://github.com/indilib/indi-3rdparty) 中找到，并由其各自的维护者维护。

了解更多关于 INDI 的信息：

- [功能](http://indilib.org/about/features.html)
- [发现 INDI](http://indilib.org/about/discover-indi.html)
- [支持的设备](http://indilib.org/devices/)
- [客户端](http://indilib.org/about/clients.html)

# 构建

## 安装前置条件

在 Debian/Ubuntu 上：

```bash
sudo apt-get install -y \
  git \
  cdbs \
  dkms \
  cmake \
  fxload \
  libev-dev \
  libgps-dev \
  libgsl-dev \
  libraw-dev \
  libusb-dev \
  zlib1g-dev \
  libftdi-dev \
  libjpeg-dev \
  libkrb5-dev \
  libnova-dev \
  libtiff-dev \
  libfftw3-dev \
  librtlsdr-dev \
  libcfitsio-dev \
  libgphoto2-dev \
  build-essential \
  libusb-1.0-0-dev \
  libdc1394-dev \
  libboost-regex-dev \
  libcurl4-gnutls-dev \
  libtheora-dev
```

## XISF 支持

要在 INDI 中启用 [XISF 格式](https://pixinsight.com/xisf/) 支持，您需要构建或安装 [libxisf](https://gitea.nouspiro.space/nou/libXISF) 包。

```bash
sudo apt-add-repository ppa:mutlaqja/ppa
sudo apt-get -y install libxisf-dev
```

## 创建项目目录

```bash
mkdir -p ~/Projects
cd ~/Projects
```

## 获取代码

要构建 INDI 以运行驱动程序，建议执行快速浅克隆，这将节省大量带宽和空间：

```bash
git clone --depth 1 https://github.com/indilib/indi.git
```

另一方面，如果您计划提交 PR 或参与 INDI 驱动程序开发，则建议进行完整克隆：

```bash
git clone https://github.com/indilib/indi.git
```

最好在您自己的个人存储库中创建 indi 的分支，而不是直接从根 indi 克隆。

## 构建 indi-core（cmake）

```bash
mkdir -p ~/Projects/build/indi-core
cd ~/Projects/build/indi-core
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ~/Projects/indi
make -j4
sudo make install
```

## 构建 indi-core（脚本）

**或者**，您可以使用 `developer-build.bash` 脚本进行更快的构建，并减少对 SSD 或 HDD 的压力。

```bash
cd ~/Projects/indi
./developer-build.bash
```

默认情况下，此脚本在机器的 `RAM` 中构建 `indi-core`，即 `/dev/shm`。
但是，您可以使用 `-o` 选项更改目标构建目录，例如：

```bash
./developer-build.bash -o /path/to/new/build/dir
```

此外，此脚本会检查目标构建目录是否至少有 `512MB` 的可用内存，如果没有，则会中止。
您可以使用 `-f` 选项强制跳过此测试：

```bash
./developer-build.bash -f
```

此外，此脚本默认以 _并行_ 方式执行 `make`。
如果您遇到问题或需要使用更少的 CPU 核心，请使用 `-j` 选项进行调整。
例如，要禁用并行执行：

```bash
./developer-build.bash -j1
```

此脚本会创建一个名为 `build` 的软符号链接文件到目标构建目录。
这有助于通过简单地跟随符号链接更轻松地访问：

```bash
cd ~/Projects/indi/build
```

最后，您可以一次性给出所有选项和参数。
例如，如果您想在 `~/indi-build` 目录中构建，跳过内存检查，并使用 `8` 个核心运行 make，请使用以下选项调用脚本：

```bash
cd ~/Projects/indi
./developer-build.bash -o ~/indi-build -f -j8
```

## 构建 indi-core（Qt Creator）

如果您计划使用 Qt Creator 进行开发，请仍然按照此过程进行手动构建。然后在 QT Creator 中：

- 使用文件 - 打开文件或项目打开项目。
- 导航到 Projects/indi 并选择 CMakeLists.txt 文件。
- Qt Creator 将打开您的项目，但可能会错误地配置它，选择 Projects 选项卡并更改为您用于初始构建的 Projects/build/indi-core 目录。项目显示可能是空白的，但无论如何单击构建按钮（地质锤）。项目应该构建。

这个过程很容易出错，可能会发生各种微妙的事情，例如一切看起来都已构建，但您的新功能却不存在。

## 构建 indi-core（VS Code）

INDI 包含一个默认的 .vscode 目录，其中包含用于构建和启动项目的默认设置。首次在 VS Code 中打开项目后，安装所有推荐的扩展。您还需要安装以下软件包：

```bash
sudo apt-get -y install astyle clangd
```

在设置中启用 clangd 扩展。默认启动脚本调试 INDI 模拟器望远镜驱动程序。第一个驱动程序也是可以调试的驱动程序。

# 架构

典型的 INDI 客户端 / 服务器 / 驱动程序 / 设备连接：

    INDI 客户端 1 ----|                  |---- INDI 驱动程序 A  ---- 设备 X
                      |                  |
    INDI 客户端 2 ----|                  |---- INDI 驱动程序 B  ---- 设备 Y
                      |                  |                     |
     ...              |--- indiserver ---|                     |-- 设备 Z
                      |                  |
                      |                  |
    INDI 客户端 n ----|                  |---- INDI 驱动程序 C  ---- 设备 T


     客户端       INET       服务器       UNIX     驱动程序          硬件
     进程        套接字      进程        管道     进程             设备

INDI 服务器是公共网络访问点，一个或多个 INDI 客户端可以联系一个或多个 INDI 驱动程序。
indiserver 启动每个驱动程序进程，并安排它从其 stdin 接收来自客户端的 INDI 协议，并期望在驱动程序的 stdout 上找到发送给客户端的命令。
从驱动程序进程的 stderr 到达的任何内容都会复制到 indiserver 的 stderr。
INDI 服务器仅提供方便的端口、分叉和数据转发服务。如果需要，客户端可以直接运行并连接到 INDI 驱动程序。

# 支持

- [常见问题](http://indilib.org/support/faq.html)
- [论坛](http://indilib.org/forum.html)
- [教程](http://indilib.org/support/tutorials.html)

# 开发

- [INDI API](http://www.indilib.org/api/index.html)
- [INDI 开发者手册](https://docs.indilib.org/)
- [教程](http://indilib.org/develop/tutorials.html)
- [开发者论坛](http://indilib.org/forum/development.html)
- [开发者聊天](https://riot.im/app/#/room/#kstars:matrix.org)
- 示例驱动程序可在 examples 和 drivers/skeleton 目录下找到。它们可以用作驱动程序开发的起点。

### 代码风格

INDI 使用 [Artistic Style](http://astyle.sourceforge.net) 格式化所有 C++ 源文件。请确保将以下 astyle 规则应用于提交给 INDI 的任何代码。在 Linux 上，您可以创建 **_~/.astylerc_** 文件，其中包含以下规则：

```
--style=allman
--align-reference=name
--indent-switches
--indent-modifiers
--indent-classes
--pad-oper
--indent-col1-comments
--lineend=linux
--max-code-length=124
```

一些 IDE（例如 QtCreator）支持在每次将文件保存到磁盘时自动格式化代码。

### 如何创建 Github 拉取请求（PR）

[如何贡献给 INDI 完整指南](http://indilib.org/develop/tutorials/181-how-to-contribute-to-indi-github-development.html)

以下是提交 PR 的简短版本：

1. 使用 Github 帐户登录并分叉官方 INDI 存储库。
2. 克隆官方 INDI 存储库，并将分叉的 INDI 存储库添加为远程（git remote add ...）。
3. 创建本地 Git 分支（git checkout -b my_branch）。
4. 处理补丁并提交更改。
5. 如果准备好了，将此分支推送到您的分叉仓库（git push -f my_fork my_branch:my_branch）。
6. 在浏览器中转到官方仓库的 github 网站，它会弹出一个消息以创建 PR。创建它。
7. 推送更新到 PR：只需更新您的分支（git push -f my_fork my_branch:my_branch）。

如果您想制作更干净的 PR（推荐！），请阅读此 [教程](https://blog.adamspiers.org/2015/03/24/why-and-how-to-correctly-amend-github-pull-requests/) 并遵循它。最好的方法是保持 _每个提交一个逻辑更改_，而不是通过多个小修复来污染历史记录。

### 驱动程序文档

提交新驱动程序时，驱动程序用户 **文档** 是提交过程的一部分。

- 安装：驱动程序名称、可执行文件名称、版本、所需的 INDI 版本。
- 功能：它到底支持哪些功能？
- 操作：如何操作驱动程序？每个子部分应附有各种选项卡的屏幕截图等。
  最好注释以便新用户更容易跟随。
  - 连接：如何建立连接？如何设置端口（如果有）？
  - 主控：主要控制选项卡及其功能。
  - 选项：可用的各种选项的解释。
  - 等等：驱动程序创建的任何其他选项卡。
- 问题：使用此驱动程序时用户应注意的任何问题或警告。

### 示例驱动程序

您可以基于现有驱动程序创建新驱动程序。请查看 examples 或 drivers/skeleton 目录，了解如何开始。

# 单元测试

要运行单元测试套件，您必须首先安装 [Google 测试框架](https://github.com/google/googletest)。您需要从源代码构建并安装此框架，因为 Google 不推荐使用包管理器来分发发行版。（这是因为每个构建系统通常是独特的，一刀切的方法效果不佳）。

安装 Google 测试框架后，请按照以下替代构建顺序操作：

```
mkdir -p build/indi
cd build/indi
cmake -DINDI_BUILD_UNITTESTS=ON -DCMAKE_BUILD_TYPE=Debug ../../
make
make test
```

有关更多详细信息，请参阅 .circleci 目录中的脚本。
