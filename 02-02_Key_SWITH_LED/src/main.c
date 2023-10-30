#include <8052.h>
#include <Delay.h>
/**
 * @brief 按一下独立按键 3 , 就点亮; 再按一下就熄灭 .
 *
 */
void main(void)
{
  unsigned char state = 0x00;
  P2_7= 0;   // 初始化第8个 LED 为低电平
  while(1){
    if( P3_2 == 0){  // 独立按键 3
      Delay_ms(20); // 延时 20ms, 消抖
      while(P3_2 == 0);
      Delay_ms(20); // 延时 20ms, 消抖
      if(P2_7 == 1){
        P2_7=0;
      }else{
        P2_7 = 1;
      }
    }
  }
}
