// Simple LED Blink – Direct Register Access

#include<LPC21xx.h>   // Header for LPC2129

void delay_ms(count) 
{
    int i, j;
    for(i=0; i<count; i++)
        for(j=0; j<12000; j++);  // Rough delay loop
}

int main() 
{
    IODIR0 = (1 << 10);   // Configure P0.10 as Output

    while(1) 
		{
        IOSET0 = (1 << 10);  // Turn ON LED
        delay_ms(500);

        IOCLR0 = (1 << 10);  // Turn OFF LED
        delay_ms(500);
    }
}
