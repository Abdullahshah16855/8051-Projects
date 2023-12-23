#include <reg51.h>
#include <stdio.h>
#include <intrins.h>
sbit scl=P2^0;
sbit sda=P2^1;
sbit rw=P2^3;
sbit rs=P2^2;
sbit en=P2^4;
void start();
void delay();
void check();
void stop();
void lcd_display();
void lcd_init();
void lcddisp(unsigned char*);
void lcdcmd(unsigned char);
void write(unsigned char);
void lcddat(unsigned char);
void delay3();
unsigned char read();
void enter();
void ack();
void display();
void delay2();
void serial_init();
void ser_msg(unsigned char *);
void conversion(unsigned char);
unsigned char sec,min,hr,day,date,mon,yr,ch;
bit c=0;

void main()
{
  serial_init();
   start();
write(0xd0);
write(0x00);
write(0x40);   
write(0x28);
write(0x14);   
write(0x06);
write(0x02);   
write(0x03);
write(0x18);
stop();
while(1)
{
serial_init();
start();
write(0xd0);
write(0x00);
start();
write(0xd1);
read();
sec=ch;
sec=sec&0x7f;
stop();
   
start();
write(0xd0);
write(0x01);
start();
write(0xd1);
read();
min=ch;
min=min&0x7f;
stop();
   
start();   
write(0xd0);
write(0x02);
start();
write(0xd1);
read();
hr=ch;
hr=hr&0x3f;
stop();

start();   
write(0xd0);
write(0x03);
start();
write(0xd1);
read();
day=ch;
day=day&0x0f;
stop();

start();   
write(0xd0);
write(0x04);
start();
write(0xd1);
read();
date=ch;
date=date&0x03f;
stop();

start();   
write(0xd0);
write(0x05);
start();
write(0xd1);
read();
mon=ch;
mon=mon&0x0f;
stop();

start();   
write(0xd0);
write(0x06);
start();
write(0xd1);
read();
yr=ch;
yr=yr&0x0f;
stop();
display();
lcd_display();

}
}
void display()
{
 conversion(hr);
 conversion(min);
 conversion(sec);
  enter();
  conversion(date);
   conversion(mon);
   conversion(yr);
   enter(); 
}

void conversion(unsigned char res)
{
unsigned char v4,v5;
v4=res&0x0f;
v5=res&0xf0;
v5=v5>>4;
v4=v4|0x30;
v5=v5|0x30;
SBUF=v5;
while(TI==0);
   TI=0;
SBUF=v4;
while(TI==0);
   TI=0;
SBUF=':';
while(TI==0);
   TI=0;
}

void lcd_display()
{
 unsigned char v9,v10;
 lcd_init();
 lcddisp("TIME:");
 lcdcmd(0xc0);
 lcddisp("DATE:");
 v9=hr&0x0f;
 v10=(hr&0xf0)>>4;
 lcdcmd(0x86);
 lcddat(v10|0x30);
 lcddat(v9|0x30);
 lcddat(':');
 v9=min&0x0f;
  v10=(min&0xf0)>>4;
 lcddat(v10|0x30);
 lcddat(v9|0x30);  
 v9=sec&0x0f;
  v10=(sec&0xf0)>>4;
 lcddat(v10|0x30);
 lcddat(v9|0x30);
lcdcmd(0xc6);

v9=date&0x0f;
 v10=(hr&0xf0)>>4;
 lcddat(v10|0x30);
 lcddat(v9|0x30);
 lcddat(':');
 v9=mon&0x0f;
  v10=(mon&0xf0)>>4;
 lcddat(v10|0x30);
 lcddat(v9|0x30);  
 lcddat(':');
 v9=yr&0x0f;
  v10=(yr&0xf0)>>4;
 lcddat(v10|0x30);
 lcddat(v9|0x30);
 delay3();
}

void delay3()
{
   unsigned int v11;
for(v11=0;v11<32000;v11++);
}

void lcd_init()
{
   lcdcmd(0x38);
   lcdcmd(0x01);
   lcdcmd(0x10);
   lcdcmd(0x0c);
   lcdcmd(0x80);
}

void enter()
{
   SBUF=0x0D;
   while(TI==0);
   TI=0;   
}

void write(unsigned char val)
{
 unsigned char v2=0x80,v3,v5;
 v5=val;
 for(v3=0;v3<8;v3++)
{
 sda=v5&v2;
 scl=1;
 delay();
 scl=0;
 v5=v5<<1;  
 }
c=sda;
scl=1;
delay();
scl=0;
if(c==1)
{
  stop();
  while(1);
 } 
 }

 void stop()
 {
 scl=1;
sda=0;
delay();
sda=1;
scl=0;
delay();
 }

void delay()
{
  nop();
  nop(); 
}   

unsigned char read()
{
 unsigned char v16;
 bit m=0;
 for(v16=0;v16<=7;v16++)
 {
  scl=1;
  delay();
  m=sda;
  scl=0;
  if(m==1)
  {
   ch|=0x01;
  }
if(v16<=6)
 ch=ch<<1;
delay();
}
return ch;
}

void start()
{
scl=1;
sda=1;
delay();
sda=0;
delay();
scl=0;   
}

void serial_init()
{
 SCON=0x50;
 TMOD=0x20;
 TH1=-3;
 TR1=1;
}

void lcddisp(unsigned char *m)
{
 unsigned char p;
 for(p=0;p[m]!='\0';p++)
  lcddat(m[p]);
 }
 
void lcddat(unsigned char val)
{
 P1=val;
 rs=1;
   rw=0;
 en=1;
 delay2();
 en=0;  
 } 

void lcdcmd(unsigned char val)
{
   P1=val;
   rs=0;
   rw=0;
   en=1;
   delay2();
   en=0;
 }
 
 void dealy2()
 {
    unsigned int v1;
    for(v1=0;v1<2000;v1++);
  }