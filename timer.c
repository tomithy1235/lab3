/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"
#include "lcd.h"
#define ONE_SECOND F_CY/256.0 - 1
#define TEN_MS .01*F_CY/256.0 - 1

void delayUs(unsigned int delay)
//delays for given microseconds
{
    PR2 = (unsigned int) (delay*14.7456);
    
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0){ }
    IFS0bits.T2IF = 0;
}

void delay1Sec()
//always delays for 1 second
{
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0){ }
    IFS0bits.T1IF = 0;
}

void delay2Sec()
//always delays for 2 seconds
{
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0){ }
    IFS0bits.T1IF = 0;
    while(IFS0bits.T1IF == 0){ }
    IFS0bits.T1IF = 0;
    //This just delays 1 second twice
}

void initTimer1()
//initializes timer1 (no interrupts)
{
    PR1 = ONE_SECOND;
    TMR1 = 0;
    T1CONbits.TCKPS = 0b11;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 0;
}

void initTimer2()
//initializes timer 2 (no interrupts)
{
    T2CONbits.TCKPS = 0b00;
    TMR2 = 0;
    T2CONbits.TON = 0;
    IFS0bits.T2IF = 0;
}

void initTimer3()
//initializes timer 3 (no interrupts)
{
    T3CONbits.TCKPS = 3;
    TMR3 = 0;
    T3CONbits.TON = 0;
    IFS0bits.T3IF = 0;
}