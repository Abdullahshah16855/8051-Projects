//Program to interface Serial EEPROM AT24C02 with 8051 microcontroller (AT89C51) 
#include<reg51.h>
#include<intrins.h>   //For using [nop()]
#define lcd_data_pin P0

sbit sda=P2^0;
sbit scl=P2^1;
sbit led=P0^3;
bit ack;
sbit led1=P0^1;
//fr output=0x80;//p0 port
sbit rs=P2^6;
sbit rw=P2^5;
sbit en=P2^7;
unsigned char reead,write,write2,i,j;
unsigned int temp;
void delay(unsigned int count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<1275;j++);
}
void lcd_command(unsigned char comm)
{
	lcd_data_pin=comm;
	en=1;
	rs=0;
	rw=0;
	delay(1);
	en=0;
}
void lcd_data(unsigned char disp)
{
	lcd_data_pin=disp;
	en=1;
	rs=1;
	rw=0;
	delay(1);
	en=0;
}
lcd_dataa(unsigned char *disp)
{
	int x;
	for(x=0;disp[x]!=0;x++)
	{
		lcd_data(disp[x]);
	}
}
void lcd_ini()
{
	lcd_command(0x38);		  // for using 8-bit 2 row LCD 
	delay(5);
	lcd_command(0x0F);        // for display on, cursor blinking
	delay(5);
	lcd_command(0x80);
	delay(5);
}
void aknowledge()	  //acknowledge condition
{
	scl=1;
	nop();
	nop();
	scl=0;
} 
void start()		//start condition
{
	sda=1;
	scl=1;
	nop();         //No operation
	nop();
	sda=0;
	scl=0;
}
void stop()			//stop condition
{
	sda=0;
	scl=1;
	nop();
	nop(); 
	sda=1;
	scl=0;
}
void send_byte(unsigned char value)	//send byte serially
{ 
	unsigned int i;
	unsigned char send;
	send=value;
	for(i=0;i<8;i++)
	{
		sda=send/128;			//extracting MSB
		send=send<<1;			//shiftng left
		scl=1;
		nop();
		nop();
		scl=0;
	}
   ack=sda;					//reading acknowledge
   sda=0;
}
unsigned char read_byte()			//reading from EEPROM serially
{
	unsigned int i;
	sda=1;
	reead=0;
	for(i=0;i<8;i++)
	{
		reead=reead<<1;
		scl=1;
		nop();
		nop();
		if(sda==1)
			reead++;
		scl=0;
	}
	sda=0;
	return reead;				//Returns 8 bits Data here
}		
void save()					//save in EEPROM
{
	start();
	send_byte(0xA0);						//device address
	aknowledge();
	send_byte(0x00);						//word address
	aknowledge();
	send_byte(5);							//send Data
	aknowledge();
	send_byte(65);
	aknowledge();
	stop();							   
	if(ack==0)
	{
		led1=1;
		delay(100);
		led1=0;
		delay(100);
		lcd_command(0x86);
		lcd_data('5');
		lcd_command(0x87);
		lcd_data('A');
	}
	else
	led1=1;
	aknowledge();
}
void Read()
{
	start();
	send_byte(0xA0);
	aknowledge();
	send_byte(0x00);
	aknowledge();
	start();
	send_byte(0xA1);					 //device address
	aknowledge();
	i=read_byte();
	aknowledge();
	j=read_byte();
	aknowledge();
	stop();
	if(i==5)
	{
		led=0;
		delay(100);
		led=1;
		delay(100);
		write=i+48;
		lcd_command(0xC6);
		lcd_data(write);	
	}
	else
	 led=1;
	if(j==65)
	{
		lcd_command(0xC7);
		lcd_data(j);
	}
	aknowledge();
}

void main()
{
	lcd_ini();
	lcd_dataa("Sent :");
	lcd_command(0xC0);
	lcd_dataa("Read :");
	temp=0;
	while(1)
	{
		save();
		Read();
	}
}