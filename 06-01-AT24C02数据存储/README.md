# 软件开发环境

## 1. 工具准备

### 开发与编译所需要的软件

* VSCode + PlatformIO 插件
* sdcc

### 烧录所需要的工具

* stcgal的安装与使用

stcgal 需要 Python 3.5 (or later)。它有两种安装方式:

1. 使用 Python3 和 ```pip```. 运行 ```pip3 install stcgal``` 安装stcgal 到系统全局。
这可能需要管理员权限和系统目录的写权限。

2. 使用程序 setuptools. 运行 ```./setup.py build``` 来构建出产物， 并使用
```sudo ./setup.py install``` 命令来安装 stcgal.

stcgal 的使用：

```
stcgal -P stc89 -p {所用的端口,例如:/dev/cu.wchusbserial14130} {hex 文件,例如: .pio/build/STC89C52RC/firmware.hex}
```

# 硬件环境

## 所需器件

* 51单片机开发板(我用的普中-A2)
* LCD1602 模块
* AT24C02 模块（开发板上已有，不必外接），存储器大小为 256 X 8 (2K bits)

# 程序功能介绍

1. 51 开发板启动后, LCD1602 上显示初始值 ```00000```
2. 按下开发板上的独立按键，
  1. 按下第 1 个按键时，数值加 1.
  1. 按下第 2 个按键时，数值减 1.
  1. 按下第 3 个按键时，数值被保存到 AT24C02 寄存器中.
  1. 按下第 4 个按键时，数值被从 AT24C02 寄存器中取出来，显示到开发板上。

# 程序说明

1. AT24C02 通过 I2C 协议与 STC89C52 进行数据通信，所以需要根据数据手册中的关于 I2C 协议时序图先实现 I2C 协议。


