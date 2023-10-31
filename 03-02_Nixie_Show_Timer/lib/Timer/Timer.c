#ifndef __TIMER_H__
#define __TIMER_H__
#include <8052.h>


/**
 * @brief 每 1 ms 产生一次中断. 使用模式1
 * 如何计算第次计数所用的时间? F = f/12 = 11.0592M/12 = 0.9216MHZ   所以, T = 1/F = 1.085us
 * 在方式1时，最多计65536个脉冲产生溢出。
 * 1ms ≈ 921.6 次 ≈ 922
 */
void TIMER_1_Init(){
    TMOD &= 0x0F;      // 清除定时器1的控制位
    TMOD |= 0x10;      // 定时器1工作在模式1下
    TH1 = (65536-922) / 256;
    TL1 = (65536-922) % 256;
    TR1 = 1;           // 启动定时器1
    EA = 1;            // 开启总中断
    ET1 = 1;           // 定时器 0 的中断使能位
}

#endif