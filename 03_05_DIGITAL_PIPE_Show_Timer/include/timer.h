#ifndef __TIMER_H__
#define __TIMER_H__
#include<8052.h>

void TIMER_1_Init(){
    TMOD &= 0x0F;      // 清除定时器1的控制位
    TMOD |= 0x10;      // 定时器1工作在模式1下
    TH1 = 64536 / 256; // 从64635 开始计数,设置计数值的高位
    TL1 = 64536 % 256; // 设置计数值的低位
    TR1 = 1;           // 启动定时器1
}

void TIMER_0_Init()
{
    // 每 1 ms 产生一次中断
    TMOD &= 0xF0;      // 清除定时器 0 的控制位
    TMOD |= 0x08;      // 定时器 0 在模式 1 下用做计数器
    TH0 = 64536 / 256; // 从64536 开始计数,设置计数值的高位
    TL0 = 64536 % 256; // 设置计数值的低位
    TR0 = 1;           // 启动定时器1
    EA = 1;            // 开启总中断
    ET0 = 1;           // 定时器 0 的中断使能位
}

#endif