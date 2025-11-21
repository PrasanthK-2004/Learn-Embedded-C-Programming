// EINT0 as Vectored IRQ (allocate slot-0 ,select low level sensitivity)

#include <LPC21xx.h>
#define led 1<<17;
void eint0_isr(void) __irq;

int main() 
{
    	PINSEL1 |= 1;         // P0.16 -> EINT0
	IODIR0 = led;   // LED output

    	VICIntSelect &= ~(1 << 14);		// As vectored IRQ
	VICVectCntl0 = 0x20 | 14;
    	VICVectAddr0 = (unsigned long)eint0_isr;

    	EXTMODE = 0;          // level sensitive
    	EXTPOLAR = 0;         // low level

	VICIntEnable = (1 << 14); 
    

    while(1);
}


void eint0_isr(void) __irq 
{
    	EXTINT = 1;           // Clear EINT0 flag
	IOSET0 = led;   // Turn ON LED
    	VICVectAddr = 0;      // Acknowledge
}
