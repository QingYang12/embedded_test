#include <8052.h>   // "reg52.h" 此文件中定义了单片机的一些特殊功能寄存器
#include <stdio.h>
typedef unsigned int u16;	 
typedef unsigned char u8;
#define led1 P2_0  //P2^0
#define led2 P2_1
#define led3 P2_2
#define led4 P2_3

void timer() __interrupt 1; // SDCC的中断函数要预先声明，区别于KEIL C51

unsigned char counter; // 软件计数器

void main()
{
    TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器	
      led1 = 0;
      led2 = 0;
      led3 = 1;
      led4 = 1;

    while(1);
}

void timer() __interrupt 1
{
    static u16 i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
    i++;
    if(i==1000)
    {
        i = 0;
        led1 = !led1;
        led2 = !led2;
        led3 = !led3;
        led4 = !led4;
    }
}