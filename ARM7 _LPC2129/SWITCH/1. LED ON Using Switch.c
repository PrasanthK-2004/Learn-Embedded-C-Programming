#include <LPC21xx.h>


int main() {

    // Configure P0.10 as output (LED)

    IODIR0 |= (1 << 10);

    

    // Configure P0.14 as input (Switch)

    IODIR0 &= ~(1 << 14);

    

    while (1) {

        if ((IOPIN0 & (1 << 14))==0) {   // If switch is pressed

            IOSET0 = (1 << 10);    // Turn ON LED

        } else {

            IOCLR0 = (1 << 10);    // Turn OFF LED

        }

    }

}
