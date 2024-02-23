#include <REGX52.H>
#include <REGX52.H>
//对类型重新定义，
typedef unsigned int u16;
typedef unsigned char u8;


//定义引脚，保持这个习惯，别直接对引脚操作
sbit ADDR0 = P2^4;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^2;

u8 i;
u8 clock =0;

//定义数码管显示0~9的数组
u8 X[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0X7D,0x07,0x7F,0x6F};

//建立临时数组来储存数码管要显示值，数组多定义一个，避免越界
u8 real[]={0x00,0x00,0x00};
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
void Timer0_Isr() interrupt 1
{
	static u16 count = 0;
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	count++;
	if(clock==60)
	{
		clock = 0;
	}
	if(count==1000)
	{
		
		count = 0;
		clock++;
		
		
	}
	
}

void Timer0_Init()		//1毫秒@11.0592MHz
{
	
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	EA = 1;
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;	//使能定时器0中断
	PT0 = 0;
}


//显示数码管函数
void display()
{
	real[0]=X[clock/10];  //对定义的倒计时取各各位
	real[1]=X[clock%10];
	
	for(i=0;i<5;i++){   //显示数码管
			switch(i)
		{
			case 0:ADDR0=0;ADDR1=1;ADDR2=1;P0=real[1];Delay(10);break;
			case 1:ADDR0=1;ADDR1=0;ADDR2=0;P0=real[0];Delay(10);break;
			
			default:break;	
		}
		P0=0x00; //消影
	}
	
		
}

void main()
{
	Timer0_Init();
	P0=0x00;
	while(1)
	{
		display();
	}

}

