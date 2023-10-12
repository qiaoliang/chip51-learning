#include <8052.h>
#include <LCD1602.h>
/**
 * 本程序通过串口以4800bps与PC通信.从串口接收数据,先点亮对应的 LED 灯,然后再将收到的数据取反后发送回去.
 * 只用到了串口和定时器1.
 */


void main(void)
{
  LCD_Init();
  LCD_ShowChar(1, 1, 'A');
  LCD_ShowString(2, 3, "Hello World!");
  while (1)
  {
  }
}