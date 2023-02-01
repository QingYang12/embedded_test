#include <8052.h>   // "reg52.h" 此文件中定义了单片机的一些特殊功能寄存器
#include <stdio.h>
#define uchar unsigned char
#define uint  unsigned int

#define Z1 P2_0	//左边马达下接口 	out2
#define Z2 P2_1	//左上		out1
#define Z3 P2_2	//右下		out4
#define Z4 P2_3	//右上		out3

#define D1 P2_4	//左边马达下接口 	out2
#define D2 P2_5	//左上		out1
#define D3 P2_6	//右下		out4
#define D4 P2_7	//右上		out3


 void stopd();
 void stopz();
 void forward();
 void back();
 void left();
 void right();
void UART_Routine() __interrupt 4;
void UART_SendByte(unsigned char Byte);
 void UsartConfiguration();

 void stopd()
{
	D1=1;
	D2=1;
	D3=1;
	D4=1;

	
}
void stopz()
{
	Z1=1;
	Z2=1;
	Z3=1;
	Z4=1;
}
void forward()
{
	D1=1;
	D2=1;
	D3=0;
	D4=0;	  
}

void back()
{
	D1=0;
	D2=0;
	D3=1;
	D4=1;	
}

void left()
{
	Z1=0;
	Z2=0;
	Z3=1;
	Z4=1;
}

void right()
{
	Z1=1;
	Z2=1;
	Z3=0;
	Z4=0;
	
}
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}
void UART_Routine() __interrupt 4    //串口中断号
{
    unsigned int receive_data;
	if(RI==1)
	{
		receive_data=SBUF;			   //接收数据
        switch(receive_data)
		{
			case (01):
				forward();break;
			case (02):
				back();break;
			case (03):
				left();break;
			case (04):
				right();break;
			case (00):
				stopd();break;
			case (07):
				stopz();break;
		}
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
