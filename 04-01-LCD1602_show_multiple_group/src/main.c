#include <8052.h>
#include <LCD1602.h>
#include <Timer.h>
/**
 * 本程序演示了LCD1602的基本操作,通过定时中断分组显示字符,字符串,数字,二进制数,十六进制数
 */
int T1_count = 0;
/*
  @brief interrupt 1 指明是定时器中断0; interrupt 2 指明是外部中断1; interrupt 3 指明是定时器中断1; interrupt 4 指明是串行口中断
*/
void TIMER_1_Routine() __interrupt(3) __using(3)
{
  T1_count++;
  if (T1_count >= 9000) // 累计 9 秒
  {
    T1_count = 0; // 累计值清零
  }
  // Timer1 重新赋值
  TH1 = (65536 - 922) / 256;
  TL1 = (65536 - 922) % 256;
}

void main(void)
{
  TIMER_1_Init();
  int lastShow = -1;
  while (1)
  {
    int current = T1_count / 3000;
    switch (current)
    {
    case 0:
      if(lastShow != current){
        lastShow = current;
        LCD_Init();
      }
      LCD_ShowChar(1, 1, 'A');
      LCD_ShowString(2, 3, "Hello World!");
      break;
    case 1:
      if(lastShow != current){
        lastShow = current;
        LCD_Init();
      }
      LCD_ShowNum(1,9,123,3);
      LCD_ShowSignedNum(2,13,-55,2);
      break;
    case 2:
      if (lastShow != current)
      {
        lastShow = current;
        LCD_Init();
      }
      LCD_ShowBinNum(1,4,0xAA,8);
      LCD_ShowHexNum(2,10,0xA8,4);
      break;
    }
  }
}