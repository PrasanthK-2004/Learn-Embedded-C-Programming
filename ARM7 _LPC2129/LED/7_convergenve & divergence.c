// Convergence and Divergence of led

#include<lpc21xx.h>
#define leds 0xff

void delay_ms(int ms) {
    int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 12000; j++);
}
int main() {
    int i,j;

    IODIR0 =leds;    // Configure P0.0 - p0.7 as LED output
    IOSET0 =leds;    
	while(1)
	{
		for(i=0,j=7;i<8;i++,j--)
		{
			IOSET0 = 1<<i | 1<<j;
			delay_ms(500);
			IOCLR0 = 1<<i | 1<<j;
			delay_ms(500);
		}
	}
}
