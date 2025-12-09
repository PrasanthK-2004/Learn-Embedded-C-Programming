// Running LED Pattern (Left to Right)

#include <LPC21xx.h>

void delay(int t) {
    int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<12000;j++);
}

int main() 
{
    IODIR0 |= (0xFF<<8);  // LEDs on P0.8–P0.15

    while(1) 
			{
		int i;
        for(i=8; i<16; i++) {
            IOSET0 = (1 << i);
            delay(500);
            IOCLR0 = (1 << i);
        }
    }
}


