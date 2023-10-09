#include <8052.h>
#include "util.h"

void main(void)
{
  unsigned char LEDnum;
  LEDnum = 1;
  while(1){
    if( P3_2 == 0){  // 独立按键 3
      delay(10); // 延时 10ms, 消抖
      while(P3_2 == 0);
      delay(10); // 延时 10ms, 消抖
      P2 = ~LEDnum;
      LEDnum = LEDnum << 1;
      if(LEDnum == 0) LEDnum = 1;
    }
  }

}