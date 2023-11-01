#ifndef __TIMER_H__
#define __TIMER_H__
#include <8052.h>


/**
 * @brief 每 1 ms 产生一次中断. 使用模式1
 * 如何计算每次计数所用的时间? F = f/12 = 11.0592M/12 = 0.9216MHZ   所以, T = 1/F = 1.085us
 * 在方式1时，最多计65536个脉冲产生溢出。
 * 1ms ≈ 921.6 次 ≈ 922
 */
void TIMER_0_Init(){
    TMOD &= 0xF0;      // 清除定时器0的控制位
    TMOD |= 0x01;      // 定时器0工作在模式1下
    TIMER_0_Reload();
    TR0 = 1;       // 启动定时器1
    EA = 1;            // 开启总中断
    ET0 = 1;           // 定时器 1 的中断使能位
}

void TIMER_0_Reload(){  // 1ms 的计数初值
    TH0 = (65536 - 922) / 256;
    TL0 = (65536 - 922) % 256;
}

/**
 *
 * interrupt 1 指明是定时器中断0;
 * interrupt 2 指明是外部中断1;
 * interrupt 3 指明是定时器中断1;
 * interrupt 4 指明是串行口中断
*/
/**
 * @brief 定时器 0 的中断服务函数

void TIMER_0_Routine() __interrupt(1) __using(1)
{
    T1_count++;
    if (T1_count >= 9000) // 累计 9 秒
    {
        T1_count = 0; // 累计值清零
    }
    // Timer1 重新赋值,1 ms 中断一次
    TH1 = (65536 - 922) / 256;
    TL1 = (65536 - 922) % 256;
}
*/
#endif