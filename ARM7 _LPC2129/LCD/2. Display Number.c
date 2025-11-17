#include <LPC21xx.h>
#include "lcd.h"


void delay(unsigned int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_display_number(unsigned int);

int main() {
    unsigned int value = 1234;
    lcd_init();
    lcd_string("VALUE = ");
    lcd_display_number(value);
    while(1);
}
