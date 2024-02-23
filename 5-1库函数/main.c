#include <REGX52.H>
#include <INTRINS.H>
unsigned char aa;
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}

void main(){
	aa = 0xfe;
	while(1){
		P2 = aa;
		aa = _crol_(aa,1);
		delay_ms(500);
	}
}
		
	
