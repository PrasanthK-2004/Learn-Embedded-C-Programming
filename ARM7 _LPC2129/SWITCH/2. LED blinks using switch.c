// while pressing switch led blinks when released led off

#include <LPC21xx.h>

void delay_ms(int ms) {
    int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 12000; j++);
}

int main() {
    IODIR0 = (1 << 10);    // P0.10 as LED output
    IODIR0 &= ~(1 << 14);   // P0.14 as switch input

    while (1) {
        if (((IOPIN0 & (1 << 14)))==0) 	   //when switch pressed led blinks
		{
            IOSET0 = (1 << 10);
            delay_ms(100);
            IOCLR0 = (1 << 10);
            delay_ms(100);
        }
	    else 
		{
            IOCLR0 = (1 << 10);
        }
    }
}
