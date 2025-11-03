// LED Controlled by Switch

#include <LPC21xx.h>

int main() {
    IODIR0 = (1 << 10);   // LED output
    IODIR0 &= ~(1);  // Switch input on P0.0

    while(1) {
        if(IOPIN0 & 1)  // Switch pressed (logic HIGH)
            IOSET0 = (1 << 10);
        else
            IOCLR0 = (1 << 10);
    }
}
