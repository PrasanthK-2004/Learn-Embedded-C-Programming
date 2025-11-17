#include <LPC21xx.h>
#include "lcd.h"
int main() {
    lcd_init();
    lcd_string("WELCOME TO ARM7");
    delay(500);

    while(1) {
	int i;
        for(i=0; i<16; i++) {
            lcd_cmd(0x18);  // Shift Left
            delay(200);
        }
        for(i=0; i<16; i++) {
            lcd_cmd(0x1C);  // Shift Right
            delay(200);
        }
    }
}
