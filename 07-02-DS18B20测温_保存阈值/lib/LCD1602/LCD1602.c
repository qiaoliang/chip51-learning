#include <8052.H>
#include <Delay.h>
// 下面的引脚与 板卡上的三个 LED 共用引脚,所以这三个LED在这个程序中不能用.
#define LCD_RS P2_6
#define LCD_RW P2_5
#define LCD_EN P2_7
#define LCD_DataPort P0			 // 普中51开发板与P0(数码管)共用引脚,所以数码管会出现乱码,不必管
const unsigned char COMM = 0x00; // LCD命令字，参考数据手册
const unsigned char DATA = 0x01; // LCD数据，参考数据手册

extern unsigned char code_pic[6][8];

void LCD_write(unsigned int flag, unsigned char data)
{
	LCD_EN = 0;	   // 使能端首先置低
	LCD_RS = flag; // 根据指令类型设置RS, 0:指令; 1:数据
	LCD_RW = 0;	   // RW清零，选择写入. 1:读取; 0:写入
	Delay_ms(10);
	LCD_DataPort = data;
	LCD_EN = 1; // 上升沿有效
	Delay_ms(10);
	LCD_EN = 0; // 变回下降沿
	Delay_ms(10);
}

/**
 * @brief  LCD1602写命令,被其它函数调用
 * @param  Command 要写入的命令
 * @retval 无
 */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_write(COMM, Command);
}

/**
 * @brief  LCD1602写数据
 * @param  Content 要写入的数据
 * @retval 无
 */
void LCD_WriteData(unsigned char Content)
{
	LCD_write(DATA, Content);
}

/**
 * @brief  LCD1602设置光标位置
 * @param  Row 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @retval 无
 */
void LCD_SetCursor(unsigned char Row, unsigned char Column)
{
	if (Row == 1)
	{
		LCD_WriteCommand(0x80 | (Column - 1));
	}
	else if (Row == 2)
	{
		LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
	}
}

/**
 * @brief 将自定义字符写入CGRAM
 *
 * @param addr 是CGRAM 的地址（0~7）
 * @param pic_num 是指向一个8位数组的首地址
 */
void LCD_Write_custom_pic(unsigned char addr, unsigned char *pic_num)
{
	unsigned char i;
	addr = addr << 3;
	for (i = 0; i < 8; i++)
	{
		LCD_WriteCommand(0x40 | (addr + i)); // (01) (000) (000)
		LCD_WriteData(pic_num[i]);
	}
}

/**
 * @brief 写六个自定义字符到CGRAM
 *
 */
void LCD_Custom_char()
{
	int i;
	for (i = 0; i < 8; i++)
	{
		LCD_Write_custom_pic(i, code_pic[i]);
	}
}

/**
 * @brief  LCD1602初始化函数
 * @param  无
 * @retval 无
 */
void LCD_Init()
{
	LCD_WriteCommand(0x38); // 命令字 0011 1000，设置八位数据接口，16X2显示，5X7点阵
	LCD_WriteCommand(0x0c); // 命令字 0000 1100，设置显示开，光标关，闪烁关
	LCD_WriteCommand(0x06); // 命令字 0000 0110，设置数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01); // 命令字 0000 0001，设置光标复位，清屏

	LCD_Custom_char();
}

/**
 * @brief  在LCD1602指定位置上显示一个字符
 * @param  Row 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符
 * @retval 无
 */
void LCD_ShowChar(unsigned char Row, unsigned char Column, char Char)
{
	LCD_SetCursor(Row, Column);
	LCD_WriteData(Char);
}

/**
 * @brief  在LCD1602指定位置开始显示所给字符串
 * @param  Row 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  String 要显示的字符串
 * @retval 无
 */
void LCD_ShowString(unsigned char Row, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Row, Column);
	for (i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
 * @brief  返回值=X的Y次方
 */
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0; i < Y; i++)
	{
		Result *= X;
	}
	return Result;
}

/**
 * @brief  在LCD1602指定位置开始显示所给数字
 * @param  Row 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~65535
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void LCD_ShowNum(unsigned char Row, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Row, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
 * @param  Row 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：-32768~32767
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void LCD_ShowSignedNum(unsigned char Row, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Row, Column);
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number1 / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  在LCD1602指定位置开始以十六进制显示所给数字
 * @param  Row 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~0xFFFF
 * @param  Length 要显示数字的长度，范围：1~4
 * @retval 无
 */
void LCD_ShowHexNum(unsigned char Row, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i, SingleNumber;
	LCD_SetCursor(Row, Column);
	for (i = Length; i > 0; i--)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData(SingleNumber + '0');
		}
		else
		{
			LCD_WriteData(SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief  在LCD1602指定位置开始以二进制显示所给数字
 * @param  Row 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
 * @param  Length 要显示数字的长度，范围：1~16
 * @retval 无
 */
void LCD_ShowBinNum(unsigned char Row, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Row, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(2, i - 1) % 2 + '0');
	}
}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}
