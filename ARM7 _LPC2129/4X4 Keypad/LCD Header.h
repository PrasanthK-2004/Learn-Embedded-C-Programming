#include <LPC21xx.h>

#define RS (1 << 8)
#define EN (1 << 9)
#define DATA 0xFF 

void delay(unsigned int count) {
    unsigned int i, j;
    for(i = 0; i < count; i++)
        for(j = 0; j <1000; j++);
}

void lcd_cmd(unsigned char cmd) {
    IOCLR0 = RS;
    IOCLR0 = DATA;
    IOSET0 = (cmd << 8);
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(5);
}

void lcd_data(unsigned char data) {
    IOSET0 = RS;
    IOCLR0 = DATA;
    IOSET0 = (data << 8);
    IOSET0 = EN;
    delay(1);
    IOCLR0 = EN;
    delay(5);
}

void lcd_init(void) {
    IODIR0 = RS | EN | DATA;
    delay(20);
    lcd_cmd(0x38);  // 8-bit, 2-line
    lcd_cmd(0x0C);  // Display ON, cursor OFF
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x01);  // Clear display
    lcd_cmd(0x80);  // Cursor at line 1
}

void lcd_string(char *str) {
    while(*str)
        lcd_data(*str++);
}

void lcd_display_number(int num) 
{
	unsigned char arr[5];
	signed int i=0;
    if (num == 0) 
	{
        lcd_data('0');
        return;
    }
	else
	{
		if (num < 0) 
		{
        	lcd_data('-');
        	num = -num;
    	}
		while(num>0)
		{
			arr[i++]=num%10;
			num=num/10;
		}
    	for(i=i-1;i>=0;i--)
			lcd_data(arr[i]+'0');
	}
}
