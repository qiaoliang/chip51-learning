Installation
============

stcgal requires Python 3.5 (or later), pyserial 3.0 or later and
TQDM 4.0.0 or later. USB support is optional and requires pyusb
1.0.0b2 or later. You can run stcgal directly with the included
```stcgal.py``` script if the dependencies are already installed.

There are two options for permanent installation:

1. Use Python3 and ```pip```. Run ```pip3 install stcgal``` to
install the latest release of stcgal globally on your system.
This may require administrator/root permissions for write access
to system directories.

2. Use setuptools. Run ```./setup.py build``` to build and
```sudo ./setup.py install``` to install stcgal.

Upload Hex file to the board
=============================


```
$ pipenv shell
$ stcgal --baud {串口的波特率} -P stc89 -p {所用的端口,例如:/dev/cu.wchusbserial14130} {hex 文件,例如: .pio/build/STC89C52RC/firmware.hex}
```