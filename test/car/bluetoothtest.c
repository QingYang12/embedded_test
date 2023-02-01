// 收到后 LED灯全亮 
#include <8052.h>   // "reg52.h" 此文件中定义了单片机的一些特殊功能寄存器
#include <stdio.h>
#define uchar unsigned char
#define uint  unsigned int


void UART_Routine() __interrupt 4;
void UART_SendByte(unsigned char Byte);
 void UsartConfiguration();

 
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}
void UART_Routine() __interrupt 4    //串口中断号
{
    uchar receive_data;
	if(RI==1)
	{
		//receive_data=SBUF;			   //接收数据
        P2=SBUF;
		RI=0;                           //串口接收寄存器置零
	}	
}

	
void UsartConfiguration()
{	
	SCON=0x50; 			//8位数据,可变波特率
	PCON |=0x80; 		//使能波特率倍速位SMOD	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;           //开启总中断
	ES=1;			//开启串口中断 
}


void main()
{
	UsartConfiguration();	
	while(1);	
}
