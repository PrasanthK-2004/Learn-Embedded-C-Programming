// toggle led
// while pressing switch led blinks when released led off

#include <LPC21xx.h>

void delay_ms(int ms) {
    int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 12000; j++);
}

int main() 
{
    IODIR0 = (1 << 10);    // P0.10 as LED output
    IODIR0 &= ~(1 << 14);   // P0.14 as switch input

    while (1) 
	{
        if (((IOPIN0 & (1 << 14)))==0) 	   // When switch pressed led blinks
		{
            IOSET0 = (1 << 10);
            delay_ms(100);
            IOCLR0 = (1 << 10);
            delay_ms(100);
        }
	    else
            IOCLR0 = (1 << 10);
		while ((IOPIN0 & (1 << 0)==0)); // Wait for switch release (Debounce delay)
    }
}


/*   ALTERNATE METHOD

#include <LPC21xx.h>

void delay_ms(int ms) {
    int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 12000; j++);
}

int main() {
    int led_state = 0;

    IODIR0 |= (1 << 10);     // Configure P0.10 as LED output
    IODIR0 &= ~(1 << 0);     // Configure P0.0 as switch input

    while (1) {
        if ((IOPIN0 & (1 << 0))==0) {     // If switch pressed
            led_state ^= 1;          // Toggle LED state
            if (led_state)
                IOSET0 = (1 << 10);  // LED ON
            else
                IOCLR0 = (1 << 10);  // LED OFF

            while ((IOPIN0 & (1 << 0)==0)); // Wait for switch release (Debounce delay)
        }
    }
}
*/
