#include <LPC21xx.h>

#define RS (1 << 8)
//#define RW (1 << 1)
#define EN (1 << 9)
#define DATA 0xFF 

void delay(unsigned int count) {
    unsigned int i, j;
    for(i = 0; i < count; i++)
        for(j = 0; j < 1000; j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = DATA;
    IOSET0 = cmd;
    IOCLR0 = RS;
    //IOCLR0 = RW;
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_data(unsigned char data) {
    IOCLR0 = DATA;
    IOSET0 = data;
    IOSET0 = RS;
    //IOCLR0 = RW;
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_string(const char *str) {
    while(*str) {
        lcd_data(*str++);
    }
}

void lcd_init(void) {
	lcd_cmd(0x01);
	lcd_cmd(0x02);
    lcd_cmd(0x0C);  // Display ON, cursor OFF
	lcd_cmd(0x38);  // 8-bit mode
    lcd_cmd(0x06);  // Auto-increment
    delay(2);
}

int main() {
    IODIR0 = RS | EN | DATA;

    lcd_init();
    lcd_cmd(0x80);  // First line
    lcd_string("Hello");

    lcd_cmd(0xC0);  // Second line
    lcd_string("PRASANTH");

    //while(1);
}
