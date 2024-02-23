#include <REGX52.H>
//定义一个数组来保存"HELLO"的字节
unsigned char Hello[5][2]={{0xff,0x76},{0xfb,0x79},{0xf7,0x38},{0xf3,0x38},{0xef,0x3f}};
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
	unsigned char i;
	while(1)
	{
		P0=0x00;
		P2=0xff;
		for(i=0;i<5;i++)
		{
		//给数码管一个反应时间
			Delay(25);
			P2=Hello[i][0];
			Delay(25);
			P0=Hello[i][1];
			Delay(25);
			P0=0x00;
			P2=0xff;
			Delay(25);
		
		}
	
	
	}



}