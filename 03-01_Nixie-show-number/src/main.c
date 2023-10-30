#include <8052.h>
#include <Nixie.h>
#include <Key.h>
/**
 * @brief 根据独立按键的按下情况，返回按键的键值,并在对应的数码管上显示
 *
 */
void main(void)
{
  unsigned char keydown,num=0;
  while(1){
    keydown = Key();
    if(keydown >0 ){
      num = keydown;
    }
    if(num >0){
      Nixie(num, num);
    }
  }
}