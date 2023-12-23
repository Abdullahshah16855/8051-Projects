/* Main.c file generated by New Project wizard
 *
 * Created:   Tue Sep 21 2021
 * Processor: AT89C51
 * Compiler:  Keil for 8051
 */

#include <reg51.h>
#include <stdio.h>

sbit LED = P2^0;

void delay (int t);

void INTR1 (void) interrupt 2       // Using External Interrupt 1 is IE.2 thats why Interrupt 2
{ 
	LED = ~LED;   // Toggle its state
	delay(500);		
}

void main(void)
 { 
   // Write your Code here
	 IE = 0x84;		// Using only external interruptt 1 for INT1 i.e 1000 0100 = 0x84
 }
 
 void delay(int t)
 {
    int i,j;
    for (i=0; i<=t; i++)
    for (j=0;j<=122; j++);  
 }