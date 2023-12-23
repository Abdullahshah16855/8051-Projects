#include<reg51.h>
#define lcd P0   // STC port 0 is connected to LCD 

sbit rs=P2^6;
sbit e=P2^7;
sbit rw=P2^5;

void delay (int);
void cmd (char);
void display (char);
void Write (char *);
void init (void);

void delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}

void cmd (char c)
{
	lcd=c;	  // LCD assign to P3
	rs=0;     // RS=0, Read Data or Initiaze Data
	rw=0;
	e=1;      // Enable from 1 to 0, or 0 to 1 to latch Data
	delay(5);
	e=0;
}
void display (char c)
{
	lcd=c;
	rs=1;	// RS=1 , to write Data on LCD
	rw=0;
	e=1;	 // Enable from 1 to 0, or 0 to 1 to latch Data
	delay(1);
	e=0;
}

void Write (char *p)
{
	while(*p)
	{
		display(*p++);
	}
}
void init (void)
{
	cmd(0x0c);		// Display ON and Cursor OFF
	cmd(0x38);    //  Use two Lines
	cmd(0x01);    // Clear Screen
	cmd(0x80);    // Beginning of First Line
}
void main()
{
	init();
	
	Write("ABBAS ALI ");
	delay(250);
	cmd(0x80);    // Beginning of First Line
	cmd(0xc0);    // Beginning of Second Line
	Write("FROM PESHAWAR");
	delay(800);
	cmd(0x01);
	
	Write("Super_Visor");
	delay(250);
	cmd(0xc0);    // Beginning of Second Line
	Write("Umer Sharif Sir");
	delay(800);
	cmd(0x01);
	
	display(1+0x30);   // Display digits 
	delay(800);
	cmd(0x01);
}