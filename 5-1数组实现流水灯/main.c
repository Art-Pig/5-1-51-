#include <REGX52.H>
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}


void main(){
	int a[9]={0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	int i;
	while(1){
		for(i =0; i<9;i++){
			P2 = a[i];
			delay_ms(500);
			P2 = 0xff;
			//delay_ms(500);����ʱһ��Ϊʲô�ҵ�C51��������н���е�ֻѭ����˸��һ��
		}
	}
}

			
		
	
	
	
	
