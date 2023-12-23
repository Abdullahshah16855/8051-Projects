#include<reg52.h> 
#define PORT P0

sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;
sbit SDA=P2^0;
sbit SCL=P2^1;

unsigned int  i;
void write( unsigned char Data,unsigned char Address);
unsigned char Read(unsigned char Address);
void Start();
void send_byte(unsigned char Data);
void Delay_ms(long int k);
void Delay_us(long int k);
void string(const char *p);
unsigned char read_byte();
void I2CNak();
void command(char a);
void stop();
void display(char b);
void initializeLCD();

void write( unsigned char Data,unsigned char Address)
{
    Start(); 
   	send_byte(0xA0);	
   	send_byte(Address); 
   	send_byte(Data);    
    stop();           	 
	  Delay_ms(5);        
}

unsigned char Read(unsigned char Address)
{
    unsigned char Data;

    Start();            
   	send_byte(0xA0);	  
   	send_byte(Address); 
    Start();		   
    send_byte(0xA1);           
	  Data = read_byte(); 
	  I2CNak();
    stop();		        
	  Delay_us(10);
    return Data;          
}

void main (void)
{
	char Name[]="123456789";
	
	initializeLCD();
	command(0x80);
	string("EEPROM COUNTER");
	
	for(i =0; i<9; i++)
	write(Name[i],i);
	
  command(0xc0);	
	for(i =0; i<9; i++)
	{				             	
	display(Read(i));
	Delay_ms(500);
	}
	while(1);
}

void command(char a)
{
	P0 = a;
  RS=0;RW=0;EN=1;
	Delay_ms(8);
	EN=0;
}

void display(char b)
{

	P0 = b;
	RS=1;RW=0;EN=1;
	Delay_ms(8);
	EN=0;
}
	
void string(const char *p)
{
while(*p!='\0')
{
display(*p);
p++;
}
}	

void initializeLCD()
{
	command(0x38);
	command(0x01);
	command(0x80);
	command(0x06);
	command(0x0C);	
}

void Start()
{
	SCL = 0;
	SDA = 1;
	Delay_us(1);
	SCL = 1;
	Delay_us(1);
	SDA = 0;
	Delay_us(1);
	SCL = 0;
}

void stop()
{
	SCL = 0;
	Delay_us(1);
	SDA = 0;
	Delay_us(1);
	SCL = 1;
	Delay_us(1);
	SDA = 1;
}
 void acknowlegde()
{
	
	SDA = 0;
	Delay_us(1);
	SCL = 1;
	Delay_us(1);
	SCL = 0;
	SDA = 1;
}

void I2CNak()
{
	SDA = 1;
	Delay_us(1);
	SCL = 1;
	Delay_us(1);
	SCL = 0;
	SDA = 1;
}

void send_byte(unsigned char Data)
{
	 unsigned char i;
	 for (i = 0; i < 8; i++) {
		
		SDA=Data & 0x80;
		SCL = 1;
	 	SCL = 0;
		Data<<=1;
	 }
	 acknowlegde();
}

unsigned char read_byte()
{
	unsigned char i, Data=0;
	for (i = 0; i < 8; i++) {
		Delay_us(1);
		SCL = 1;
		Data|=SDA;
		if(i<7)
		Data<<=1;
		SCL = 0;
	}
	return Data;
}

void Delay_ms(long int k)
{
		int i;
	TMOD=0X02;
	TH0=0x00;
	while(k!=0)
	{
		for(i=0;i<4;i++){
		TR0=1;
		while(!TF0);
		TF0=0;}
		k--;
	}
}  

void Delay_us(long int k)
{

	TMOD=0X02;
	TH0=256-k;
	TR0=1;
	while(!TF0);
	TF0=0;
}