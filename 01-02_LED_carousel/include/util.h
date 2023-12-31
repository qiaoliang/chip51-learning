#include <8052.h>
//你所使用的单片机的主频是多少。假设它是12MHz，那么每个机器周期为 12 / 12MHz = 1 微秒。
//假设你要延时1毫秒，那么计数值将为：
//计数值 = 1毫秒 / 1微秒 = 1000 计数值
//定时器的工作模式是 模式 1, 即 16 位, 则 1000的补数为( 65536 - 1000 ) = 64536。
//所以, 需要设置定时器初值为64536(0xFCC8),所以:
    //  高位设置为 FC
    //  低位设置为 C8
    void
    delay(unsigned int ms) // 1ms的延时函数
{
    for (int i = 0; i < ms; i++)
    {
        TMOD |= 0x10; // 定时器1工作在模式1下
        TH1 = 0xFC;  // 设置计数值的高位
        TL1 = 0xC8;  // 设置计数值的低位
        TR1 = 1;     // 启动定时器1
        while (TF1 == 0)
            ;    // 等待定时器1溢出
        TR1 = 0; // 停止定时器1
        TF1 = 0; // 清除定时器1的溢出标志位
    }
}

