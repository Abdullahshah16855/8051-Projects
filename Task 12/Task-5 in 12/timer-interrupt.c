#include <reg51.h>
#include <stdio.h>
#include "LCD.h"

#define LED P0

// Selecting Channel 
sbit A=P2^4;
sbit b=P2^3;
sbit C=P2^2;

int x;

void timer0 (void) interrupt 1   // Timer Interrupt 0 IE.1
{
		TH0=0xB7;    // 20 ms delay
		TL0=0xFD;
	
		x+=1;
	
		if(x==1)
		{
		A=0;	b=0; C=0;
		LED = 0xFF;  
		}
	
		if(x==2)
		{
		A=0;	b=0; C=1;
		LED = 0xFF;  
		}
		
			if(x==3)
		{
		A=0;	b=1; C=0;
		LED = 0xFF;  
		}
		
			if(x==4)
		{
		A=0;	b=1; C=1;
		LED = 0xFF;  
		}
		
			if(x==5)
		{
		A=1;	b=0; C=0;
		LED = 0xFF;  
		}
		
			if(x==6)
		{
		A=1;	b=0; C=1;
		LED = 0xFF;  
		}
		
		if(x==7)
		{
			A=1;	b=1; C=0;
		LED = 0xFF;  	
		}
	
		if(x==8)
		{
		A=1;	b=1; C=1;
		LED = 0xFF;  
		x=0;
		}
}
void main(void)
{
		IE =0x82;   // Using just Timer Interrupt 0
		TMOD=0x01;  // Using Timer 0
    
	  TH0=0xB7;	//Generating 20 ms delay
    TL0=0xFD;
	 
    TR0=1;
		while(1);
}
 