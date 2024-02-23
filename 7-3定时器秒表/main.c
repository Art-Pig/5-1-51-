#include <REGX52.H>
#include <REGX52.H>
//���������¶��壬
typedef unsigned int u16;
typedef unsigned char u8;


//�������ţ��������ϰ�ߣ���ֱ�Ӷ����Ų���
sbit ADDR0 = P2^4;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^2;

u8 i;
u8 clock =0;

//�����������ʾ0~9������
u8 X[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0X7D,0x07,0x7F,0x6F};

//������ʱ���������������Ҫ��ʾֵ������ඨ��һ��������Խ��
u8 real[]={0x00,0x00,0x00};
//�����ʱ������Ӱ��ע�ⲻ���ö�ʱ����Ӱ����Ϊ��ʱ����Ҫռ�üĴ�����
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
	TL0 = 0x18;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
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

void Timer0_Init()		//1����@11.0592MHz
{
	
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x18;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	EA = 1;
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;	//ʹ�ܶ�ʱ��0�ж�
	PT0 = 0;
}


//��ʾ����ܺ���
void display()
{
	real[0]=X[clock/10];  //�Զ���ĵ���ʱȡ����λ
	real[1]=X[clock%10];
	
	for(i=0;i<5;i++){   //��ʾ�����
			switch(i)
		{
			case 0:ADDR0=0;ADDR1=1;ADDR2=1;P0=real[1];Delay(10);break;
			case 1:ADDR0=1;ADDR1=0;ADDR2=0;P0=real[0];Delay(10);break;
			
			default:break;	
		}
		P0=0x00; //��Ӱ
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

