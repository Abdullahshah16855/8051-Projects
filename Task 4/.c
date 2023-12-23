
#include <reg51.h>
#include <stdio.h>

sbit LED = P2^0;

void delay(int t);

void main(void)
 { 
    
   // Write your code here
   LED = 0;   // Declare as Output
   
    while (1)
    {
       LED = 1;
       delay(500);
       LED = 0;
       delay(500);
      }
    }
 void delay(int t)
 {
    int i,j;
    for (i=0; i<=t; i++)
    for (j=0;j<=122; j++);  
 }
 