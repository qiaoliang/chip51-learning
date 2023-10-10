#include <8052.h>
#include "util.h"
#include "digitalpipe.h"
#include "timer.h"

int T0_count = 0;
volatile int pos = 0;
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
void TIMER_0_Routine() __interrupt(1) __using(1)
{
  T0_count++;
  if (T0_count >= 200)
  {
    calculateTime();
    T0_count =0;
  }
}
void main(void)
{
  TIMER_0_Init();
  while(1){
    ShowTimer(hour,mins,sec);
  }
}