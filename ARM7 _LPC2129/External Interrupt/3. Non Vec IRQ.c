#include <LPC21xx.h>

#define LED (1<<17)

void eint0_isr(void) __irq;

int main()
{
    PINSEL1 |= 0x01;          // P0.16 -> EINT0
    IODIR0 = LED;             // LED output

    VICIntSelect &= ~(1 << 14);   // Select EINT0 as IRQ

    VICDefVectAddr = (unsigned long)eint0_isr;

    EXTMODE = 0x01;           // Edge sensitive
    EXTPOLAR = 0x00;          // Falling edge

    VICIntEnable |= (1 << 14);

    while(1);
}

void eint0_isr(void) __irq
{
    EXTINT = 0x01;            // Clear EINT0 interrupt flag

    IOSET0 = LED;             // LED ON

    VICVectAddr = 0x00;       // Acknowledge interrupt
}
