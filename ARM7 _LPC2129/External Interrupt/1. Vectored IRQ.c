#include <LPC21xx.h>

#define LED (1 << 17)

void eint0_isr(void) __irq;

int main()
{
    PINSEL1 |= (1 << 0);   // P0.16 -> EINT0

    IODIR0 |= LED;

    // VIC configuration (Vectored IRQ slot 0)
    VICIntSelect &= ~(1 << 14);      // IRQ (not FIQ)
    VICVectCntl0 = (1 << 5) | 14;    // enable slot 0, EINT0
    VICVectAddr0 = (unsigned long)eint0_isr;

    // External interrupt config
    EXTMODE = 1;     // edge triggered
    EXTPOLAR = 0;    // falling edge

    VICIntEnable = (1 << 14);

    while(1);
}

void eint0_isr(void) __irq
{
    EXTINT = (1 << 0);     // clear interrupt flag

    IOSET0 = LED;          // LED ON

    VICVectAddr = 0;       // acknowledge VIC
}
