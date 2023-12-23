#include <reg51.h>

#include "read_write_time.h"


//lcd Part
//sfr LCD_DATA = 0x90;
sbit En = P2^0;
sbit RW = P2^1;
sbit RS = P2^2;

//sbit busy = P1^7;



//DS1302 Part
sbit rtcCE= P2^4;
sbit rtcSCLK = P2^5;
sbit rtcIO = P2^6;


//Keys part
sbit temp = P0^7;
sbit time = P0^6;
sbit exit = P0^5;
sbit configure = P3^7;

//some functional register
unsigned char bdata shiftRegister;

//some register bits
sbit lowBit = shiftRegister^0;
sbit highBit = shiftRegister^7;

//sbit mybit = P1^0;

void main(void){
	initializeAll();
	while(1){
		systemView();
	}	
}

void writeBurst(){
	unsigned char i;
	unsigned char z[] = {0x00,0x12,0x12,0x25,0x06,0x07,0x16,0X00};//yy,dd,mm,hh,mm,ss
	rtcCommand(0xBE);
	for(i=0; i<0x08; i++){
		rtcCommand(z[i]);
		customDelay(0xFF,0xF0);
	}
	rtcCE = 0;
}

void systemView(){
	lcdCmd(0x01);
	if(time == 0){
		lcdCmd(0x01); 
		lcdCmd(0x80);
		lcdMessage("Time ");
		while(exit == 1){
			displayTime();
			if(configure == 0){
				lcdCmd(0x01);
				lcdMessage("Burst Mode Write");
				oneSecondDelay();
				writeBurst();
				lcdCmd(0x01);
			}
		}
	}
	}
void initializeAll(){
	unsigned char z;
	initializeSerial();
	rtcCE = 0;
	rtcSCLK = 0;
	rtcIO = 1;	
	for(z=0; z<4; z++){
		lcdCmd(lcdCmds[z]);
	}
	oneSecondDelay();
}

void displayTime(){
	unsigned char h,m,s,y,mt,d,day;
	//rtcWrite(0x84,0x29);
	h = rtcRead(0x85);
	m = rtcRead(0x83);
	s = rtcRead(0x81);
	y = rtcRead(0x8D);
	mt = rtcRead(0x89);
	d = rtcRead(0x87);
	day = rtcRead(0x8B);
	asciiDisplay(h,'h','t');
	asciiDisplay(m,'m','t');
	asciiDisplay(s,'s','t');
	asciiDisplay(day,'b','t');
	asciiDisplay(y,'y','t');
	asciiDisplay(mt,'c','t');
	asciiDisplay(d,'d','t');
}

void rtcCommand(unsigned char c){
	unsigned char z;
	shiftRegister = c;
	rtcCE = 1;
	for(z=0; z<8; z++){
		rtcIO = lowBit;
		rtcSCLK = 1;
		customDelay(0xFF,0x00);
		rtcSCLK = 0;
		customDelay(0xFF,0x00);
		shiftRegister = shiftRegister >> 1;
	}
}
unsigned char rtcRead(unsigned char address){
	unsigned char z;
	rtcCommand(address);
	for(z = 0; z<8; z++){
		shiftRegister = shiftRegister >> 1;
		highBit = rtcIO;
		rtcSCLK = 1;
		customDelay(0xFF,0x00);
		rtcSCLK = 0;
		customDelay(0xFF,0x00);
	}
	rtcCE = 0;
	return shiftRegister;
}
void rtcWrite(unsigned char address, unsigned char byte){
	rtcCommand(address);
	rtcCommand(byte);
	rtcCE = 0;
}
void initializeSerial(){
	TMOD = 0x21;
	TH1 = 0xFD;
	SCON = 0x50;
	TR1 = 1;
}

void customDelay(unsigned char h, unsigned char l){
	TH0 = h;
	TL0 = l;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}
void oneSecondDelay(){
	unsigned char z;
	for(z = 0; z<0x0E; z++){
		customDelay(0x00,0x00);
	}
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
			lcdCmd(0xC9);
			if(a == 0x30);
			else{ lcdData(a); }
			if (a == 0x30 && b == 0x30);
			else{lcdData(b);}
			lcdData(c);
		}
		else if(flag == 'b'){
			lcdCmd(0xCB);
			lcdData('.');
			lcdData(a);
			lcdData(b);
			if(c == 0x30);
			else
				lcdData(c);
			lcdData('%');
		}
		else if(flag == 'c'){
			lcdCmd(0x85);
			if(a == 0x30);
			else{ lcdData(a); }
			if (a == 0x30 && b == 0x30);
			else{lcdData(b);}
			lcdData(c);
		}
		else if(flag == 'd'){
			lcdCmd(0x87);
			lcdData('.');
			lcdData(a);
			lcdData(b);
			if(c == 0x30);
			else
				lcdData(c);
			lcdData(0xDF);
			lcdData('C');
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
			lcdCmd(0x85);
			lcdData(a);
			lcdCmd(0x86);
			lcdData(b);
			lcdCmd(0x87);
			lcdData(':');
		}
		else if(flag == 'm'){
			lcdCmd(0x88);
			lcdData(a);
			lcdCmd(0x89);
			lcdData(b);
			lcdCmd(0x8A);
			lcdData(':');
		}
		else if(flag == 's'){
			lcdCmd(0x8B);
			lcdData(a);
			lcdCmd(0x8C);
			lcdData(b);
		}
		else if(flag == 'd'){
			lcdCmd(0xC5);
			lcdData(a);
			lcdCmd(0xC6);
			lcdData(b);
			lcdCmd(0xC7);
			lcdData('-');
		}
		else if(flag =='c'){
			lcdCmd(0xC8);
			lcdData(a);
			lcdCmd(0xC9);
			lcdData(b);
			lcdCmd(0xCA);
			lcdData('-');
		}
		else if(flag == 'y'){
			lcdCmd(0xCB);
			lcdMessage("20");
			lcdCmd(0xCD);
			lcdData(a);
			lcdCmd(0xCE);
			lcdData(b);
		}
		else if(flag == 'b'){
			lcdCmd(0xC0);
			if(byte == 0x01)
				lcdMessage("SUN,");
			else if(byte == 0x02)
				lcdMessage("MON,");
			else if(byte == 0x03)
				lcdMessage("TUE,");
			else if(byte == 0x04)
				lcdMessage("WED,");
			else if(byte == 0x05)
				lcdMessage("THU,");
			else if(byte == 0x06)
				lcdMessage("FRI,");
			else if(byte == 0x07)
				lcdMessage("SAT,");
		}
	}
}

void lcdMessage(unsigned char *c){
	while(*c !=0){
		lcdData(*c++);
	}
}

void lcdData(unsigned char dta){
	LCD_DATA = dta;
	RS = 1;
	RW = 0;
	En = 1;
	customDelay(0xF9,0xFF);//0x00,0x10
	En = 0;
}

void lcdCmd(unsigned char dta){
	LCD_DATA = dta;
	RS = 0;
	RW = 0;
	En = 1;
	customDelay(0xF9,0xFF);
	En = 0;
}