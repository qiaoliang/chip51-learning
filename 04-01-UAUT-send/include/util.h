#ifndef __UTIL_H__
#define __UTIL_H__
#include<8052.h>
#include"timer.h"
void delay(unsigned int ms){
    for(int i=0;i<ms;i++){
        TIMER_0_Init();
        while (TF0 == 0); // 计数器溢出时,时间刚好是1ms
        TR0 = 0; // 停止定时器 0
        TF0 = 0; // 清除定时器的溢出标志位
    }
}
#endif