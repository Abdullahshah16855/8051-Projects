#include<reg51.h>
#define lcd P2

sbit rs=P3^2;
sbit e=P3^4;

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
	e=1;      // Enable from 1 to 0, or 0 to 1 to latch data
	delay(5);
	e=0;
}
void display (char c)
{
	lcd=c;
	rs=1;	// RS=1 , to write data on LCD
	e=1;	 // Enable from 1 to 0, or 0 to 1 to latch data
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
	cmd(0x01);     // Clear Screen
	cmd(0x80);    // Beginning of First Line
}
void main()
{
	init();
	
	Write("ABBAS AlI ");
	delay(250);
         cmd(0x01);   // Clear Screen
	cmd(0x80);    // Beginning of First Line
	
	Write("18JZELE0237");
	delay(250);
	cmd(0x01);
	cmd(0x80);
	Write("MBSD MIDTERM 21 ");
	delay(250);
	cmd(0x01);
	
   
display (0x41);   // Hexa Decimal Number of A alphabet
Write(": 65");
delay (65);
cmd(0x01);        // Clear Screen
	 
display (0x42);    // Hexa Decimal Number of B alphabet
Write(": 66");
delay (66);
cmd(0x01);  		// Clear Screen

display (0x42);    // Hexa Decimal Number of B alphabet
Write(": 66");
delay (200);
cmd(0x01);			// Clear Screen

display (0x41);   // Hexa Decimal Number of A alphabet
Write(": 65");
delay (65);
cmd(0x01);		// Clear Screen

display (0x53);    // Hexa Decimal Number of S alphabet
Write(": 83");
delay (83);
cmd(0x01);			// Clear Screen

display (0x41);   // Hexa Decimal Number of A alphabet
Write(": 65");
delay (65);
cmd(0x01);			// Clear Screen

display (0x4C);   // Hexa Decimal Number of L alphabet
Write(": 76");
delay (76);
cmd(0x01);			// Clear Screen

display (0x49);   // Hexa Decimal Number of I alphabet
Write(": 73");
delay (73);
cmd(0x01);			// Clear Screen
}