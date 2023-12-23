#include<reg51.h>
#define lcd P0

sbit rs=P2^6;
sbit e=P2^7;
sbit rw=P2^5;

void delay (int);
void cmd (char);
void display (char);
void Write (char *);
void init (void);
void custom(void);


unsigned char custom_char[]= {	0x00,0x04,0x0E,0x04,0x15,0x0E,0x04,0x00, 
								0x00,0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x00, 
								0x00,0x0A,0x15,0x11,0x11,0x0A,0x04,0x00,
								0x0E,0x11,0x11,0x1F,0x1B,0x1B,0x1B,0x1F,
								0x0E,0x11,0x10,0x1F,0x1B,0x1B,0x1B,0x1F,
								0x00,0x0E,0x15,0x1B,0x0E,0x0E,0x00,0x00,
							};

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
	rs=1;	// RS=1 , to write data on LCD
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

void custom (void)
{
	int k;
	cmd(0x40);
	for(k=0;k<48;k++)
	display(custom_char[k]);
	cmd(0x80);
}
void main()
{
	int i;
	
	init();
	custom();
	
	for (i=0; i<=15; i++)
	{
		display(i);
		delay(100);
	}
}
	