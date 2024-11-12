/********************************************************************/
//This program demonstrates the use of timer   		   //								                                                     */
/******************************************************************/


#include <p18f4550.h>
#include <stdlib.h>


/*The following lines of code perform interrupt vector relocation to work with the USB bootloader. These must be
used with every application program to run as a USB application.*/
void timer_isr(void);

extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x1000
void _reset (void)
{
	_asm goto _startup _endasm

}
#pragma code
//The program execution comes to this point when a timer interrupt is generated
#pragma code _HIGH_INTERRUPT_VECTOR = 0x1008
void high_ISR (void)
{
	
	_asm goto timer_isr _endasm    //The program is relocated to execute the interrupt routine timer_iser

}
//
#pragma code
//
#pragma code _LOW_INTERRUPT_VECTOR = 0x1018
 void low_ISR (void)
{

}
#pragma code
// This function is executed as soon as the timer interrupt is generated due to timer overflow
#pragma interrupt timer_isr
void timer_isr(void)
{
	TMR0H = 0XFF;                         // Reloading the timer values after overflow
	TMR0L = 0X00;
	PORTB = ~PORTB;                         //Toggle the PORTB led outputs RB0 - RB3
 	INTCONbits.TMR0IF = 0;	             //Resetting the timer overflow interrupt flag

}





void main()
{	
	ADCON1 = 0x0F;        //Configuring the PORTE pins as digital I/O 
	
	TRISB = 0;                  //Configruing the LED port pins as outputs
	PORTB = 0xFF;                //Setting the initial value of the LED's after reset	
	T0CON = 0x00;				//Set the timer to 16-bit mode,internal instruction cycle clock,1:256 prescaler
  	TMR0H = 0xFF;                // Reset Timer0 to 0x48E5 TO MAKE DELAY OF 1 SECOND
  	TMR0L = 0x00;
   	INTCONbits.TMR0IF = 0;      // Clear Timer0 overflow flag
	INTCONbits.TMR0IE = 1;		// TMR0 interrupt enabled
 	T0CONbits.TMR0ON = 1;		// Start timer0
	INTCONbits.GIE = 1;			// Global interrupt enabled

	while(1);                      //Program execution stays here untill the timer overflow interrupt is generated
	
}
