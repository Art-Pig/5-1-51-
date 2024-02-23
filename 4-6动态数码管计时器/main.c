/*
--------流程----------
1.先写好数码管对应字符数组，数码管位置对应数组
2.初始化P0，P2
3.定时器判断时间
4.变灯
5.灯咋变：
	对秒表上的时间取整或取余，动态扫描（延时人眼看不到的范围）
****6.尽可能不要对已定义的位或引脚反复操作！！！！
-----------------------
*/
#include <REGX52.H>
//对类型重新定义，
typedef unsigned int u16;
typedef unsigned char u8;


//定义引脚，保持这个习惯，别直接对引脚操作
sbit ADDR0 = P2^4;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^2;

u8 i;
u16 clock =59999;

//定义数码管显示0~9的数组
u8 X[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0X7D,0x07,0x7F,0x6F};

//建立临时数组来储存数码管要显示值，数组多定义一个，避免越界
u8 real[]={0x00,0x00,0x00,0x00,0x00,0x00};

//软件延时用来消影，注意不能用定时器消影，因为定时器是要占用寄存器的
void Delay(u8 xms)	//@11.0592MHz
{
	while(xms)
	{
		unsigned char i, j;

		
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

//定时器初始化函数
void time_init()
{
	TMOD &= 0xF0;//调用定时器0,注意位操作最好不要直接赋值
	TMOD |= 0x01;
	TL0 = 0x18;  //0xFC18到溢出约为1ms；
	TH0 = 0xFC;
	TF0 = 0; //清除TF0标志
	TR0=1;	//开始计时
	ET0 = 1;	//使能中断
	EA = 1;
	PT0 = 0;
	
}

//定时器中断函数
void time0() interrupt 1
{
	static u16 count;	//静态数据，发在函数内类似于局部变量，反正在函数里不受外界干扰
	TL0 = 0x18;  //0xFC18到溢出约为1ms；
	TH0 = 0xFC;
	count++;									//count 来记录定时器经历了多少次1ms
	if(count==1000) //定时1s
	{
		count=0;
		clock--;
	}
}


//显示数码管函数
void display()
{
	real[0]=X[clock/10000];  //对定义的倒计时取各各位
	real[1]=X[clock/1000%10];
	real[2]=X[clock/100%10];
	real[3]=X[clock/10%10];
	real[4]=X[clock%10];
	for(i=0;i<5;i++){   //显示数码管
			switch(i)
		{
			case 0:ADDR0=1;ADDR1=1;ADDR2=1;P0=real[0];Delay(1);break;
			case 1:ADDR0=1;ADDR1=1;ADDR2=0;P0=real[1];Delay(1);break;
			case 2:ADDR0=1;ADDR1=0;ADDR2=1;P0=real[2];Delay(1);break;
			case 3:ADDR0=1;ADDR1=0;ADDR2=0;P0=real[3];Delay(1);break;
			case 4:ADDR0=0;ADDR1=1;ADDR2=1;P0=real[4];Delay(1);break;
			default:break;	
		}
		P0=0x00; //消影
	}
	
		
}
	
void main()
{
	time_init();
	P0=0x00;
	while(1){
		display();
	}
}