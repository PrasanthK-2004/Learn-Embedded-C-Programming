#include <LPC21xx.h>

#define LCD_DATA 0xFF 
#define RS (1 << 8)
#define EN (1 << 9)

void delay(unsigned int t) {
    unsigned int i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < 1000; j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = LCD_DATA;            // Clear data pins
    IOSET0 = (cmd << 8);          // Send command
    IOCLR0 = RS;                  // RS = 0 ? Command
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_data(unsigned char data) {
    IOCLR0 = LCD_DATA;
    IOSET0 = (data << 8);
    IOSET0 = RS;                  // RS = 1 ? Data
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_init() {
    IODIR0 |= LCD_DATA | RS | EN;
    delay(20);
    lcd_cmd(0x38);  // 8-bit, 2-line, 5x7
    lcd_cmd(0x0C);  // Display ON, Cursor OFF
    lcd_cmd(0x06);  // Entry mode
    lcd_cmd(0x01);  // Clear
}

void lcd_string(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_create_custom_char() {
	int i;
    unsigned char smiley[8] = {0x00, 0x0A, 0x00, 0x00, 0x11, 
	                           0x0E, 0x00, 0x00};

    lcd_cmd(0x40);  // Set CGRAM address for character 0

    for (i = 0; i < 8; i++)
        lcd_data(smiley[i]);  // Write pattern

    lcd_cmd(0x80);  // Return to DDRAM (line 1 position 0)
}

int main(void) {
    lcd_init();
    lcd_create_custom_char();

    lcd_string("Hello ");
    lcd_data(0);  // Display custom character 0 (smiley)
    while (1);
}
