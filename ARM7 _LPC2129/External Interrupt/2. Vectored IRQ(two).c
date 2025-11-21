// EINT0 (slot0) & EINT1(slot1) as Vectored IRQ (select both as falling edge sensitivity)

#include <LPC21xx.h>
#define led1 1<<17
#define led2 1<<18
void eint0_isr(void) __irq 
{
    EXTINT = 1;           // Clear EINT0 flag
	IOSET0 = (1 << 10);   // Turn ON LED1
    VICVectAddr = 0;      // Acknowledge
}

void eint1_isr(void) __irq 
{
    EXTINT = 1;           // Clear EINT1 flag
	IOSET0 = (1 << 10);   // Turn ON LED2
    VICVectAddr = 0;      // Acknowledge
}

int main() 
{
    PINSEL1 |= 0x01;         // P0.16 -> EINT0
	PINSEL0 |= 2<<28;		 // p0.14 -> EINT1
	IODIR0 = led1|led2;      // LED output

    VICIntSelect &= ~((1 << 14)|(1<<15));		// As vectored IRQ

	VICVectCntl0 = 0x20 | 14;
    VICVectAddr0 = (unsigned long)eint0_isr;

	VICVectCntl1 = 0x20 | 15;
    VICVectAddr1 = (unsigned long)eint1_isr;

    EXTMODE = 0x03;          // edge sensitive
    EXTPOLAR = 0x00;         // falling edge

	VICIntEnable = (1 << 14)|(1<<15); 
    

    while(1);
}

