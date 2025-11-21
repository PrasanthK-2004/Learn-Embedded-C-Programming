// EINT0 and EINT1 as Non Vectored IRQ (both falling edge sensitivity)

#include <LPC21xx.h>
#define led1 1<<17
#define led2 1<<18
void eint_isr(void) __irq;

int main() 
{	__enable_irq();
    	PINSEL1 &= ~(3<<0);    // clear bits for P0.16
	PINSEL1 |=  (1<<0);    // set EINT0 = 01

	PINSEL0 &= ~(3<<28);   // clear bits for P0.14
	PINSEL0 |=  (2<<28);   // set EINT1 = 10

	IODIR0  = led1|led2;      // LED output

    	VICIntSelect  =0;		// As IRQ
    	VICDefVectAddr = (unsigned long)eint_isr;

    	EXTMODE = 0x03;          // edge sensitive
    	EXTPOLAR = 0;            // falling edge

	VICIntEnable |= (1 << 14)|(1<<15); 
    

    while(1)
    {
    	IOSET0 = led1|led2;
    }

}


void eint_isr(void) __irq 
{	if((VICIRQStatus>>14)&1)
	{	int i,j;					     
    		EXTINT = 0x01;        // Clear EINT0 flag
		IOCLR0 = led1;         // Turn OFF LED1


    		for(i=0;i<500;i++)


        		for(j=0;j<12000;j++);
	}
	if((VICIRQStatus>>15)&1)
	{	int i,j;
		EXTINT = 0x02;        // Clear EINT1 flag
		IOCLR0 = led2;         // Turn OFF LED2
		for(i=0;i<500;i++)


        		for(j=0;j<12000;j++);
	}      
    	VICVectAddr = 0;      // Acknowledge
}
