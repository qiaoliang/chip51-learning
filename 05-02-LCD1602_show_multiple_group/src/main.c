#include <8052.h>
#include <LCD1602.h>
/**
 * 本程序演示了LCD1602的基本操作,通过定时中断分组显示字符,字符串,数字,二进制数,十六进制数
 */
int count = 0;
void TIMER_0_Routine(void) __interrupt(1) __using(1)// 定时器0中断函数
{
  count++;
  if (count >= 9000)
    count = 0;
}

void main(void)
{
  TIMER_0_Init();
  int lastShow = -1;
  while (1)
  {
    int current = count / 3000;
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