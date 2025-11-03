// Alternating LED Pattern (Even/Odd)

#include <LPC21xx.h>

void delay(int t) {
    int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<12000;j++);
}

int main() {
    IODIR0 = (0xFF << 8);

    while(1) {
        IOSET0 = (0xAA << 8);  // 10101010 
        IOCLR0 = (0x55 << 8);  // 01010101 
        delay(400);

        IOSET0 = (0x55 << 8);  // 01010101 
        IOCLR0 = (0xAA << 8);  // 10101010
        delay(400);
    }
}
