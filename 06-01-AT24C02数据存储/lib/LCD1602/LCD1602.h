#ifndef __LCD1602_H__
#define __LCD1602_H__

unsigned char code_pic[6][8] = {
    {0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x04, 0x00}, // ↑
    {0x00, 0x04, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04}, // ↓
    {0x00, 0x04, 0x08, 0x1F, 0x08, 0x04, 0x00, 0x00}, // ←
    {0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00}, // →
    {0x04, 0x04, 0x0A, 0x1F, 0x1F, 0x0A, 0x04, 0x04}, // 占位符
    {0x0E, 0x04, 0x1F, 0x0A, 0x11, 0x0A, 0x0A, 0x0A}  // 乔
};

//用户调用函数：
void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_Write_custom_pic(unsigned char addr, unsigned char *pic_num);
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Content);
void LCD_Clear(void);
#endif
