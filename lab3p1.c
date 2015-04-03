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

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )


volatile int adcVal = 0;
volatile int done = 0;


int main(void)
{
    char intPrint[8];
    initTimer1();
    initTimer2();
    initTimer3();
    initMotors();//does initPWM() for us
    initADC();
    initLCD();

    while(1){

        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }
        motorControl(100,100);
        delay2Sec();
        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }

        motorControl(100,50);
        delay2Sec();
        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }

        motorControl(50,100);
        delay2Sec();
        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }

        motorControl(-50,0);
        delay2Sec();
        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }

        motorControl(-100,-100);
        delay2Sec();
        if(done == 1)
        {
            done = 0;
            clearLCD();
            moveCursorLCD(0,0);
            sprintf(intPrint,"%d",adcVal);
            printStringLCD(intPrint);
        }


        
    }
    return 0;
}

void _ISR _ADC1Interrupt(void){
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


/*
void _ISR _CNInterrupt(void){
    
    IFS1bits.CNIF = 0;//put flag down
    delayUs(5000);//to debounce
    
}
 * */