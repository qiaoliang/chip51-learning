#include <8052.h>
#include <timer.h>

void UART_Init(){   // 9600bps@11.0592
    SCON = 0x50;    // SCON=01010000B，串口工作方式1，允许串口接收
    PCON = 0x00;    // SMOD=0，波特率不加倍
    EA= 1;          // 让中断使能
    ES = 1;         // 允许串口中断,通过中断方式接收数据,中断号是 4.

    // 定时器1, 不产生中断, 只用于产生波特率
    TMOD &= 0x0F; // 清除定时器 1 的控制位, 保留低4位. 51单片机串口通讯必须使用定时器1,不能使用定时器0
    TMOD |= 0x20; // 选择定时器1,工作方式2,即 8位自动重装,可以提高定时器的精度
    // TH1 初值 = 256 - fosc / 波特率 / 32 / 12 * 2^SMOD
    TH1 = 0xFD; // 重装值, 波特率为 9600bps
    TL1 = 0xFD; // 初始值
    TR1 = 1;    // 启动定时器1
}

void UART_SendByte(unsigned char byte) // 通过查询方式来发送数据
{
    SBUF = byte;    // 向缓存器中写入内容
    while(TI==0);   // 发送中,TI位 如果为0 就表示数据未发送完成.反复执行本条语句检测TI位
    TI = 0;         // 此时数据已发送完成, 马上将TI位清零,以便下一次发送.
}
/**
 * @brief 发送结尾为'\0' 的字符串
 *
 * @param str 字符串的首地址
 */
void UART_SendString(unsigned char *str){
    unsigned char temp;
    while(*str != '\0'){
        temp = *str;
        str++;
        UART_SendByte(temp);
    }
}
unsigned char UART_RecieveByte(){
    unsigned char result =0xFF;
    if (RI)
    {
        unsigned char result = SBUF;
        RI = 0;
    }
    return result;
}