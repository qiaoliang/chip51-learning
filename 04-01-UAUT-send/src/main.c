#include <8052.h>
#include "UART.h"
#include "util.h"
/**
 * @brief 本程序点亮LED,以 4800bps 发送数据 ox66, 再熄灭LED,延时1秒,循环执行.
 *
 */
void main(void)
{
  UART_init();
  while(1){
    P2 = 0x00;  //发送前,点亮
    delay(1000);
    UART_send(0x66);
    P2 = 0xFF;  // 发送完成以后,熄灭
    delay(1000);
  }
}