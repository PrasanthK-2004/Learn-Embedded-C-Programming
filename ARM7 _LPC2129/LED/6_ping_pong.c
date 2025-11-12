// Ping-Pong Effect (Left ? Right ? Left)

#include <LPC21xx.h>

void delay(int t) {
    int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<12000;j++);
}

int main() {
    int i;
    IODIR0 |= (0xFF << 8);   // LEDs on P0.8–P0.15

    while(1) {
        // Left to Right
        for(i=8; i<16; i++) {
            IOSET0 = (1 << i);
            delay(150);
            IOCLR0 = (1 << i);
        }

        // Right to Left
        for(i=15; i>=8; i--) {
            IOSET0 = (1 << i);
            delay(150);
            IOCLR0 = (1 << i);
        }
    }
}
