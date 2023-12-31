#include <8052.h>
#include <reg51.h> //将寄存器头文件包含在文件中

void delay(void)  //100ms延时函数
{
  TMOD = 0x10; // 定时器1工作在模式1下
  TH1 = 0x2E;  // 将计数值的高位设置为0x2E
  TL1 = 0x80;  // 将计数值的低位设置为0x80
  TR1 = 1;     // 启动定时器1
  while (TF1 == 0)
    ;      // 等待定时器1溢出
  TR1 = 0; // 停止定时器1
  TF1 = 0; // 清除定时器1的溢出标志位
}

void main(void)
{
  while(1){
    P2 = 0xEE;
    for(int i = 0; i < 8; i++)
      delay();
    delay();
    P2 = 0xFF;
    delay();
  }

}