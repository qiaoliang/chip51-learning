#include <8052.h>
#include "OneWire.h"

// DS18B20指令,指令对应的命令字(16进制数) 要参考 DS18B20的手册.
#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_CONVERT_T 0x44
#define DS18B20_READ_SCRATCHPAD 0xBE
char THigh = 32;
char TLow = 25;
/**
 * @brief  DS18B20开始温度变换
 * @param  无
 * @retval 无
 */
void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
 * @brief  DS18B20读取温度
 * @param  无
 * @retval 温度数值
 */
float DS18B20_ReadT(void)
{
	unsigned char TLSB, TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	Temp = (TMSB << 8) | TLSB;
	T = Temp / 16.0;
	return T;
}
void DS18B02_SetThreshold(unsigned char KeyNum)
{

	if (KeyNum == 1) // K1按键，THigh自增
	{
		THigh++;
		if (THigh > 125)
		{
			THigh = 125;
		}
	}
	if (KeyNum == 2) // K2按键，THigh自减
	{
		THigh--;
		if (THigh <= TLow)
		{
			THigh++;
		}
	}
	if (KeyNum == 3) // K3按键，TLow自增
	{
		TLow++;
		if (TLow >= THigh)
		{
			TLow--;
		}
	}
	if (KeyNum == 4) // K4按键，TLow自减
	{
		TLow--;
		if (TLow < -55)
		{
			TLow = -55;
		}
	}
}
