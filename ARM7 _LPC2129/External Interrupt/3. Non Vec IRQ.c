// EINT0 as Non Vectored IRQ (select falling sensitivity)

#include <LPC21xx.h>
#define led 1<<17;
void eint0_isr(void) __irq;

int main() 
{	__enable_irq();
    	PINSEL1  = 0x01;         // P0.16 -> EINT0
	IODIR0 = led;   // LED output

    	VICIntSelect  =0;		// As vectored IRQ
    	VICDefVectAddr = (unsigned long)eint0_isr;

    	EXTMODE = 0x01;          // edge sensitive
    	EXTPOLAR = 0;            // falling edge

	VICIntEnable |= (1 << 14); 
    

    while(1)
    {	int i;
    	IOSET0 = led;
	for(i=0;i<500000;i++);
	IOCLR0 = led;
	for(i=0;i<500000;i++);
    }

}


void eint0_isr(void) __irq 
{
    	EXTINT = 0x01;           // Clear EINT0 flag
	IOSET0 = led;         // Turn ON LED
    	VICVectAddr = 0;      // Acknowledge
}
