#include <LPC21xx.h>
#include "lcd.h"

int main()
{
    unsigned int count = 0;
    IOPIN0 = (1 << 14); // Switch input
    lcd_init();
    lcd_string("COUNT:");
    lcd_cmd(0xC0);

    while(1) 
	{
        if(IOPIN0 & (1 << 14)) 	  // Switch pressed
		{  
            count++;
            lcd_cmd(0xC0);
            lcd_display_number(count);
            delay(500);  
        }
    }
}
