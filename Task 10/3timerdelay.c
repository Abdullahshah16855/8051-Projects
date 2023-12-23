#include <reg51.h>
#include <stdio.h>

sbit D1=P2^0;
sbit D2=P2^1;
sbit D3=P2^2;

 unsigned int a=0,b=0;
	
void timer0(void) interrupt 1
{
	  TH0=0xDB;
    TL0=0xFF;
	
		D1=~D1; // Generate a 10 ms
  
   a+=1;
	 b+=1;
	
   if(a==10)  // Delay of 100 ms
   {
		 D2=~D2;
     a=0;
	 }
   
	 if(b==100) // 1 sec
   {
		 D3=~D3;
      b=0;
	 }
 }
void main(void)
 {
		IE=0x82;   // Timer interupt Is Enable.
    TMOD=0x01;  // Using Timer 0 in Mode 1 which is 16 bits
    
	  TH0=0xDB;   // Generate a 10 ms delay
    TL0=0xFF;
	 
    TR0=1;
    while(1);

 }