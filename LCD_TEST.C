/********************************************************************************/
/*This program demonstrates the interfacing of LCD to PIC18F4550 microcontroller*/
/********************************************************************************/

/*
LCD DATA port----PORT D
signal port------PORT E
    rs-------RE0
    rw-------RE1
    en-------RE2
*/
#include <p18f4550.h>

//LCD data pins connected to PORTD and control pins connected to PORTE
#define LCD_DATA    PORTD               //LCD data port
#define ctrl        PORTE               //LCD signal port
#define en          PORTEbits.RE2      // enable signal
#define rw          PORTEbits.RE1      // read/write signal
#define rs          PORTEbits.RE0     // register select signal
#define BUSY        PORTDbits.RD7

//LCD function definitions
void LCD_Busy(void);
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_write_string(static char *str);

/*The following lines of code perform interrupt vector relocation to work with the USB bootloader. These must be
used with every application program to run as a USB application.*/
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
//Function to generate delay
void myMsDelay (unsigned int time)
{
        unsigned int i, j;
        for (i = 0; i < time; i++)
                for (j = 0; j < 710; j++);/*Calibrated for a 1 ms delay in MPLAB*/
}


// Function to initialise the LCD
void init_LCD(void)
{
    LCD_cmd(0x38);      // initialization of 16X2 LCD in 8bit mode
    myMsDelay(15);

    LCD_cmd(0x01);      // clear LCD
    myMsDelay(15);

    LCD_cmd(0x0C);      // cursor off
    myMsDelay(15);

    LCD_cmd(0x80);      // ---8 go to first line and --0 is for 0th position
    myMsDelay(15);

            // ---8 go to first line and --0 is for 0th position

    return;
}
//Function to pass command to the LCD
void LCD_cmd(unsigned char cmd)
{
    LCD_DATA = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
    return;
}

//Function to write data to the LCD
void LCD_write(unsigned char data)
{
    LCD_DATA = data;
    rs = 1;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
    return ;
}
//Function to split the string into individual characters and call the LCD_write function
void LCD_write_string(static char *str)   //store address value of the string in pointer *str
{
    int i = 0;
    while (str[i] != 0)
    {
        LCD_write(str[i]);      // sending data on LCD byte by byte
        myMsDelay(15);
                i++;
    }
    return;
}

void main(void)
{     
     char var1[] = "WELCOME";
  	 ADCON1 = 0x0F;        //Configuring the PORTE pins as digital I/O 
     TRISD = 0x00;         //Configuring PORTD as output
     TRISE = 0x00;         //Configuring PORTE as output
	
    
     init_LCD();           // initialization of LCD
     myMsDelay(50);       // delay of 50 mili seconds
     LCD_write_string(var1);
     while (1);
}
