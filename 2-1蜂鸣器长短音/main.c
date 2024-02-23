#include <REGX52.H>
#include <INTRINS.H>//
#define Long 250
#define Short 100
sbit BEEP=P2^5;

void Delay(unsigned int xms)		//@11.0592MHz
{
	while(xms)
	{
		unsigned char i, j;

		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void	BEEPSOND(unsigned int num)
{
	unsigned int i;
	for(i=0;i<num;i++)
	{
		BEEP=1;
		Delay(1);
		BEEP=0;
		Delay(1);
		
	}
}

void main()
{
	while(1)
	{
		BEEPSOND(Long);
		Delay(1500);
		
		BEEPSOND(Long);
		Delay(1500);
		
		BEEPSOND(Long);
		Delay(1500);
		
		
		BEEPSOND(Short);
		Delay(1500);
		
		Delay(2000);
		
		
	}
}
	
	
