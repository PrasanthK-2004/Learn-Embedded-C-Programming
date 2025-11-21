#include<lpc21xx.h>
#include"lcd.h"

#define c0 (IOPIN1 & (1<<20))
#define c1 (IOPIN1 & (1<<21))
#define c2 (IOPIN1 & (1<<22))
#define c3 (IOPIN1 & (1<<23))

#define r0 1<<16
#define r1 1<<17
#define r2 1<<18
#define r3 1<<19

unsigned int keypad[4][4] = { 
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

int keyscan(void)
{
	unsigned char row_val,col_val;
	PINSEL2 |=0x00;
	IODIR1 |=r0|r1|r2|r3;

	while(1)
	{
	 	IOCLR1 |=r0|r1|r2|r3;
		IODIR1 |= c0|c1|c2|c3;

		while((c0&&c1&&c2&&c3)==1);  // wait for keypad press
		// Testing row0
		IOCLR1 |=r0;
		IOSET1 =r1|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
		 	row_val =0;
			break;
		}

		// Testing row1
		IOCLR1 |=r1;
		IOSET1 =r0|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
		 	row_val =1;
			break;
		}

		// Testing row2
		IOCLR1 |=r2;
		IOSET1 =r0|r1|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
		 	row_val =2;
			break;
		}

		// Testing row3
		IOCLR1 |=r3;
		IOSET1 =r0|r1|r2;
		if((c0&&c1&&c2&&c3)==0)
		{
		 	row_val =3;
			break;
		}

		if(c0==0)
		col_val =0;
		else if(c1==0)
		col_val =1;
		else if(c2==0)
		col_val =2;
		else
		col_val =3;

		while((c0&&c1&&c2&&c3)==0);  // wait until keypad released (debounce)
	}
	return keypad[row_val][col_val];
}

int main()
{
	int res;
	lcd_init();
	lcd_string("4x4 keypad");
	while(1)
	{
	 	lcd_cmd(0xc0);
		res=keyscan();
		lcd_display_number(res);
		delay(500);
		lcd_cmd(0x01); 
	} 	
}
