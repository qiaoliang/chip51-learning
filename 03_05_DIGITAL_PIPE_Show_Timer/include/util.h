#ifndef __UTIL_H__
#define __UTIL_H__
#include<8052.h>
#include"timer.h"
void delay(unsigned int ms){
    for(int i=0;i<ms;i++){
        TIMER_1_Init();
        while (TF1 == 0); // 从64536 开始计数,计数器溢出时,时间刚好是1ms
        TR1 = 0; // 停止定时器1
        TF1 = 0; // 清除定时器1的溢出标志位
    }
}
unsigned char lengthOf(unsigned int number){
    unsigned char length =0;
    if(number == 0 ) return length;
    do{
        length++;
        number/=10;
    }while(number);
    return length;
}
#endif