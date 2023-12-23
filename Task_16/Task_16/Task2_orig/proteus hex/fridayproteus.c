#include<reg51.h>



#define lcd_data P1

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
void asciiDisplay(unsigned char byte, unsigned char flag, unsigned char entity);
	unsigned char h,m,s,y,mt,d,day;
	unsigned char z;
	void customDelay(unsigned char h, unsigned char l);
	void rtcCommand1(unsigned char c);
	
sbit SCLK=P2^5;
sbit CE=P2^4;
sbit IO=P2^6; 
sbit time=P0^7;
sbit exit=P0^6;

//some functional register
unsigned char bdata shiftRegister;
sbit lowBit = shiftRegister^0;
sbit highBit = shiftRegister^7;
sbit rs=P2^2;
sbit en=P2^0;
sbit wr=P2^1;	                          
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


void main(void)
{
	
	initializeAll();
	while(1)
{
		systemView();
}	
}

void displayTime(){

	//rtcWrite(0x84,0x10);
	//rtcWrite(0x82,0x10);
	//rtcWrite(0x80,0x10);
h = rtcRead(0x85);
	m = rtcRead(0x83);
	s = rtcRead(0x81);
  //y = rtcRead(0x8D);
	//mt = rtcRead(0x89);
	//d = rtcRead(0x87);
	//day = rtcRead(0x8B);
	asciiDisplay(h,'h','t');
	asciiDisplay(m,'m','t');
	asciiDisplay(s,'s','t');
	/*asciiDisplay(day,'b','t');
	asciiDisplay(y,'y','t');
	asciiDisplay(mt,'c','t');
	asciiDisplay(d,'d','t');*/
}



void rtcCommand(unsigned char c){
	unsigned char z;
	shiftRegister = c;
	CE = 1;
	for(z=0; z<8; z++){
		IO = lowBit;
		SCLK = 1;
		customDelay(0xFF,0x00);
		SCLK = 0;
		customDelay(0xFF,0x00);
		shiftRegister = shiftRegister >> 1;
	}
}
unsigned char rtcRead(unsigned char address)
	{
	unsigned char z;
	rtcCommand(address);
	for(z = 0; z<8; z++)
		{
		shiftRegister = shiftRegister >> 1;
		highBit = IO;
		SCLK = 1;
		customDelay(0xFF,0x00);
		SCLK = 0;
		customDelay(0xFF,0x00);
	}
	CE = 0;
	return shiftRegister;
}
void initializeAll(){
	initializeSerial();
	CE = 0;
	SCLK = 0;
	init();
	IO = 1;	
	oneSecondDelay();
}
void initializeSerial(){
	TMOD = 0x21;
	TH1 = 0xFD;
	SCON = 0x50;
	TR1 = 1;
}
void oneSecondDelay(){
	unsigned char z;
	for(z = 0; z<0x0E; z++){
		customDelay(0x00,0x00);
	}
}
void customDelay(unsigned char h, unsigned char l){
	TH0 = h;
	TL0 = l;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}
void asciiDisplay(unsigned char byte, unsigned char flag, unsigned char entity){
	if(entity == 'h'){
		unsigned char a,b,c;
		a = byte / 100;
		byte = byte %100;
		b = byte / 10;
		byte = byte % 10;
		c =  byte;
		a = a | 0x30;
		b = b | 0x30;
		c = c | 0x30;
		if(flag == 'a'){
			command(0xC9);
			if(a == 0x30);
			else{ display(a); }
			if (a == 0x30 && b == 0x30);
			else{display(b);}
			display(c);
		}
		else if(flag == 'b'){
			command(0xCB);
			display('.');
			display(a);
			display(b);
			if(c == 0x30);
			else
				display(c);
			display('%');
		}
		else if(flag == 'c'){
			command(0x85);
			if(a == 0x30);
			else{ display(a); }
			if (a == 0x30 && b == 0x30);
			else{display(b);}
			display(c);
		}
		else if(flag == 'd'){
			command(0x87);
			display('.');
			display(a);
			display(b);
			if(c == 0x30);
			else
				display(c);
			display(0xDF);
			display('C');
		}
	}
	else{
		unsigned char a,b;
		a = byte & 0xF0;
		a = a >> 4;
		a = a | 0x30;
		b = byte & 0x0F;
		b = b | 0x30;
		if(flag == 'h'){
			command(0x85);
			display(a);
			command(0x86);
			display(b);
			command(0x87);
			display(':');
		}
		else if(flag == 'm'){
			command(0x88);
			display(a);
			command(0x89);
			display(b);
			command(0x8A);
			display(':');
		}
		else if(flag == 's'){
			command(0x8B);
			display(a);
			command(0x8C);
			display(b);
		}
		else if(flag == 'd'){
			command(0xC5);
			display(a);
			command(0xC6);
			display(b);
			command(0xC7);
			display('-');
		}
		else if(flag =='c'){
			command(0xC8);
			display(a);
			command(0xC9);
			display(b);
			command(0xCA);
			display('-');
		}
		else if(flag == 'y'){
			command(0xCB);
			string("20");
			command(0xCD);
			display(a);
			command(0xCE);
			display(b);
		}
		else if(flag == 'b'){
			command(0xC0);
			if(byte == 0x01)
				string("SUN,");
			else if(byte == 0x02)
				string("MON,");
			else if(byte == 0x03)
				string("TUE,");
			else if(byte == 0x04)
				string("WED,");
			else if(byte == 0x05)
				string("THU,");
			else if(byte == 0x06)
				string("FRI,");
			else if(byte == 0x07)
				string("SAT,");
		}
	}
}

void systemView()
{
	command(0x01);
	if(time == 0){
command(0x01); 
command(0x80);
		string("Time ");
		while(exit == 1){
			displayTime();
		/*	if(configure == 0){
		command(0x01);
				string("Burst Mode Write");
				oneSecondDelay();
				writeBurst();
		command(0x01);*/
			}
		}
	}

	void rtcWrite(unsigned char address, unsigned char byte)
{
	rtcCommand1(address);
	rtcCommand1(byte);
	CE=0;
}
void rtcCommand1(unsigned char c){
	unsigned char z;
	shiftRegister = c;
	CE = 1;
	for(z=0; z<8; z++){
		IO = lowBit;
		SCLK = 1;
		customDelay(0xFF,0x00);
		SCLK = 0;
		customDelay(0xFF,0x00);
		shiftRegister = shiftRegister >> 1;
	}
}