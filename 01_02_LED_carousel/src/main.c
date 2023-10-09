#include <8052.h>
#include "util.h"
void main(void)
{
  while(1){
      delay(1000);
      P2 = 0xFE;
      delay(1000);
      P2 = 0xFF;
  }
}