// Pattern print on led using switches
// Switch1 - left shift	led
// Switch2 - right shift led 
// Switch3 - alternate led
#include <LPC21xx.h>

#define LEDS   (0xF << 8)   // LEDs on P0.8?P0.11
#define SW1    (1 << 0)     // Switch 1 on P0.0
#define SW2    (1 << 1)     // Switch 2 on P0.1
#define SW3    (1 << 2)     // Switch 3 on P0.2

void delay_ms(int ms) {
    int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 12000; j++);
}

int main() {
    IODIR0 |= LEDS;                  // Set P0.8?P0.11 as output (LEDs)
    IODIR0 &= ~(SW1 | SW2 | SW3);    // Set P0.0?P0.2 as input (Switches)

    while (1) {
        int i;

        if ((IOPIN0 & SW1)==0) {          // Pattern 1: Left shift
            for (i = 8; i <= 11; i++) {
                IOSET0 = (1 << i);
                delay_ms(300);
                IOCLR0 = (1 << i);
            }
        }

        if ((IOPIN0 & SW2)==0) {          // Pattern 2: Right shift
            for (i = 11; i >= 8; i--) {
                IOSET0 = (1 << i);
                delay_ms(300);
                IOCLR0 = (1 << i);
            }
        }

        if ((IOPIN0 & SW3)==0) {          // Pattern 3: Alternate LEDs
            IOSET0 = (1 << 8) | (1 << 10);
            IOCLR0 = (1 << 9) | (1 << 11);
            delay_ms(400);
            IOSET0 = (1 << 9) | (1 << 11);
            IOCLR0 = (1 << 8) | (1 << 10);
            delay_ms(400);
        }
    }
}
