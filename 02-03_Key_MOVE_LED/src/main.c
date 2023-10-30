#include <8052.h>
#include <Delay.h>
#include <Key.h>
/**
 * @brief 按一下按键, 灯循环亮
 *
 */
void main(void)
{
  unsigned char LEDnum;
  LEDnum = 1;
  while(1){
    unsigned char keydown = Key();
    switch (keydown){
    case 3:
      P2 = ~LEDnum;
      LEDnum = LEDnum << 1;
      if(LEDnum == 0) LEDnum = 1;
      break;
    case 2:
      P2 = ~LEDnum;
      LEDnum = LEDnum >> 1;
      if(LEDnum == 0) LEDnum = 1;
      break;
    default:
      break;
    }
  }
}