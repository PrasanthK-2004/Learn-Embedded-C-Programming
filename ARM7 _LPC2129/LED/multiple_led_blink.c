//Blink Multiple LEDs

#include <LPC21xx.h>

void delay(int d) {
    int i, j;
    for(i=0; i<d; i++)
        for(j=0; j<10000; j++);
}

int main(void) {
    int leds = (1<<8) | (1<<9) | (1<<10) | (1<<11);  // 4 LEDs
    IODIR0 |= leds;

    while(1) {
        IOSET0 = leds;   // All ON
        delay(300);
        IOCLR0 = leds;   // All OFF
        delay(300);
    }
}
