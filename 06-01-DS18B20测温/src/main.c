#include <8052.h>
#include <LCD1602.h>
#include <DS18B20.h>
#include <Delay.h>
/**
 * 本程序演示了LCD1602的基本操作,通过定时中断分组显示字符,字符串,数字,二进制数,十六进制数
 */

float T;

int count = 0;
void TIMER_0_Routine(void) __interrupt(1) __using(1)// 定时器0中断函数
{
  count++;
  if (count >= 9000)
    count = 0;
}
void main()
{
  DS18B20_ConvertT(); // 上电先转换一次温度，防止第一次读数据错误
  delay_ms(1000);        // 等待转换完成
  LCD_Init();
  LCD_ShowString(1, 1, "Temperature:");
  while (1)
  {
    DS18B20_ConvertT();  // 转换温度,就是让器件把测量后的温度写到器件内部的暂存器中
    T = DS18B20_ReadT(); // 从暂存器读取温度
    if (T < 0)           // 如果温度小于0
    {
      LCD_ShowChar(2, 1, '-'); // 显示负号
      T = -T;                  // 将温度变为正数
    }
    else // 如果温度大于等于0
    {
      LCD_ShowChar(2, 1, '+'); // 显示正号
    }
    LCD_ShowNum(2, 2, T, 3);                                  // 显示温度整数部分
    LCD_ShowChar(2, 5, '.');                                  // 显示小数点
    LCD_ShowNum(2, 6, (unsigned long)(T * 10000) % 10000, 4); // 显示温度小数部分
  }
}