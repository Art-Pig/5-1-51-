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
	//��������Ϊ2��������K3��������ȷ
	while(1)
	{
	//����һ����ʼֵ��������ܱ��֡���
		number=5;
		P0=0x40;
	
		P3=0xff;
		P2 = 0xff;
		//����

		//if�жϣ�Ϊ���������������Ӧ��ֵ
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

		//˵������û���£�number���ǳ�ʼֵ
		if(number==5){
			P0=0x40;
			Delay(1);
			P2=0xff;
		
		
		}

		//һ��������ȷ�������������ʾP��P2^0����
		else if(number==password)
		{
			P0=0x73;
			Delay(1);
	
			P2 = 0x7f;
			
		}

		//���������������������������������ʾE��P2^0����
		else if(number==0||number==1||number==3)  
		{
			P0=0x79;
			Delay(1);
			P2=0xff;
		
		}
		//����һ���ٰ��£��ٴ�ѭ��
		while(P3==0xff);
	}

}