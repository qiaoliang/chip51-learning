#!/bin/zsh


# 如果有参数则赋值为源文件路径
if [ $# -gt 0 ]; then
  source_file=$1
# 如果没有参数,使用默认值
else
  source_file=".pio/build/STC89C52RC/firmware.hex"
fi

stcgal -P stc89 -p /dev/cu.wchusbserial14120 "$source_file"

