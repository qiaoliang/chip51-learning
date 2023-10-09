#include <8052.h>

void main(void)
{
  P2_0 = 0x01;
  while(1){
    if(P3_1 == 0)
    {
      P2_0 = 0x00;
    }else{
      P2_0 = 0x01;
    }
  }

}