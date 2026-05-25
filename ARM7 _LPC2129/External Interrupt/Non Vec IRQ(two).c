#include <LPC21xx.h>

#define led1 (1<<17)
#define led2 (1<<18)

void eint_isr(void) __irq;

int main()
{
    PINSEL1 |= (1<<0);        // EINT0 P0.16
    PINSEL0 |= (2<<28);       // EINT1 P0.14

    IODIR0 = led1 | led2;

    VICIntSelect = 0;         // IRQ mode
    VICDefVectAddr = (unsigned long)eint_isr;

    EXTMODE = 0x03;           // edge sensitive
    EXTPOLAR = 0x00;          // falling edge

    VICIntEnable |= (1<<14) | (1<<15);

    IOCLR0 = led1 | led2;

    while(1);
}

void eint_isr(void) __irq
{
    if(EXTINT & 0x01)
    {
        EXTINT = 0x01;
        IOSET0 = led1;
    }

    if(EXTINT & 0x02)
    {
        EXTINT = 0x02;
        IOSET0 = led2;
    }

    VICVectAddr = 0;
}
