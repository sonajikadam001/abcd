/*
Program : LAB1
*/
#include <p18f4550.h>

/*The following lines of code perform interrupt vector relocation to work with the USB bootloader. These must be used with every application program to run as a USB application.*/
extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x1000

void _reset (void)
{
	_asm goto _startup _endasm
}

#pragma code
#pragma code _HIGH_INTERRUPT_VECTOR = 0x1008
void high_ISR (void)
{
}

#pragma code
#pragma code _LOW_INTERRUPT_VECTOR = 0x1018
void low_ISR (void)
{
}
#pragma code
/*End of interrupt vector relocation*/

/*Start of main program*/
void MsDelay (unsigned int time)
{
	unsigned int i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 700; j++);/*Calibrated for a 1 ms delay in MPLAB*/
}
#define lrbit PORTBbits.RB0
#define rlbit PORTBbits.RB1
#define buzzer PORTCbits.RC0
#define relay PORTCbits.RC1


void main()
{
    unsigned char val=0;
	unsigned int k;
    INTCON2bits.RBPU=0; 
	ADCON1 = 0x0F;

	TRISBbits.TRISB0=1;
	TRISBbits.TRISB1=1;
	TRISCbits.TRISC0=0;
	TRISCbits.TRISC1=0;
	
	TRISB = 0x03;
	PORTB = 0x10;
	buzzer = 0;
	
	relay = 0;

while (1)
	{
	if (!(lrbit))
	val = 1;
	if (!(rlbit))
	val = 0;
 
	if (val)
	{
		buzzer = 1;
		relay = 1;
		LATB = LATB >>1;
		MsDelay(250);
		 if (LATB == 0x10 |LATB == 0x00)
			{
			LATB = 0x80;
		    MsDelay(250);
			}
	
		
	}
	else
	{
		buzzer = 0;
		relay = 0;
		LATB = LATB <<1;
		MsDelay(250);
		 if (LATB == 0x80 |LATB == 0x00)
			{
			LATB = 0x10;
		    MsDelay(250);
			}
	}
	}
   
}



