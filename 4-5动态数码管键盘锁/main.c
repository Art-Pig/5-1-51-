#include <REGX52.H>
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
void Delay(unsigned char xms)
{
	unsigned char i,j;
	while(xms--)
	{
		for(i=0,j=123;i<j;i++);

	}
}

void main()
{

	unsigned char number;
	unsigned char password = 2;
	//设置密码为2，即按下K3，密码正确
	while(1)
	{
	//给它一个初始值帮助数码管保持——
		number=5;
		P0=0x40;
	
		P3=0xff;
		P2 = 0xff;
		//锁存

		//if判断，为各个按键赋予相对应的值
		if(K1==0)
		{
			Delay(10);
			number=0;
		
		}
		else if(K2==0)
		{
			Delay(10);
			number=1;
		}
		else if(K3==0)
		{
			Delay(10);
			number=2;
		}
		else if(K4==0)
		{
			Delay(10);
			number=3;
		}

		//说明按键没按下，number还是初始值
		if(number==5){
			P0=0x40;
			Delay(1);
			P2=0xff;
		
		
		}

		//一旦密码正确则数码管立刻显示P，P2^0点亮
		else if(number==password)
		{
			P0=0x73;
			Delay(1);
	
			P2 = 0x7f;
			
		}

		//如果按下其他按键。则密码错误，数码管显示E，P2^0不亮
		else if(number==0||number==1||number==3)  
		{
			P0=0x79;
			Delay(1);
			P2=0xff;
		
		}
		//按键一旦再按下，再次循环
		while(P3==0xff);
	}

}