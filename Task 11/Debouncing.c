#include <reg51.h>
#include <stdio.h>

sbit D1=P2^0;
sbit K1=P3^1;

int k1_btn_state=0;
int k1_press_cntr=0;
int k1_release_cntr=0;

void timer0(void) interrupt 1   //Using IE.1 timer Interrupt 0
{
 	  TH0=0xDB;			// Generate 10 ms delay 
    TL0=0xFF;
	// Pressing the button
	if (k1_btn_state==0)
	{
		 if (K1==0)
	{	
		k1_press_cntr++;
		if (k1_press_cntr==10)
	{
		D1 = ~D1;   //LED Toggle
		k1_btn_state=1;
	}
	}
		else
			k1_press_cntr=0;
	}
	// Releasing Coding
	if (k1_btn_state==1)
	{
		if (K1==1)
	{
		k1_release_cntr+=1;}
		if (k1_release_cntr==10)
	{
		k1_btn_state=0;
	}
	}
	else
	{
		k1_release_cntr=0;
	}
}

void main(void)
 {
		IE=0x82;
    TMOD=0x01;
    
	  TH0=0xDB;
    TL0=0xFF;
	 
    TR0=1;
    while(1);

 }