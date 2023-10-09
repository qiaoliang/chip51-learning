#include <8052.h>
#include "util.h"

void main(void)
{
  P2_0 = 0x00;
  while(1){
    if( P3_1 == 1){
      P2_0 = 0x00;
    }else{
      P2_0 = 0x01;
    }
  }

}