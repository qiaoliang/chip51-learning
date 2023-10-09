#include <8052.h>
#include "util.h"

void main(void)
{
  P2 = 0xFE;
  while(1){
    delay(20);
    P2 = ~P2;
    P2 = P2 << 1;
    P2 = ~P2;
    if(P2 == 0xFF)
      P2 = 0xFE;
  }

}