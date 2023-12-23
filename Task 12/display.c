#include <reg51.h>
#include <stdio.h>

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
		for (x=0; x<20; x++)   // Total of 500 ms delay
	{
		timerdelay();  //25 ms
	}

		A=1;	b=1; C=0;
		LED = 0xFF;  
		for (x=0; x<20; x++)    // Total of 500 ms delay
	{
		timerdelay();
	}
		
		A=1;	b=0; C=1;
		LED = 0xFF;  
		for (x=0; x<20; x++)    // Total of 500 ms delay
	{
		timerdelay();
	}
		
		A=1;	b=0; C=0;
		LED = 0xFF;  
		for (x=0; x<20; x++)
	{
		timerdelay();
	}
		
		A=0;	b=1; C=1;
		LED = 0xFF;  
		for (x=0; x<20; x++)
	{
		timerdelay();
	}
		
		A=0;	b=1; C=0;
		LED = 0xFF;  
		for (x=0; x<20; x++)
	{
		timerdelay();
	}
		
		A=0;	b=0; C=1;
		LED = 0xFF;  
		for (x=0; x<20; x++)
	{
		timerdelay();
	}
		A=0;	b=0; C=0;
		LED = 0xFF;  
		for (x=0; x<20; x++)
	{
		timerdelay();
	}
}
 void timerdelay()
 {
	  TMOD=0x01;  //Using timer 0 in 16 Bit mode 1
    
	  TH0=0xA5;	//Generating 25 ms delay
    TL0=0xFE;
	 
    TR0=1;
    while (TF0==0);
		TR0=0;
	  TF0=0;
	}