#include <LPC21xx.h>

#define RS   (1 << 8)        // P0.8
#define EN   (1 << 9)        // P0.9
#define DATA 0x000000FF      // P0.0–P0.7

void delay(unsigned int count) {
    unsigned int i,j;
    for(i=0; i<count; i++)
        for(j=0; j<5000; j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = RS | EN | DATA;   // Clear all pins
    IOSET0 = (cmd & 0xFF);     // command on P0.0–P0.7
    IOCLR0 = RS;               // RS=0 (command)
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_data(unsigned char data) {
    IOCLR0 = RS | EN | DATA;
    IOSET0 = (data & 0xFF);    // data on P0.0–P0.7
    IOSET0 = RS;               // RS=1 (data)
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_init(void) {
    IODIR0 |= (RS | EN | DATA);

    delay(20);
    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x06);   // Auto increment
    lcd_cmd(0x01);   // Clear display
    lcd_cmd(0x80);   // Cursor at 1st line
    delay(5);
}

void lcd_string(char *str) {
    while(*str)
        lcd_data(*str++);
}

// ======================= MAIN =======================

int main() {

    lcd_init();
    lcd_string("WELCOME TO ARM7");
    delay(500);

    while(1) {
        int i;

        // Shift LEFT 16 times
        for(i = 0; i < 16; i++) {
            lcd_cmd(0x18);      // Display shift LEFT
            delay(200);
        }

        // Shift RIGHT 16 times
        for(i = 0; i < 16; i++) {
            lcd_cmd(0x1C);      // Display shift RIGHT
            delay(200);
        }
    }
}
