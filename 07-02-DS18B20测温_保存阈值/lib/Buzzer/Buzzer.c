#include <8052.H>
#include "Delay.h"
#define BUZZER P2_5

void buzzer_delay500us()
{
    unsigned char i;
    i = 253;
    while (--i)
        ;
}
void Buzzer(unsigned int time)
{
    BUZZER = 0;
    while (time--)
    {
        BUZZER = !BUZZER;
        buzzer_delay500us();
    }
}