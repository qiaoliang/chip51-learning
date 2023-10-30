#include <8052.H>
#include <Delay.h>	//包含Delay头文件

#define INTERVAL 2	//数码管显示间隔时间
#define LETTER_DASH  10
#define LETTER_E     0x79
#define LETTER_R     0x77
//数码管段码表
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40/* - */,0x79/* E */,0x77 /* R */};

void ShowError()
{
	P2_2 = 1;P2_3 = 1;P2_4 = 1;
	P0 = LETTER_E;
	Delay_ms(INTERVAL);
	P2_2 = 0;P2_3 = 1;P2_4 = 1;
	P0 = LETTER_R;
	Delay_ms(INTERVAL);
	P2_2 = 1;P2_3 = 0;P2_4 = 1;
	P0 = LETTER_R;
	Delay_ms(INTERVAL);
}

//数码管显示子函数
void Nixie(unsigned char Location,unsigned char Number)
{
	switch(Location)		//位码输出
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//段码输出
	Delay_ms(1);				//显示一段时间
	P0=0x00;				//段码清0，消影
}
void ShowTime(unsigned char hour, unsigned char mins, unsigned char sec)
{
	Nixie(1,hour/10);	//显示小时的十位
	Nixie(2,hour%10);	//显示小时的个位
	Nixie(3,LETTER_DASH);	//显示冒号
	Nixie(4,mins/10);	//显示分钟的十位
	Nixie(5,mins%10);	//显示分钟的个位
	Nixie(6,LETTER_DASH);	//显示冒号
	Nixie(7,sec/10);	//显示秒钟的十位
	Nixie(8,sec%10);	//显示秒钟的个位
}
