#include <reg51.h>
#include <stdio.h>

sbit D1=P2^0;
sbit K1=P3^1;

int k1_btn_state=0;
int k1_press_cntr=0;
int k1_release_cntr=0;

	
void timer0(void) interrupt 1
{
    TH0=0xDB;
    TL0=0xFF;
    if (k1_btn_state==0)
{
k1_press_cntr+=1;
}
else
{
k1_press_cntr=0;
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