#include <8052.h>
#include "util.h"
#include "digitalpipe.h"

void main(void)
{
  while(1){
    if(P3_1 == 0){  // 按下 1 号按键, 在第一个数码管显示 1
      DigitalPipeDisplay(5,8);
    }
    if (P3_0 == 0)
    { // 按下 2 号按键, 数码管显示 2
      DigitalPipeDisplay(6,9);
    }
    if(P3_2 == 0){  // 按下 3 号按键, 数码管显示 3
      DigitalPipeDisplay(7,6);
    }
    if (P3_3 == 0){
      DigitalPipeDisplay(8,7);
    }
  }
}