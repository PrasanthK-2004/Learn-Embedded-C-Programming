#include <LPC21xx.h>
#include "lcd.h"

int main() {
    unsigned int count = 0;
    lcd_init();
    lcd_string("Counter:");
    lcd_cmd(0xC0); // 2nd line

    while(1) {
        lcd_cmd(0xC0);      // Set cursor again at 2nd line
        lcd_display_number(count);
        delay(500);
        count++;
        if(count > 9999) count = 0;
    }
}
