
#include <reg51.h>
#include <stdio.h>

#define LED P2

void delay(int t);

void main(void)
 { 
    
   // Write your code here
   LED = 0;   // Declare as Output
 
    while (1)
    {
       LED = 0xAA;  // 10101010 = pattern of LED
       delay(500);	// Delay of 501 ms
			
       LED = 0x55;	// 01010101 = pattern of LED
       delay(500);	// Delay of 501 ms
      }
    }
 void delay(int t)   
 {
    int i,j;
    for (i=0; i<=t; i++)
    for (j=0;j<=122; j++);  
 }
 