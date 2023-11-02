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
* LCD1602 显示屏模块
* DS18B20 测温模块（开发板上已有，不必外接）
* AT24C02 寄存器模块（开发板上已有，不必外接）

# 程序功能介绍

1. 在 LCD1602 上显示 DS18B02 上获得的信息, (1) 当前的温度; (2) 是否超过阈值 O:H 或 O:L (3) 高温阈值; (4) 低温阈值.
2. 如果当前温度在两个阈值之间,则不显示第 (2) 项.
3. 通过 4 个独立按键调整高温与低温的阈值.
4. 每次修改阈值后,都保存到 AT24C02 中. 重启时, 再从 AT24C02 中读出来.

# 程序说明

1. DS18B20 使用 1-Wire 协议与 MCU 通信, 属于半双工.
2. 尙不支持通过长按按键来快速调整阈值.


