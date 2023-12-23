#ifndef LCD.h
#define LCD.h

#define lcd_data P0

void rtcWrite(unsigned char address, unsigned char byte);
void oneSecondDelay(void);
void delay (int);
void command (char);
void display (char);
void string (char *);
void init (void);
void initializeAll(void);
void initializeSerial(void);
void systemView(void);
 void displayTime(void);
unsigned char rtcRead(unsigned char address);
void asciiDisplay(unsigned char byte, unsigned char flag);
unsigned char h,m,s,y,mt,d,day;
unsigned char z;
void customDelay(unsigned char h, unsigned char l);
void write_time_using_hercules(void);
unsigned char bdata shiftRegister;
sbit lowBit=shiftRegister^0;
sbit highBit=shiftRegister^7;
sbit SCLK=P3^6;
sbit CE=P3^5;
sbit IO=P3^4; 
sbit time=P3^1;
sbit exit=P3^0;
unsigned char s1,s2,x1,x3,x2,h1,h2,m1,m2;



unsigned char i,j;


//some functional register
//unsigned char bdata shiftRegister;
//sbit lowBit = shiftRegister^0;
//sbit highBit = shiftRegister^7;
sbit rs=P2^6;
sbit en=P2^7;
sbit wr=P2^5;	 
void delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}
void command (char c)
{
	lcd_data=c;
	rs=0;            // To send a command to the LCD
	en=1;
   wr=0;       // for write mode wr=0 and for read mode wr=1
	delay(5);
	en=0;
}
void display (char c)
{
	lcd_data=c;      
	rs=1;           // displaying a character or Data
	en=1;
        wr=0;
	delay(5);
	en=0;
}


void string (char *p)
{
	while(*p)
	{
		display(*p++);
	}
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