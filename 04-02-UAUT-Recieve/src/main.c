#include <8052.h>
#include "UART.h"
#include "util.h"
/**
 * 本程序通过串口以4800bps与PC通信.从串口接收数据,先点亮对应的 LED 灯,然后再将收到的数据取反后发送回去.
 * 只用到了串口和定时器1.
 */

unsigned char data_out = 0x00;
/**
 * @brief 串口中断处理函数.当串口接收到数据时,将数据取反后发送回去.
 *
 */
void UART_Routine(void) __interrupt 4 __using 1
{
  if(RI){
    RI = 0;
    P2 = SBUF;
    UART_send(~SBUF);  // 取反后,再发送回去
  }
  if(TI){
    TI = 0;
  }
}

void main(void)
{
  UART_init();
  while(1){
  }
}