// LED Binary Counter (0–255)

#include <LPC21xx.h>

void delay(int t) {
    int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<12000;j++);
}

int main() {
    int leds = (0xFF << 8);
    IODIR0 = leds;

    while(1) 
			{
				int count;
        for(count = 0; count < 256; count++) {
            IOCLR0 = leds;
            IOSET0 = (count << 8);
            delay(200);
        }
    }
}
