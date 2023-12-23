#include<reg51.h>
#include "LCD.h"

void write_time_using_hercules(void)
{
	unsigned char arr[8];
	TMOD=0X20;
	SCON=0x50;
	TH1=-3;
	TR1=1;
	
	for(i=0; i<8; i++)
		{
			while (RI==0);
			arr[i]=SBUF;
			RI=0;
			
		}
			command(0x01);
		 command(0x80);
		
	        h1=arr[0];
          h2=arr[1];
          h1 = h1 & 0x0f;
          h1 =h1 << 4;		
					h2= h2 & 0x0f;
          x1 = h1|h2; 		
				rtcWrite(0x84,x1); 
		
		
		
					m1=arr[3];
          m2=arr[4];
          m1 = m1 & 0x0f;
          m1 =m1 << 4;		
					m2= m2 & 0x0f;
          x2 = m1 | m2;
		   rtcWrite(0x82,x2);
		
	      	s1=arr[6];
          s2=arr[7];
          s1 = s1 & 0x0F;
          s1 =s1 << 4;		
	        s2= s2 & 0x0F;
          x3 = s1 | s2;
		rtcWrite(0x80,x3);     // second
}
void main(void)
{
	
	initializeAll();
  
	write_time_using_hercules();
	while(1)
{
	  
		systemView();
}	
}

void displayTime(){

	//rtcWrite(0x84,0x10);
	//rtcWrite(0x82,0x10);
  h = rtcRead(0x85);
	m = rtcRead(0x83);
	s = rtcRead(0x81);
  y = rtcRead(0x8D);
	mt = rtcRead(0x89);
	d = rtcRead(0x87);
	day = rtcRead(0x8B);
	asciiDisplay(h,'h');
	asciiDisplay(m,'m');
	asciiDisplay(s,'s');
	asciiDisplay(day,'b');
	asciiDisplay(y,'y');
	asciiDisplay(mt,'c');
	asciiDisplay(d,'d');
	 //rtcWrite(0x80,0x02);
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
	//initializeSerial();
	init();
	CE = 0;
	SCLK = 0;
	IO=1;


	
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

void asciiDisplay(unsigned char byte, unsigned char flag){
	
		unsigned char a,b;
		a = byte & 0xF0;
		a = a >> 4;
		a = a + 0x30;
		b = byte & 0x0F;
		b = b + 0x30;
	  
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

void systemView()
{
	
command(0x01); 
command(0x80);
		 
		//rtcWrite(0x82,0x29);
		string("Time ");
		while(1)
			{
			displayTime();
		     }
}
	

	void rtcWrite(unsigned char address, unsigned char byte)
{
	rtcCommand(address);
	rtcCommand(byte);
	CE=0;
}


