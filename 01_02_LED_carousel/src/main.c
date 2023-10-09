#include <8052.h>
#include "util.h"

void main(void)
{
  P2_1 = 0x01;
  while(1){
    if( P3_1 == 0){
      delay(20);
      while(P3_1 == 0);
      delay(20);
      P2_1 = ~P2_1;
    }
  }

}