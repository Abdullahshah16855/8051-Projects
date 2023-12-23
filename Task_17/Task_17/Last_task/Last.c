#include <reg51.h >

//display on lcd 

sbit rs = P2^6;
sbit wr=P2^5;
sbit en=P2^7;
sbit led = P2^0;
sbit DQ	=P3^7;
sbit buz_pin = P1^5;

unsigned int i=0,j=0;
unsigned char U,T,H,intpart,decpart;
	unsigned char value[3];


unsigned int index=0;

void display (char);
void command(char );
unsigned char temp;
void delay_us(unsigned int );
unsigned char temperature;
void string (char *point);
void read_temp_hercules(void);

void read_temp_hercules (void)
{

	ES = 1;  // enable the  seraial intrupts
	TMOD = 0x20;  // timer 1 in mode 2
	SCON = 0x50;
	
	TH1= -3;  //baud rate  9600
	TR1=1;   //start timer 1
	
      
	
	for (j=0; j<3 ; j++)
	     {
		 
        while(RI == 0);	
        value[j] = SBUF;  //recieved temprature from hercules
				RI=0;  
		  
	     }
			H=value[0]; //provide hundert value
			T=value[1]; //provide tenth value
			U=value[2]; //provide unit value
		   } 


void display (char temp)
{
	P0=temp;      
	rs=1;           // displaying a character or Data
	en=1;
  wr=0;
	delay_us(5);
	en=0;
}



void string (char *point)
{
	while(*point)
	{
		display(*point++);
	}
}

void delay_us(unsigned int z){
        unsigned int i;
        for(i=0;i<z;i++);
}

void delay_ms(unsigned int z1){
        unsigned int i,j;
        for(i=0;i<z1;i++)
        for(j=0;j<125;j++);
}

void delay_18B20(unsigned int ud){
    while(ud--);
}

void Init_18B20(void){
    DQ = 1;   
    delay_18B20(8);
    DQ = 0;   
    delay_18B20(65);
    DQ = 1;   
    delay_18B20(20);    
}

unsigned char Read_temp (void){
	
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

void Write_temp (unsigned char dat){
    unsigned char i=0;
    for (i=8; i>0; i--){
        DQ = 0;
        DQ = dat&0x01;
        delay_18B20(5);
        DQ = 1;
        dat>>=1;
    }
}

void ReadTemperature (void){	
    unsigned char a=0;
    unsigned char b=0;
	
    Init_18B20();
    Write_temp(0xCC);    // skip rom   
    Write_temp(0x44);    //This command initiates a single temperature conversion. 
    delay_18B20(10); 
    Init_18B20();
	
    Write_temp(0xCC);
    Write_temp(0xBE);    //This command allows the master to read the contents of  the scratchpad. T
    delay_18B20(10);
    a=Read_temp();        //Read temp low value
    b=Read_temp();	//Read temp high value
    
	 temperature= ((b*256+a)>>4); // combine the values.    
}

void lcd_init (void)
{
	command(0x38);      //Use two lines and 5x7 matrix
	command(0x0c);         // display on
	command(0x01);      //Clearing the screen
	command(0x80);       // Force cursor to beginning of the first line
	command(0xc0);       // 2nd line
}


void TempShow(void){
   
   
  command(0xc0);
	display(H);
	display(T);
	display(U);
	//custom Char (degree)
command(64);   // CGRAM address where value of the first character is store 0x40 (0xDF Abrar)
display(0x03);
display(0x03);
display(0x00);
display(0x00);
display(0x00);
display(0x00);
display(0x00);
command(0xc3);
display(0);    // for displaying 1st character
  string("C");
	
}

void command(char c)
{
	P0=c;
	rs=0;            // To send a command to the LCD
	en=1;
  wr=0;            // for write mode wr=0 and for read mode wr=1
	delay_us(5);
	en=0;
}

void main(){
	
	lcd_init();
	EA=1;
  TMOD = 0x01; 
	ET0=1;
	TH0 = 0xff; //reload timer value limit
	TL0 = 0x06;
	TR0=1;
	
	           read_temp_hercules ();
		         
	          
  while(1);

	}

void timer0_intrupt (void) interrupt 1   // called after  250u second 
{
   
	if ( T >= 0x33 | H >=0x31)
	{
    buz_pin = 0;
		delay_ms(1);
		buz_pin=1;
	}	
  buz_pin=1;	
	  
	   
		index+=1;
  	if (index == 4000)  //make it 1second
	 	{
			 command(0x80);
		   string("temperature");
       TempShow();
	    
         index=0;			
		}
	      
	TH0 = 0xff; //reload timer value limit
	TL0 = 0x06;
}