#include <LPC21xx.h>

int main(void) {
    IODIR0 |= (0xF << 8);     // Configure P0.8?P0.11 as LED outputs
    IODIR0 &= ~(0xF << 0);    // Configure P0.0?P0.3 as switch inputs

    while (1) {
        if ((IOPIN0 & (1 << 0))==0) IOSET0 = (1 << 8); else IOCLR0 = (1 << 8);
        if ((IOPIN0 & (1 << 1))==0) IOSET0 = (1 << 9); else IOCLR0 = (1 << 9);
        if ((IOPIN0 & (1 << 2))==0) IOSET0 = (1 << 10); else IOCLR0 = (1 << 10);
        if ((IOPIN0 & (1 << 3))==0) IOSET0 = (1 << 11); else IOCLR0 = (1 << 11);
    }
}
