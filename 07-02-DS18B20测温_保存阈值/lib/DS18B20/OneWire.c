#include <8052.h>

//引脚定义
#define OneWire_DQ P3_7 // 开发板上的D18B20的数字引脚连到了P3_7. 本语句与后面这个语句作用相同: __sbit __at(0xB0) OneWire_DQ;
/**
  * @brief  单总线初始化
  * @param  无
  * @retval 从机响应位，0为响应，1为未响应
  */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ=1;				// 0. 先置高电平
	OneWire_DQ=0;				// 1. 拉低电平直到500us
	i = 247;while (--i);		//Delay 500us
	OneWire_DQ=1;				// 2. 拉高电平至70us
	i = 32;while (--i);			//Delay 70us
	AckBit=OneWire_DQ;			// 3. 接收应答需要500us
	i = 247;while (--i);		//Delay 500us
	return AckBit;
}

/**
  * @brief  单总线发送一位
  * @param  Bit 要发送的位
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
   // 调用一个函数约需要 4 us; 执行一条空语句, 约需要 1 us. 以下代码中的等待考虑了调用函数和执行语句所需要的时间.
	unsigned char i;
	OneWire_DQ=0;				// 0. 先拉低电平,保持10 us后
	i = 4;while (--i);			//
	OneWire_DQ = Bit;			// 1. 为 DQ 赋值. 如果Bit是 1, 相当于提高电平.表示[发送的数值是1];如果 Bit 是 0, 相当于保持低电平,表示[发送的数值是0].
	i = 24;while (--i);			//    再保持50us;
	OneWire_DQ=1;				// 2. 置高电平,结束发送
}

/**
  * @brief  单总线接收一位
  * @param  无
  * @retval 读取的位
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ = 0;				// 0. 先拉低电平,保持 5 us, 表示[开始接收数据]
	i = 2;while (--i);			//Delay 5us
	OneWire_DQ = 1;				// 1. 拉高电平,保持 5 us, 表示[开始接收数据]
	i = 2;while (--i);			//Delay 5us
	Bit=OneWire_DQ;
	i = 24;while (--i);			//Delay 50us
	return Bit;
}

/**
  * @brief  单总线发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  单总线接收一个字节
  * @param  无
  * @retval 接收的一个字节
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}
