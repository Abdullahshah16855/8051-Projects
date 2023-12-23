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
		A=0;	b=0; C=0;
		LED = 0x06;   // Display 1
		timerdelay();
	
		A=0;	b=0; C=1;
		LED = 0x5B;  // Display 2
		timerdelay();
		
		A=0;	b=1; C=0;
		LED = 0x4F;  // Display 3
		timerdelay();
		
		A=0;	b=1; C=1;
		LED = 0x66;  // Display 4
		timerdelay();
		
		A=1;	b=0; C=0;
		LED = 0x6D;  // Display 5
		timerdelay();
		
		A=1;	b=0; C=1;
		LED = 0x7D;  // Display 6
		timerdelay();
		
		A=1;	b=1; C=0;
		LED = 0x07;  	// Display 7
		timerdelay();
	
		A=1;	b=1; C=1;
		LED = 0x7F;  // Display 8
		timerdelay();
}
 void timerdelay()
 {
	  TMOD=0x01;
    
	  TH0=0x00;	//Generating 71 ms delay
    TL0=0x00;
	 
    TR0=1;
    while (TF0==0);
		TR0=0;
	  TF0=0;
	}