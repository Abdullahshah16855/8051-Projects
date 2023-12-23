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

int length;
int flag;
int counter=0;
int j; 
volatile char RxData[16];
unsigned char temp;
int a=0;

void Serial (void) interrupt 4
 {
	if (RI==1)
	{
			temp=SBUF;
			RxData[counter] = temp;
			length = counter;
			if (temp == 0x0D)  // 0x0D means <CR> in Hercules to terminate , it dont know '\n\r'
			flag=1;
			a=1;
			RI=0;
	}
			counter+=1;
}
 
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

 
void main()
{
	IE = 0x90;
	init();
	TMOD = 0x20;
	TH1 = 0xFD;
	SCON = 0x50;
	TR1 = 1; 
	while(1)
	{
		if (flag==1)
		{
			for(j=0; j<length; j++)
			{
				display(RxData[j]);
				flag=0;
				counter=0;
			}
			if (a==1)
		{
			cmd(0xc0);
		}
		}
		
	}
}