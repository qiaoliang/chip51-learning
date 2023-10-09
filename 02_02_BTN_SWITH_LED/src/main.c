#include <8052.h>
#include "util.h"

void main(void)
{
  P2_7= 0;   // 初始化第8个 LED 为低电平
  while(1){
    if( P3_2 == 0){  // 独立按键 3
      delay(10); // 延时 10ms, 消抖
      while(P3_2 == 0);
      delay(10); // 延时 10ms, 消抖
      if(P2_7){
        P2_7 = 0;
      }else{
        P2_7 = 1;
      }
    }
  }

}