#include <LPC21xx.h>

#define LCD_DATA 0xFF
#define RS (1 << 8)
#define EN (1 << 9)

void delay(unsigned int t) {
    unsigned int i, j;
    for (i=0;i<t;i++) for(j=0;j<1000;j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = LCD_DATA;
    IOSET0 = cmd;
    IOCLR0 = RS;  // Command
    IOSET0 = EN; delay(20);
    IOCLR0 = EN;
    delay(20);
}

void lcd_data(unsigned char data) {
    IOCLR0 = LCD_DATA;
    IOSET0 = data;
    IOSET0 = RS;  // Data
    IOSET0 = EN; delay(20);
    IOCLR0 = EN;
    delay(20);
}

void lcd_init() {
    IODIR0 |= LCD_DATA | RS | EN;
    delay(20);
    lcd_cmd(0x38); // 8-bit, 2-line
    lcd_cmd(0x0C); // Display ON
    lcd_cmd(0x06); // Entry mode
    lcd_cmd(0x01); // Clear
}

// All 8 custom characters
unsigned char custom_chars[8][8] = {
    {0x00,0x0A,0x00,0x00,0x11,0x0E,0x00,0x00}, // 0 - Smiley
    {0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00}, // 1 - Heart
    {0x04,0x06,0x1F,0x06,0x04,0x00,0x00,0x00}, // 2 - Right Arrow
    {0x04,0x0C,0x1F,0x0C,0x04,0x00,0x00,0x00}, // 3 - Left Arrow
    {0x04,0x0E,0x1F,0x04,0x04,0x00,0x00,0x00}, // 4 - Up Arrow
    {0x04,0x04,0x1F,0x0E,0x04,0x00,0x00,0x00}, // 5 - Down Arrow
    {0x00,0x01,0x03,0x16,0x1C,0x08,0x00,0x00}, // 6 - Checkmark
    {0x00,0x11,0x0A,0x04,0x0A,0x11,0x00,0x00}  // 7 - Cross
};

void lcd_load_custom_chars() {
	int i,c;
    for(c=0; c<8; c++) {
        lcd_cmd(0x40 + (c*8)); // Set CGRAM address
        for(i=0;i<8;i++)
            lcd_data(custom_chars[c][i]);
    }
    lcd_cmd(0x80); // Return to DDRAM (line 1 pos 0)
		delay(5);
}

void lcd_display_custom_chars() {
	int i;
    lcd_cmd(0x80); // Line 1 start
    for(i=0;i<8;i++)
        lcd_data(i); // Display 0?7 chars

    lcd_cmd(0xC0); // Line 2 start
    for(i=0;i<8;i++)
        lcd_data(i); // Display again
}

int main(void) {
    lcd_init();
    lcd_load_custom_chars();
    lcd_display_custom_chars();
    while(1);
}
