/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>
#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB11
#define LCD_E   LATBbits.LATB10
#define LCD_WRITE_CONTROL 0
#define LCD_WRITE_DATA 1
#define LOWER 1

#define TRIS_D7  TRISBbits.TRISB15
#define TRIS_D6  TRISBbits.TRISB14
#define TRIS_D5  TRISBbits.TRISB13
#define TRIS_D4  TRISBbits.TRISB12
#define TRIS_RS  TRISBbits.TRISB11
#define TRIS_E   TRISBbits.TRISB10

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'. */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower)
{
    if(lower)
        LATB = (LATB&0x0FFF) | ((word&0x0F)<<12);
    
    else
        LATB = (LATB&0x0FFF) | ((word&0xF0)<<8);
    
    LCD_RS = commandType;
    delayUs(1);
    LCD_E = 1;
    delayUs(1);
    LCD_E = 0;
    delayUs(delayAfter);
}


/* Using writeFourBits, this function should write the two bytes (16 bits) of a character
 * to the LCD. */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter)
{
    
    writeFourBits(word, commandType, delayAfter, 0);//sends upper
    writeFourBits(word, commandType, delayAfter, 1);//sends lower

}


/* Given a character, write it to the LCD. RS should be set to the appropriate value*/
void printCharLCD(char c) 
{
    writeLCD(c,LCD_WRITE_DATA,46);//sends character, 1, 46 us delay
}



/*Initialize the LCD */
void initLCD(void)
{
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;
    TRIS_RS = 0;
    TRIS_E = 0;
    delayUs(15000);

    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    
    // Enable 4-bit interface
    writeFourBits(0x03, LCD_WRITE_CONTROL, 4100, LOWER);
    writeFourBits(0x03, LCD_WRITE_CONTROL, 100, LOWER);
    writeLCD(0x32, LCD_WRITE_CONTROL, 100);
    
    // Function Set (specifies data width, lines, and font)
    writeLCD(0x28, LCD_WRITE_CONTROL, 40);
    writeLCD(0x08, LCD_WRITE_CONTROL, 40);// Turn Display (D) Off
    writeLCD(0x01, LCD_WRITE_CONTROL, 1500);//Clear Display 
    writeLCD(0x06, LCD_WRITE_CONTROL, 40);// Set Increment Display, No Shift

    writeLCD(0x0C, LCD_WRITE_CONTROL, 40);// Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}


/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s)
{
    while(*s)
        printCharLCD(*(s++));
}

/* Clear the display. */
void clearLCD()
{
    writeLCD(0x01, LCD_WRITE_CONTROL, 1500);
}


/* Use the command for changing the DD RAM address to put the cursor somewhere. */
void moveCursorLCD(unsigned char x, unsigned char y)
{
    //the x and y coordinates are to be ZERO indexed
    //with y = {0,1} and x = {0-7}

    unsigned char ADD = 0x80;
    
    if(y == 1)
        ADD = 0xC0;

    ADD |= x;

    writeLCD(ADD, LCD_WRITE_CONTROL, 40);
}