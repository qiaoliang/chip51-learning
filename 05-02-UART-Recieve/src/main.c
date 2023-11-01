#include <8052.h>
#include <UART.h>
#include <Timer.h>
#include <LCD1602.h>
/**
 * 本程序通过串口以9600 bps与PC通信. 通过串口中断程序接收数据.
 * 只用到了串口和定时器1.
 */
unsigned char row =0x01;
unsigned char column =0x01;
/**
 * @brief 串口中断处理函数.当串口接收到数据时,将数据取反后发送回去.
 */
void UART_Routine(void) __interrupt 4 __using 4
{
  if (RI)
  {
    unsigned char data_recieved = SBUF;
    if(data_recieved=='\a'){  // 0x07 ,清屏
      LCD_ShowChar(row, column, 'x');
      LCD_Clear();
      row=1;
      column=1;
      RI = 0;
      return;
    }
    if(data_recieved=='\b'){   // 0x08 在下一行开始显示
      LCD_ShowChar(row, column, 'y');
      RI = 0;
      if(row>=2)
        LCD_Clear();  // 清屏
      row = row==2?1:2;
      column = 1;
      return;
    }
    if(data_recieved<=31){   // 不可见的控制字符
      RI = 0;
      return;
    }
    LCD_ShowChar(row, column, data_recieved);
    if(column<16){
      column++;
    }else{
      column=1;
      if(row<2){
        row++;
      }else{
        row=1;
        LCD_Clear();  // 清屏
      }
    }
    RI = 0;
  }
}

void main(void)
{
  UART_Init();
  LCD_Init();
  UART_SendString("你好,我是51单片机\r\n");
  while (1)
  {
  }
}