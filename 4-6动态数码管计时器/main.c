/*
--------����----------
1.��д������ܶ�Ӧ�ַ����飬�����λ�ö�Ӧ����
2.��ʼ��P0��P2
3.��ʱ���ж�ʱ��
4.���
5.��զ�䣺
	������ϵ�ʱ��ȡ����ȡ�࣬��̬ɨ�裨��ʱ���ۿ������ķ�Χ��
****6.�����ܲ�Ҫ���Ѷ����λ�����ŷ���������������
-----------------------
*/
#include <REGX52.H>
//���������¶��壬
typedef unsigned int u16;
typedef unsigned char u8;


//�������ţ��������ϰ�ߣ���ֱ�Ӷ����Ų���
sbit ADDR0 = P2^4;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^2;

u8 i;
u16 clock =59999;

//�����������ʾ0~9������
u8 X[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0X7D,0x07,0x7F,0x6F};

//������ʱ���������������Ҫ��ʾֵ������ඨ��һ��������Խ��
u8 real[]={0x00,0x00,0x00,0x00,0x00,0x00};

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

//��ʱ����ʼ������
void time_init()
{
	TMOD &= 0xF0;//���ö�ʱ��0,ע��λ������ò�Ҫֱ�Ӹ�ֵ
	TMOD |= 0x01;
	TL0 = 0x18;  //0xFC18�����ԼΪ1ms��
	TH0 = 0xFC;
	TF0 = 0; //���TF0��־
	TR0=1;	//��ʼ��ʱ
	ET0 = 1;	//ʹ���ж�
	EA = 1;
	PT0 = 0;
	
}

//��ʱ���жϺ���
void time0() interrupt 1
{
	static u16 count;	//��̬���ݣ����ں����������ھֲ������������ں����ﲻ��������
	TL0 = 0x18;  //0xFC18�����ԼΪ1ms��
	TH0 = 0xFC;
	count++;									//count ����¼��ʱ�������˶��ٴ�1ms
	if(count==1000) //��ʱ1s
	{
		count=0;
		clock--;
	}
}


//��ʾ����ܺ���
void display()
{
	real[0]=X[clock/10000];  //�Զ���ĵ���ʱȡ����λ
	real[1]=X[clock/1000%10];
	real[2]=X[clock/100%10];
	real[3]=X[clock/10%10];
	real[4]=X[clock%10];
	for(i=0;i<5;i++){   //��ʾ�����
			switch(i)
		{
			case 0:ADDR0=1;ADDR1=1;ADDR2=1;P0=real[0];Delay(1);break;
			case 1:ADDR0=1;ADDR1=1;ADDR2=0;P0=real[1];Delay(1);break;
			case 2:ADDR0=1;ADDR1=0;ADDR2=1;P0=real[2];Delay(1);break;
			case 3:ADDR0=1;ADDR1=0;ADDR2=0;P0=real[3];Delay(1);break;
			case 4:ADDR0=0;ADDR1=1;ADDR2=1;P0=real[4];Delay(1);break;
			default:break;	
		}
		P0=0x00; //��Ӱ
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