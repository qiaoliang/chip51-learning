#include <8052.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "Key.h"

float T, TShow;
extern char TLow, THigh;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();								// 上电先转换一次温度，防止第一次读数据错误
	Delay_ms(1000);									// 等待转换完成
	if (THigh > 125 || TLow < -55 || THigh < TLow) // //如果阈值非法，则设为默认值
	{
		THigh = 32;
		TLow = 25;
	}
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	LCD_ShowSignedNum(2, 4, THigh, 3);
	LCD_ShowSignedNum(2, 12, TLow, 3);

	while (1)
	{
		/*温度读取及显示*/
		DS18B20_ConvertT();	 // 转换温度, 从温度感应元件中将当前的温度值转运到数据寄存器中
		T = DS18B20_ReadT(); // 读取温度, 即: 从数据寄存器中读出数据
		if (T < 0)			 // 如果温度小于 0 度,
		{
			LCD_ShowChar(1, 3, '-'); // 显示负号
			TShow = -T;				 // 将温度变为正数
		}
		else // 如果温度大于等于0
		{
			LCD_ShowChar(1, 3, '+'); // 显示正号
			TShow = T;
		}
		LCD_ShowNum(1, 4, TShow, 3);							  // 显示温度整数部分
		LCD_ShowChar(1, 7, '.');								  // 显示小数点
		LCD_ShowNum(1, 8, (unsigned long)(TShow * 100) % 100, 2); // 显示温度小数部分
		Delay_ms(10);
		KeyNum = Key();
		/*阈值判断及显示*/
		if (KeyNum)
		{
			DS18B02_SetThreshold(KeyNum);		// 根据按键值调整阈值 TH和TL
			LCD_ShowSignedNum(2, 4, THigh, 3); // 显示阈值数据
			LCD_ShowSignedNum(2, 12, TLow, 3);
		}
		if (T > THigh) // 温度越界判断
		{
			LCD_ShowString(1, 13, "OV:H");
		}
		else if (T < TLow)
		{
			LCD_ShowString(1, 13, "OV:L");
		}
		else
		{
			LCD_ShowString(1, 13, "    ");
		}
	}
}