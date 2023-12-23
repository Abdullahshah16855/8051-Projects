#include< reg51.h >

sbit sda=P2^0;
sbit scl=P2^1;

unsigned char read_catch,z;
unsigned int index=0,i=0,value,newvalue=0;

unsigned int select[]  =  {0x1C,0x18,0x14,0x10,0x0C,0x08,0x04,0x00};
unsigned int message[] =  {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

void delay(unsigned int count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<114;j++);
}


void aknowledge()	  //acknowledge condition
{
	sda=0;
	delay(1);
	scl=1;
	delay(1);
	scl=0;
	sda=1;
} 
void start_opration()		//start_opration condition
{
	sda=1;
	scl=0;
	delay(1);
  scl=1;
	delay(1);
	sda=0;
	delay(1);
	scl=0;
	
}
void stop_opration()			//stop_opration condition
{ 
	scl=0;
	delay(1);
  sda=0;
	delay(1);
	scl=1;
	delay(1);
	sda=1;

	
}
void write_lcd_eeprom(unsigned char value)	//send_catch byte serially
{ 
	unsigned int i=0;
	 
	  for(i=0;i<8;i++)
	{
		sda=value & 0x80;			//extracting MSB
		
	  scl=1;
		scl=0;
		value<<=1;			     //shiftng left
	}
	aknowledge();
  
}
unsigned char read_eeprom()			//reading from EEPROM serially
{
	unsigned int i=0;
	sda=1;
	read_catch=0;
	for(i=0;i<8;i++)
	{  delay(1);
		scl=1;
		read_catch |= sda;
		if(i<7)
			read_catch <<=1;
		scl=0;
	}
	
	return read_catch;				//Returns 8 bit data here
}

void save_data(unsigned char Data , unsigned char address , unsigned char page_addr)				
{
	start_opration();
	write_lcd_eeprom(0xA0 | (page_addr>>1));						//page number  
	write_lcd_eeprom(address);						        //word address
	write_lcd_eeprom(Data);							  //send data for storing in eeprom
	stop_opration();
  delay(1);
	
}

char Read_data(unsigned char address , unsigned char page_addr)
{
	unsigned char DATA;
	start_opration();
	write_lcd_eeprom(0xA0 |(page_addr<<1)); // devise adress
	write_lcd_eeprom(address); //word adress
	start_opration();
	write_lcd_eeprom(0xA1 |(page_addr<<1));	 //send_catch controle byte for reading
	DATA=read_eeprom();
	stop_opration();
  delay(1);
	
	return DATA;
	
}

void main()
{
	
  IE = 0x82; // enable global and timer 0 intrupts
	TMOD = 0x01;  //enable mode1 of the timer 0 intrupts 
	TH0 = 0x4B;
	TL0 = 0xFD;
	TR0=1;
	while(1);
	
}

void timer0_intrupt (void) interrupt 1   // called after 50 ms 
{
      
	index+=1; 
	
	if(index==20) // make it 1 second 
	{    
		  
	     save_data (newvalue+=1,0,0);
		   newvalue = Read_data(0,0); // Using page 0 and location 0

		switch (newvalue)
		{
			case  0 : 		{ P2 = select[0];
			                P0 = message[0];}
			break;
			
			case  1 : 		{ P2 = select[0];
			                P0 = message[1];}
			break;	
										
			case  2 : 		{ P2 = select[0];
			                P0 = message[2];}
			break;
	    case  3 : 		{ P2 = select[0];
			                P0 = message[3];}
			break;
		  case  4 : 		{ P2 = select[0];
              			  P0 = message[4];}
		  break;
			case  5  : 		{ P2 = select[0];
			                P0 = message[5];}
			break;
			case  6 : 		{ P2 = select[0];
			                P0 = message[6];}
			break;
			case  7 : 		{ P2 = select[0];
			                P0 = message[7];}
			break;
			case  8 : 		{ P2 = select[0];
			                P0 = message[8];}
			break;
			case  9 : 		{ P2 = select[0];
			                P0 = message[9];}
			default: 
				 break;
		}
		
		
		
	if (newvalue >= 8)
		{
	    newvalue=0;
			save_data(0,0,0);
		}
	  
		index=0;
		
	}
	
	TH0 = 0x4B; //reload timer value limit
	TL0 = 0xFD;
} 

