#include < reg51.h >
#define lcd_data P3

sbit rs = P2^0;
sbit wr=P2^1;
sbit en=P2^2;
sbit DQ	=P0^0;
sbit Beep=P1^7;
sbit LED=P1^5;

void command (char c);
unsigned char temp;
void delay_us(unsigned int t);
unsigned char temp; 

void display (char c)
{
	lcd_data=c;      
	rs=1;           // displaying a character or Data
	en=1;
  wr=0;
	delay_us(5);
	en=0;
}


void string (char *p)
{
	while(*p)
	{
		display(*p++);
	}
}
 void delay_us(unsigned int t){
        unsigned int i;
        for(i=0;i<t;i++);
}
void delay_ms(unsigned int t){
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);
}
void delay_18B20(unsigned int ti){
    while(ti--);
}
void Init_18B20(void){
    DQ = 1;   
    delay_18B20(8);
    DQ = 0;   
    delay_18B20(65);
    DQ = 1;   
    delay_18B20(20);    
}
unsigned char ReadOneChar(void){
    unsigned char i=0;
    unsigned char dat = 0;
    for (i=8;i>0;i--){
          DQ = 0;
          dat>>=1;
          DQ = 1;
          if(DQ)
          dat |= 0x80;
          delay_18B20(4);
    }
    return(dat);
}
void WriteOneChar(unsigned char dat){
    unsigned char i=0;
    for (i=8; i>0; i--){
        DQ = 0;
        DQ = dat&0x01;
        delay_18B20(5);
        DQ = 1;
        dat>>=1;
    }
}
void ReadTemperature(void){	
    unsigned char a=0;
    unsigned char b=0;
    Init_18B20();
    WriteOneChar(0xCC);    // skip rom   
    WriteOneChar(0x44);    //This command initiates a single temperature conversion. 
    delay_18B20(10); 
    Init_18B20();
    WriteOneChar(0xCC);
    WriteOneChar(0xBE);    //This command allows the master to read the contents of  the scratchpad. T
    delay_18B20(10);
    a=ReadOneChar();        //Read temp low value
    b=ReadOneChar();          //Read temp high value
    temp=((b*256+a)>>4);    
}//End code DS18B20


void init (void)
{
	command(0x38);      //Use two lines and 5x7 matrix
	command(0x0c);         // display on
	command(0x01);      //Clearing the screen
	command(0x80);       // Force cursor to beginning of the first line
	command(0xc0);       // 2nd line
}


void TempShow(unsigned char z){ 
	unsigned char U,T,H;
	command(0xc0);
    /*display((z/100)+48);//unit
     display((z%100/10)+48);//tenth
    display((z%10)+48);//hundred 
     string("'C");*/
	
	H=(z/100)+0x30;//hundred
  U=(z%100/10)+0x30;//unit
  T=(z%10)+0x30;//tenth
	display(H);
	display(U);
	display(T);
  string("'C");
	if(U>=0x32 & T>=0x36)
	{LED=1;
	Beep=0;}
}
void command (char c)
{
	lcd_data=c;
	rs=0;            // To send a command to the LCD
	en=1;
   wr=0;       // for write mode wr=0 and for read mode wr=1
	delay_us(5);
	en=0;
}
void main(){
	LED=0;
	init();
	while(1){
		command(0x80);
		string("temperature");
		  ReadTemperature();	
		  TempShow(temp); 
		  delay_ms(500);
	}
}//THE END






