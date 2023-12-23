#ifndef LCD.h
#define LCD.h

#define lcd_data P0

sbit rs = P2^6;
sbit wr=P2^5;
sbit en=P2^7;
sbit DQ	=P3^7;
sbit LED1=P2^0;
sbit LED2=P2^1;
sbit LED3=P2^2;
sbit Beep=P1^5;
void main();
void command (char c);
unsigned char temp;
void delay_us(unsigned int t);
unsigned char Tmp; 
unsigned char U,T,H,a=0;
void TimmerDelay(void);

void display (char c)
{
	lcd_data=c;      
	rs=1;           // displaying a character or Data
	en=1;
  wr=0;
	delay_us(5);
	en=0;
}
void command (char c)
{
	lcd_data=c;
	rs=0;            // To send a command to the LCD
	en=1;
   wr=0;       // for write mode wr=0 and for read mode wr=1
	delay_us(5);
	en=0;
}

void string (char *p)
{
	while(*p)
	{
		display(*p++);
	}
}
void TimmerDelay()
{
unsigned char i;
	for(i=0;i<144;i++);
}
void init (void)
{
	command(0x38);      //Use two lines and 5x7 matrix
	command(0x0c);         // display on
	command(0x01);      //Clearing the screen
	command(0x80);       // Force cursor to beginning of the first line
	command(0xc0);       // 2nd line
}
#endif