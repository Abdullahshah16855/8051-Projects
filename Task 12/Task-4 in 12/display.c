#include <reg51.h>
#include <stdio.h>
#include "LCD.h"

#define LED P0

// Selecting Channel 
sbit A=P2^4;
sbit b=P2^3;
sbit C=P2^2;

void timerdelay();

void main(void)
{
		int x;
			A=1;	b=1; C=1;
		LED = 0xFF;  
		timerdelay();
	
				A=1;	b=1; C=0;
		LED = 0xFF;  
		timerdelay();
		
			A=1;	b=0; C=1;
		LED = 0xFF;  
		timerdelay();
		
		A=1;	b=0; C=0;
		LED = 0xFF;  
		timerdelay();
		
		A=0;	b=1; C=1;
		LED = 0xFF;  
		timerdelay();
		
			A=0;	b=1; C=0;
		LED = 0xFF;  
		timerdelay();
		
			A=0;	b=0; C=1;
		LED = 0xFF;  	
		timerdelay();
	
		A=0;	b=0; C=0;
		LED = 0xFF;  
		timerdelay();
}
 void timerdelay()
 {
	  TMOD=0x01;  //Timer 0 in mode 1 which is 16 Bits
    
	  TH0=0xDB;	//Generating 10 ms delay
    TL0=0xFF;
	 
    TR0=1;
    while (TF0==0);
		TR0=0;
	  TF0=0;
	}