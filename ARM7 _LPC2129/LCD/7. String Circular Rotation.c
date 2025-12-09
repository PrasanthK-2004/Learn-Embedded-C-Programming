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
}

void lcd_data(unsigned char data) {
    IOCLR0 = RS | EN | DATA;
    IOSET0 = data;
    IOSET0 = RS;   
    IOSET0 = EN;
    delay(2);
    IOCLR0 = EN;
}

void lcd_init(void) {
    IODIR0 |= (RS | EN | DATA);
    delay(20);
    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x01);   // Clear display
	  lcd_cmd(0x02);   // Set cursor to home position
    delay(10);
}

void lcd_string(char *str) {
    while(*str)
        lcd_data(*str++);
}

// Rotate string right by 1 character (circular)
void rotate_right(char *str) {
	int i;
    int len = 0;
    char last;

    // Find length
    while(str[len] != '\0') len++;

    last = str[len - 1];       // Save last character

    for(i = len - 1; i > 0; i--) {
        str[i] = str[i - 1];   // Shift right
    }

    str[0] = last;             // Put last char at front
}


int main() {
    lcd_init();

    while(1) {
        lcd_cmd(0x80);      // Start at first line
        lcd_string(msg);    // Display current string
        delay(100);         // Adjust scroll speed
        rotate_right(msg);  // Rotate string circularly to right
    }
}
