#include <LPC21xx.h>

#define RS (1 << 8)
#define EN (1 << 9)
#define DATA 0xFF

void delay(unsigned int t){
    unsigned int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<1000;j++);
}

void lcd_cmd(unsigned char cmd){
    IOCLR0 = DATA;         // Clear P0.0-P0.7
    IOSET0 = cmd;        // Put cmd on P0.0-7
    IOCLR0 = RS;           // RS = 0
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

void lcd_data(unsigned char data){
    IOCLR0 = DATA;
    IOSET0 = data;
    IOSET0 = RS;           // RS = 1
    IOSET0 = EN; delay(1);
    IOCLR0 = EN;
    delay(2);
}

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

int main(){
	int count=0;
    lcd_init();

    IODIR0 &= ~(1 << 16);   // P0.16 as INPUT
	lcd_init();
	lcd_string(" ");
	lcd_cmd(0x80);
    lcd_string("COUNT:");
    lcd_cmd(0xC0);
		lcd_display_number(count);

    while(1) 
	{
        if((IOPIN0 & (1 << 16))==0) 	  // Switch pressed
		{  
            count++;
            lcd_cmd(0xC0);
            lcd_display_number(count);
            delay(500);
						while((IOPIN0 & (1 << 16))==0);
        }
    }
}
