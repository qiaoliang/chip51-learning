#include <8052.h>
#include "util.h"
#include "digitalpipe.h"

void main(void)
{
  // 数码管需要5ms到10ms的延时才能显示正常.
  // 没有延时,数字位置可能会显示错.
  // 延时过长,数字会发生闪烁.
  while(1){
    DigitalPipeDisplay(5,8);
    delay(5);
    DigitalPipeDisplay(6,9);
    delay(5);
    DigitalPipeDisplay(7,6);
    delay(5);
    DigitalPipeDisplay(8,7);
    delay(5);
  }
}