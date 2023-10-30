#include <8052.h>
#include <LCD1602.h>
#include <Timer.h>
/**
 * 本程序演示了LCD1602的自定义字符功能
 */

void main(void)
{
  LCD_Init();

  while (1)
  {
    LCD_WriteCommand(0x80|0x01);
    int i;
    for(i=0;i<0x06;i++)
    {
      LCD_WriteData(i);
    }
  }
}