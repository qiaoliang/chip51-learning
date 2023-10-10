#include <8052.h>
#include "util.h"
#include "digitalpipe.h"

int T0_count = 0;
volatile int pos = 0;
/*
  @brief interrupt 1 指明是定时器中断0; interrupt 2 指明是外部中断1; interrupt 3 指明是定时器中断1; interrupt 4 指明是串行口中断
*/
void TIMER_0_Routine() __interrupt(1) __using(1)
{
  T0_count++;
  if (T0_count >= 100)
  {
    pos=pos+1;
    T0_count = 0;
  }
}
void main(void)
{
  TIMER_0_Init();
  while(1){
    for(int i=0;i<4;i++){
      DigitalPipeDisplay(8 - (pos+i) % 8, 4-i);
      delay(5);
    }
  }
}