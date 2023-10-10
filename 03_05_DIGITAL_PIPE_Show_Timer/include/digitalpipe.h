#ifndef DIGITALPIPE_H
#define DIGITALPIPE_H

#include <8052.h>
#include "util.h"

#define LETTER_DASH  10
#define LETTER_E     0x79
#define LETTER_R     0x77

unsigned char DigitalPipeNumber[]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

const unsigned int INTERVAL = 2;

void ShowError(){
   P2_2 = 1;P2_3 = 1;P2_4 = 1; P0=LETTER_E;
   delay(INTERVAL);
   P2_2 = 0;P2_3 = 1;P2_4 = 1; P0=LETTER_R;
   delay(INTERVAL);
   P2_2 = 1;P2_3 = 0;P2_4 = 1; P0=LETTER_R;
   delay(INTERVAL);
}

/*
 @brief 在位置 location 上显示一个数字 number
*/
void DigitalPipeSingleDisplay(unsigned char location, unsigned char number){
   switch (location)
   {
   case 1: P2_2 = 1; P2_3 = 1; P2_4 = 1; break;
   case 2: P2_2 = 0; P2_3 = 1; P2_4 = 1; break;
   case 3: P2_2 = 1; P2_3 = 0; P2_4 = 1; break;
   case 4: P2_2 = 0; P2_3 = 0; P2_4 = 1; break;
   case 5: P2_2 = 1; P2_3 = 1; P2_4 = 0; break;
   case 6: P2_2 = 0; P2_3 = 1; P2_4 = 0; break;
   case 7: P2_2 = 1; P2_3 = 0; P2_4 = 0; break;
   case 8: P2_2 = 0; P2_3 = 0; P2_4 = 0; break;
   }
   P0 = DigitalPipeNumber[number];
   delay(INTERVAL);
}
/*
 * @brief 显示时间
 * @param hour 小时
 * @param mins 分钟
 * @param sec 秒
 */
void ShowTimer(unsigned char hour, unsigned char mins, unsigned char sec){
   DigitalPipeSingleDisplay(1, hour / 10);
   DigitalPipeSingleDisplay(2, hour % 10);
   DigitalPipeSingleDisplay(3, LETTER_DASH);
   DigitalPipeSingleDisplay(4, mins / 10);
   DigitalPipeSingleDisplay(5, mins % 10);
   DigitalPipeSingleDisplay(6, LETTER_DASH);
   DigitalPipeSingleDisplay(7, sec / 10);
   DigitalPipeSingleDisplay(8, sec % 10);
}
/*
 @brief 显示 number, 个位数的位置设置为 location
*/
void ShowNumberOnPipe(unsigned int location, unsigned  long number)
{
   unsigned int length = lengthOf(number);
   if (location < 1 || location > 9 || location < length)
   {
      ShowError();
      return;
   }
   if (number == 0)
   {
      DigitalPipeSingleDisplay(location, 0);
      return;
   }
   while (number)
   {
      DigitalPipeSingleDisplay(location--, number % 10);
      number /= 10;
   }
}
#endif