// Two switches controlling one LED
// Switch1 (P0.0) ? Turn LED ON
//Switch2 (P0.1) ? Turn LED OFF

#include <LPC21xx.h>

int main(void) {
    IODIR0 |= (1 << 10);           // Configure P0.10 as LED output
    IODIR0 &= ~((1 << 0) | (1 << 1)); // Configure P0.0 and P0.1 as switch inputs

    while (1) {
        if ((IOPIN0 & (1 << 0))==0)     // Switch1 pressed
            IOSET0 = (1 << 10);    // LED ON

        if (((IOPIN0 & (1 << 1))==0) || ((IOPIN0 & (1 << 0))==1))     // Switch2 pressed or Switch1 released
            IOCLR0 = (1 << 10);    // LED OFF
    }
}
