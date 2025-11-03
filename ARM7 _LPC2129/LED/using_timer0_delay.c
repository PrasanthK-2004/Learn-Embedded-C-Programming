// LED Blink Using Timer0 Delay for 500 microsecond

#include <LPC21xx.h>

void delay_ms(int ms) {
    T0PR = 15000 - 1;       // Prescale for 1ms at 15MHz PCLK
    T0TCR = 0x03;           // Reset timer and then Enable timer
    while(T0TC < ms);       // Wait until Timer Counter reaches required value
    T0TCR = 0x00;           // Stop timer
}

int main() {
    IODIR0 = (1 << 10);   // LED pin output

    while(1) {
        IOSET0 = (1 << 10); // LED ON
        delay_ms(500);
        IOCLR0 = (1 << 10); // LED OFF
        delay_ms(500);
    }
}
