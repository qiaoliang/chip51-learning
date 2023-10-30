#include <8052.h>
#include <Timer.h>
#include <Nixie.h>
#include <Delay.h>

int T1_count = 0;
unsigned char hour,mins,sec = 0;

void calculateTime(){
  sec++;
  if(sec == 60){
    sec = 0;
    mins++;
    if(mins == 60){
      mins = 0;
      hour++;
      if(hour == 24){
        hour = 0;
      }
    }
  }
}
/*
  @brief interrupt 1 指明是定时器中断0; interrupt 2 指明是外部中断1; interrupt 3 指明是定时器中断1; interrupt 4 指明是串行口中断
*/
void TIMER_1_Routine() __interrupt(3) __using(3)
{
  T1_count++;
  if (T1_count >= 1000)   // 累计 1 秒
  {
    calculateTime();
    T1_count =0;    // 累计值清零
  }
  // Timer1 重新赋值
  TH1 = (65536 - 922) / 256;
  TL1 = (65536 - 922) % 256;
}

void main(void)
{
  TIMER_1_Init();
  while(1){
    ShowTime(hour,mins,sec);
  }
}