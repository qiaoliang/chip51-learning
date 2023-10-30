#include <8052.h>
/**
 * @brief 按住独立按键 1, LED 灯亮; 松开按键, LED 灯熄.
 *
 */
void main(void)
{
  P2_0 = 0x00;  // 低电平,LED 亮.
  while(1){
    if( P3_1 == 1){  // 按下按键,是高电平
      P2_0 = 0x00;
    }else{
      P2_0 = 0x01;
    }
  }
}