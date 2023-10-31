#include <8052.h>
#include <UART.h>
#include <Delay.h>

/**
 * 本程序点亮LED后,以 4800bps 发送数据 0x66. 执行发送命令以后,再熄灭LED,延时1秒,循环执行.
 *
 */
void main(void)
{
  UART_Init();
  while(1){
    P2 = 0x00;  //发送前,点亮
    Delay_ms(1000);
    UART_SendByte(0x66);
    P2 = 0xFF;  // 发送完成以后,熄灭
    Delay_ms(1000);
  }
}