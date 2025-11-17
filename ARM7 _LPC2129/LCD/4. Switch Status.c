#include <LPC21xx.h>
#include "lcd.h"
int main() {
    lcd_init();
    IOPIN0 = (1 << 14);  // P0.14 = input switch
    lcd_string("SWITCH:");

    while(1) {
        lcd_cmd(0xC0);
        if(IOPIN0 & (1 << 14))
            lcd_string("SWITCH PRESSED  ");
        else
            lcd_string("SWITCH RELEASED ");
        delay(300);
    }
}
