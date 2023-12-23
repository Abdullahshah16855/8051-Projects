/*Write Mode
1.Send the START command from the Master.
2.Send Device (EEPROM) Address with write mode.
3.Send Register address in Device (EEPROM), Where we have to access.
4.Send the Data to the Device (EEPROM).
5.If you want to send more than one byte, keep sending that byte.
6.Finally, Send the STOP command.

Read Mode
1.Send the START command from the Master.
2.Send Device (EEPROM) Address with write mode.
3.Send Register address in Device (EEPROM), Where we have to access.
4.Send again START command or Repeated START command.
5.Send Device address with Reading mode.
6.Read the data from Device (EEPROM).
7.Finally, Send the STOP command.
*/
//Program to interface Serial EEPROM AT24C02 with 8051 microcontroller (AT89C51) 
#include<reg51.h>
#include<intrins.h>   //For using [nop()]
# define Led P0
sbit sda=P2^0;
sbit scl=P2^1;
bit ack;
unsigned char  table[]={0x1C,0x18,0x14,0x10,0x0C,0x08,0x04,0x00};   // P2 channel
unsigned char  table2[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};   // P0 is for displaying number
unsigned char Data,write,write2,i,j,a1=0,k=0,y=0;
unsigned int temp;
void delay();

/*By sending or receiving eight bits, a complete word is sent to or received by the EEPROM.
When sending a word, the acknowledgement from the EEPROM must be checked.
There should a clock (high to low transition from an initial low) between two words.
When a word is sent to the EEPROM, it sends back a zero (0) to tell the controller that the word has been received successfully by it. 
The controller reads this acknowledgement bit by sending a high to low transition at SCL. 
Acknowledgement bit must be checked every time a word is sent to the EEPROM*/

void aknowledge()	  //acknowledge condition
{
	scl=1;
	nop();  /*	The nop routine inserts a NOP instruction into the program. This routine can be used to pause for 1 CPU cycle. This routine is implemented as an intrinsic function. The NOP instruction is included inline.*/
	nop();
	scl=0;
} 

/*Start condition:
Any read or write operation in EEPROM is initiated by Start condition.
 This occurs when there is a high to low transition of SDA while SCL is high. 
(Refer the following diagram) This tells the EEPROM that words from the controller are ready for it. 
SCL is set low at the end of start condition. This is because any read or write operation first involves transfer of some words to EEPROM. 
That requires a low to high transition of clock corresponding to each bit of the word.*/

void start()		//start condition
{
	sda=1;
	scl=1;
	nop();         //No operation
	nop();
	sda=0;
	scl=0;
}

/*A stop condition is provided to terminate a read or write operation. 
A low to high transition of SDA when SCL is high sets the stop condition.*/

void stop()			//stop condition
{
	sda=0;
	scl=1;
	nop();
	nop(); 
	sda=1;
	scl=0;
}

/*A low to high transition at SCL transfers a bit to the EEPROM, 
i.e., at a low to high transition of SCL, SDA pin of EEPROM behaves as input for bits of word(s).
 If the data changes when the SCL is high, it will be misinterpreted as start or stop condition.*/

void send_byte(unsigned char value)	//send byte serially
{ 
	unsigned int i;
	unsigned char send;
	send=value;
	sda=1;
	for(i=0;i<8;i++)
	{
	//	sda=send/128;			//extracting MSB
		sda=send & 0x80;
		scl=1;
		nop();
		nop();
		send=send<<1;			//shiftng left
		scl=0;
	}
   ack=sda;					//reading acknowledge
   sda=0;
}

/*At high to low transition of SCL a bit is transferred from the EEPROM
 i.e. the SDA pin behaves as output for bits of word(s) or acknowledgement at high to low transition of the SCL.
When SCL is low again the data change is valid, i.e.,
when bits of a word are to be read or write, they are differentiated by the low of the SCL.*/

unsigned char read_byte()			//reading from EEPROM serially
{
	unsigned int i;
	sda=1;    // sda is set to default high initially
	//reead=0;
	Data=0;
	for(i=0;i<8;i++)
	{
	//	reead=reead<<1;
		scl=1;     // a high to loe transition of scl transfer Bit from EEPROM
		Data|=sda;
		nop();
		nop();
	/*	if(sda==1)
			reead++;*/
		if(i<7)
			Data<<=1;
		scl=0;
	}
	sda=0;           //SDA is again set low after transfer of LSB
	return Data;				//Returns 8 Bit Data here
}		
void save()					//save in EEPROM
{
	start();
	send_byte(0xA0);						//device address or control byte
	aknowledge();
	send_byte(0x05);						//word address
	aknowledge();
	send_byte(5);							//send Data
	aknowledge();
	stop();							   
	if(ack==0)
	{
//led=0;
	}
	aknowledge();
}
void Read()
{
	start();
	send_byte(0xA0);
	aknowledge();
	send_byte(0x05);
	aknowledge();
	start();
	send_byte(0xA1);					 //device address
	aknowledge();
	i=read_byte();
	/*aknowledge();
	j=read_byte();*/
	aknowledge();
	stop();
	if(i==5)
	{
for(a1=0;a1<10;a1++)
		{
			P2=0x18;
			for(k=0;k<15;k++)
			{delay();}
			Led=table2[a1];
		}

	}
	aknowledge();
}
/*there is 32 pages in EEPROM and each pages is having 8 bytes 
so when we send 0x00(00000)(page)(000)(word) its mean that we are accessing page 0 and on page 0 we access position 0.*/
void main()
{

	temp=0;
	while(1)
	{
		save();
		Read();
	}
}
 void delay()
 {
 TMOD=0x01;
   TH0=0x00;
    TL0=0x00;
    TR0=1;
	 while(TF0==0);
   TR0=0;
	 TF0=0;
 }