#include <REGX52.H>
//�������ʾ����
unsigned char X[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0X7D,0x07,0x7F,0x6F};
unsigned char temp[5]={0};
//���嵹��ʱclock
unsigned char clock;
//�����ʱ����
void Delay(unsigned char xms)	//@11.0592MHz
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
//�����λѡ���ѡ����
void Nixie(unsigned char Location,unsigned char Number)
{
	switch(Location)
	{
		case 1:
			P2_4=1;
			P2_3=1;
			P2_2=1;
			break;
		case 2:
			P2_4=1;
			P2_3=1;
			P2_2=0;
			break;
		case 3:
			P2_4=1;
			P2_3=0;
			P2_2=1;
			break;
		case 4:
			P2_4=1;
			P2_3=0;
			P2_2=0;
			break;
		case 5:
			P2_4=0;
			P2_3=1;
			P2_2=1;
			break;
		case 6:
			P2_4=0;
			P2_3=1;
			P2_2=0;
			break;
		case 7:
			P2_4=0;
			P2_3=0;
			P2_2=1;
			break;
		case 8:
			P2_4=0;
			P2_3=0;
			P2_2=0;
			break;
	}
	//��ѡ
	P0=X[Number];
	//��Ӱ
	Delay(1);
	
	P0=0x00;

	
	
}

void main()
{
	unsigned char nums = 10;
	clock=9999;
	
	while(1)
	{
		//Delay(1000);
		//if(clock>=0)
		//{
			//ȡclockÿһ��λ
		/*temp[0]=clock/1000;
		temp[1]=(clock/100)%10;
		temp[2]=(clock/10)%10;
		//temp[3]=(clock/10)%10;
		temp[3]=clock%10;*/
			
		//}
		temp[0]=clock/1000;
		Nixie(3,nums/2);
		Nixie(2,1);
		/*Nixie(2,temp[1]);
		Nixie(3,temp[2]);
		Nixie(4,temp[3]);
		//Nixie(5,temp[4]);
		if(clock>=99999){
			break;
		
		}*/
		//clock++;
	}
}	