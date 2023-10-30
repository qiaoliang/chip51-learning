#define FREQ_OSC 11059200UL // 晶振频率，单位Hz

void delay_ms(unsigned int count)
{
	unsigned int i;
	while (count > 0)
	{
		i = FREQ_OSC / 1000 / 12; // 1ms延时需要的计数次数
		while (i > 0)
		{
			i--;
		}
		count--;
	}
}
