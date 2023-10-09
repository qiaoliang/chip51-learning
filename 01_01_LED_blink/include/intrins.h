/*
  原因：intrins.h 是 keil c51提供的方法
    但是 SDCC 没有提供该方法，所以需要自己实现
  keil c51 intrins.h 兼容头文件  for SDCC
  实现
    1. void _push_ (unsigned char _sfr)
    2. void _pop_ (unsigned char _sfr)
*/

#ifndef _INTRINS_H_
#define _INTRINS_H_

/* warning: __push __pop 使用堆栈临时保存 sfr 数据，必需成对使用!
     __push(x);
         ...  // 保护代码块
         __pop(x)；  //缺少无该语句编译不会出错，但运行错误!
*/
#define __push(x) __asm push _##x __endasm /* void _push_ (unsigned char _sfr); */
#define __pop(x) __asm pop _##x __endasm   /* void _pop_  (unsigned char _sfr); */

#define _push_ __push　 /*兼容 keil c51*/
#define _my_pop_ __pop　   /*兼容 keil c51*/

/*   安全使用保护宏：
     pushSfr(x);
         ...                 // 受保护代码块
         popSfr(x)；         // 缺少无该语句编译出错，确保生成正确代码。
*/
#define pushSfr(x) \
    do             \
    {              \
    __push(x)

#define popSfr(x) \
    __pop(x);     \
    }             \
    while (0)

#endif //_INTRINS_H_