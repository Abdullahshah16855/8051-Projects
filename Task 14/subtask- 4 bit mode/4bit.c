#include<reg51.h>
#define lcd P2

sbit rs=P2^0;
sbit e=P2^2;
sbit rw=P2^1;

void delay (int);
void lcdcmd (char);
void lcddata (char);
void lcd_str (char *);
void lcd_init (void);
void lcdcmd1(char c);
void lcddata1(char c);

void delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}
void lcdcmd(char c)
{
	unsigned char x;
	x= c& 0xf0;
	lcdcmd1(x);
	
	x= (c<<4)&0xf0;
	lcdcmd1(x);
}

void lcdcmd1 (char c)
{
	lcd=c;	  // LCD assign to P3
	rs=0;     // RS=0, Read Data or Initiaze Data
	rw=0;
	e=1;      // Enable from 1 to 0, or 0 to 1 to latch ata
	delay(5);
	e=0;
}
void lcddata(char c)
{
	unsigned char x;
	x= c& 0xf0;
	lcddata1(x);
	
	x= (c<<4)&0xf0;
	lcddata1(x);
}

void lcddata1 (char c)
{
	lcd=c;
	rs=1;	// RS=1 , to write Data on LCD
	rw=0;
	e=1;	 // Enable from 1 to 0, or 0 to 1 to latch Data
	delay(1);
	e=0;
}

void lcd_str (char *p)
{
	while(*p)
	{
		lcddata(*p++);
	}
}

void lcd_init (void)
{
	lcdcmd(0x28);		// 4bit Mode
	lcdcmd(0x0c);		// Display ON and Cursor OFF
	//lcdcmd(0x38);    //  Use two Lines
	lcdcmd(0x01);    // Clear Screen
//	lcdcmd(0x80);    // Beginning of First Line
	lcdcmd(0x83);    // 
	lcdcmd(0x06);
}
void main()
{
	lcd_init();
	
	lcd_str("ABBAS ALI ");
	delay(250);
	lcdcmd(0x80);    // Beginning of First Line
	lcdcmd(0xc0);    // Beginning of Second Line
	lcd_str("FROM PESHAWAR");
	delay(800);
	lcdcmd(0x01);
	
	lcd_str("CHIP SOUL");
	delay(250);
	lcdcmd(0xc0);    // Beginning of Second Line
	lcd_str("TECHNOLOGY");
	delay(800);
	lcdcmd(0x01);
	
	// OR by word by word using lcddata command
	lcddata('A');		lcddata('B'); 	lcddata('B'); 	lcddata('A'); 	lcddata('S');
	
}