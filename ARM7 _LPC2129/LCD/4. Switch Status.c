#include <LPC21xx.h>

#define RS (1 << 8)
#define EN (1 << 9)
#define DATA 0xFF

//------------------ DELAY --------------------
void delay(unsigned int t){
    unsigned int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<1000;j++);
}

//------------------ LCD COMMAND ----------------
void lcd_cmd(unsigned char cmd){
    IOCLR0 = DATA;         // Clear P0.0-P0.7
    IOSET0 = cmd;        // Put cmd on P0.0-7
    IOCLR0 = RS;           // RS = 0
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

//------------------ LCD DATA --------------------
void lcd_data(unsigned char data){
    IOCLR0 = DATA;
    IOSET0 = data;
    IOSET0 = RS;           // RS = 1
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

//------------------ LCD INIT ---------------------
void lcd_init(){
    IODIR0 |= DATA | RS | EN;   // LCD pins output
    delay(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
	  lcd_cmd(0x06);
    lcd_cmd(0x80);
}

void lcd_string(char *p){
    while(*p) lcd_data(*p++);
}

//------------------ MAIN -------------------------
int main(){
    lcd_init();

    IODIR0 &= ~(1 << 16);   // P0.16 as INPUT
	lcd_string("        ");  // Clear line
	lcd_cmd(0x80);
    lcd_string("SWITCH:");

    while(1){
        lcd_cmd(0xC0);

        if((IOPIN0 & (1 << 16))==0)
            lcd_string("PRESSED");
        else
            lcd_string("RELEASED");

        delay(300);
    }
}
