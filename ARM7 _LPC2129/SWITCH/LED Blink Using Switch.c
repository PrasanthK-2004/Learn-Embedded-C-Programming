// LED Blink Using Switch (Direct Register Access)

#include <LPC21xx.h>

int main() 
{
    // Configure P0.10 as output (LED)
    IODIR0 = (1 << 10);
    
    // Configure P0.0 as input (Switch)
		IOPIN0 = 1;
    while (1) 
    {
        if (IOPIN0 & (1))           // If switch is pressed
          IOSET0 = (1 << 10);    // Turn ON LED
          else
            IOCLR0 = (1 << 10);    // Turn OFF LED
        
    }
}
