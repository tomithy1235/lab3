// ******************************************************************************************* //
// File:         lab2p1.c
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "lab3helper.h"
#include "pwm.h"
#include "adc.h"
#include <stdio.h>

#define TRIS_BUTTON TRISBbits.TRISB5
#define BUTTON PORTBbits.RB5

#define PRESSED 0
#define RELEASED 1

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

#define MAXPOTVAL 1010.0 //analytically found (really as 1008)


typedef enum statesEnum{

    forward, idle, backward

} states;

volatile int adcVal = 0;
volatile int done = 0;
volatile int lastOneWasForward = 1;
volatile states state = idle;

int main(void)
{
    char intPrint[8];
    int r = 0, l = 0;
    initButton();
    initTimer1();
    initTimer2();
    initTimer3();
    initMotors();//initializes PWM for us too
    initADC();
    initLCD();

    while(1){

            if(done == 1)
            {
                done = 0;
                clearLCD();
                moveCursorLCD(0,0);
                sprintf(intPrint,"%d",adcVal);
                printStringLCD(intPrint);//TODO: check this actually works for printing int
                if(state == idle)
                    motorControl(0,0);
                else
                {
                    r = (int) (100 * (2.0 * adcVal / MAXPOTVAL));
                    l = (int) (200 - r);

                    if(state == forward)
                        motorControl(l,r);
                    else if (state == backward)
                        motorControl(-l,-r);
                }
                
            }

        
    }
    return 0;
}

void _ISR _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;

    int i = 0;
    unsigned int *adcPtr;
    adcVal = 0;
    adcPtr = (unsigned int *) (&ADC1BUF0);

    for(i = 0; i < 16; i++){
        adcVal = adcVal + *adcPtr/16;
        adcPtr++;
    }

    done = 1;
}


void _ISR _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;//put flag down
    delayUs(5000);//to debounce
    if (BUTTON == PRESSED) {
        if (state == forward || state == backward)
            state = idle;
        else if (lastOneWasForward == 1) {
            lastOneWasForward = 0;
            state = backward;
        } else {
            lastOneWasForward = 1;
            state = forward;
        }
    }
}