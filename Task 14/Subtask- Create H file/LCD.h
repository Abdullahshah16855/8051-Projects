#ifndef LCD.h
#define LCD.h

#define lcd P0

sbit rs=P2^6;
sbit e=P2^7;
sbit rw=P2^5;

void delay (int);
void cmd (char);
void display (char);
void Write (char *);
void init (void);

#endif
