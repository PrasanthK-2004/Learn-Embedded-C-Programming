#include <LPC21xx.h>

#define RS   (1 << 8)        // P0.8
#define EN   (1 << 9)        // P0.9
#define DATA 0xFF            // P0.0–P0.7

char msg[] = "WELCOME TO ARM7   ";  // Extra spaces for smooth scroll

void delay(unsigned int count) {
    unsigned int i,j;
    for(i=0; i<count; i++)
        for(j=0; j<5000; j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = RS | EN | DATA;
    IOSET0 = cmd;
    IOCLR0 = RS;   
    IOSET0 = EN;
    delay(2);
    IOCLR0 = EN;
    delay(5);
}

void lcd_data(unsigned char data) {
    IOCLR0 = RS | EN | DATA;
    IOSET0 = data;
    IOSET0 = RS;   
    IOSET0 = EN;
    delay(2);
    IOCLR0 = EN;
    delay(5);
}

void lcd_init(void) {
    IODIR0 |= (RS | EN | DATA);
    delay(20);
    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x01);   // Clear display
    lcd_cmd(0x06);   // Auto increment
    delay(10);
}

void lcd_string(char *str) {
    while(*str)
        lcd_data(*str++);
}

// Rotate string left by 1 character (circular)
void rotate_left(char *str) {
    char first = str[0];
    int i = 0;
    while(str[i] != '\0') {
        str[i] = str[i+1];
        i++;
    }
    str[i-1] = first;  // Put first char at the end
}

int main() {
    lcd_init();

    while(1) {
        lcd_cmd(0x80);      // Start at first line
        lcd_string(msg);    // Display current string
        delay(100);         // Adjust scroll speed
        rotate_left(msg);   // Rotate string circularly
    }
}
