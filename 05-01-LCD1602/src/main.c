#include <8052.h>
#include <LCD1602.h>
/**
 * 本程序用于测试LCD1602驱动程序,在LCD1602上显示字符
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