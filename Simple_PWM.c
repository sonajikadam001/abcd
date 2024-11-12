
				
/** I N C L U D E S ********/

#include<p18f4550.h>




/** P R I V A T E  P R O T O T Y P E S ***************************************/

void myMsDelay (unsigned int time);

/** V E C T O R  R E M A P P I N G *******************************************/


extern void _startup (void);  // See c018i.c 
#pragma code _RESET_INTERRUPT_VECTOR = 0x1000
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x1008
void _high_ISR (void)
{
    //_asm goto High_ISR _endasm
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x1018
void _low_ISR (void)
{
   // _asm goto Low_ISR _endasm
}

#pragma code

/** D E C L A R A T I O N S **************************************************/

#pragma code

void main()
{ 
	TRISCbits.TRISC0 = 0 ;              // DC Motor IN1
    TRISCbits.TRISC1 = 0 ; 				// DC Motor IN2
	TRISCbits.TRISC2 = 0 ; 				// CCP2 PWM output, DC motor enable 
	PR2 = 0x4A;                         // set PWM period to Maximum value 
    CCPR1L = 0x12;                      // Initalise PWM duty cycle to 00 
    CCP1CON = 0x3C;                     // Configure CCP1CON as explained above.
 	T2CON = 0x07;
	PORTCbits.RC0 = 0;
	PORTCbits.RC1 = 1;
  while(1)
	{
		PR2 = 0x00;
		myMsDelay(1000);
		PR2 = 0x3F;
		myMsDelay(1000);
		PR2 = 0xBF;
		myMsDelay(1000);
		PR2 = 0xFF;
		myMsDelay(1000);
 	}   
 
}


void myMsDelay (unsigned int time)
{
	unsigned int i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 710; j++);/*Calibrated for a 1 ms delay in MPLAB*/
}