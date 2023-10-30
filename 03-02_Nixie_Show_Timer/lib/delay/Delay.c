void Delay_ms(unsigned int xms) // Delay Function @11.0592MHz
{
	unsigned char i, j;

	for (; xms > 0; xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}