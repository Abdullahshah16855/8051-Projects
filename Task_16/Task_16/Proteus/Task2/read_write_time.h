#ifndef read_write_time.h
#define read_write_time.h
#define LCD_DATA  P1

unsigned char lcdCmds[4] = {0x38,0x01,0x0E};
void customDelay(unsigned char, unsigned char);
void initializeSerial();
void lcdCmd(unsigned char);
void lcdData(unsigned char);
void lcdMessage(unsigned char *);
void oneSecondDelay();
void asciiDisplay(unsigned char, unsigned char, unsigned char);
void rtcCommand(unsigned char );
unsigned char rtcRead(unsigned char);
void rtcWrite(unsigned char, unsigned char);
void displayTime();
void setTime(unsigned char);
void setDate(unsigned char);
void initializeAll();
void systemView();
void writeBurst();
void initialize_serial();





#endif