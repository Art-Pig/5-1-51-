#include <REGX52.H>
void delay(unsigned char xms)
{
	while(xms)
	{
		xms--;
	}
}
void main()
{
	unsigned char j,i;
	for(j=0;j<8;j++)
	{
		P2=0x01<<j;
		for(i=0;i<3;i++)
		{
			~P2;
			delay(20000);
			P2=0xFF;
			delay(20000);
		}
		if(j==7)
		{
			j=0;
		}
	}
}
	
