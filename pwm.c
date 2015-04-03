#include "p24FJ64GA002.h"
#include "pwm.h"

#define RP2 RPOR1bits.RP2R
#define RP3 RPOR1bits.RP3R
#define RP6 RPOR3bits.RP6R
#define RP7 RPOR3bits.RP7R

#define TRIS_RP2 TRISBbits.TRISB2
#define TRIS_RP3 TRISBbits.TRISB3
#define TRIS_RP6 TRISBbits.TRISB6
#define TRIS_RP7 TRISBbits.TRISB7

#define OCR1 18
#define OCR2 19
#define OCR3 20
#define OCR4 21

//TODO: do I need to configure PWM pins for output?

void initPWM(){
    //initalizes PWM for all 4 

    T3CONbits.TCKPS = 3;// prescaler
    TMR3 = 0;
    PR3 = 56;//PR3 = (1ms)*(FCY)/256 - 1

    OC1CONbits.OCTSEL = 1; // using timer 3
    OC2CONbits.OCTSEL = 1; 
    OC3CONbits.OCTSEL = 1; 
    OC4CONbits.OCTSEL = 1; 
    
    OC1CONbits.OCM = 6;//Using PWM with no fault pin
    OC2CONbits.OCM = 6;
    OC3CONbits.OCM = 6;
    OC4CONbits.OCM = 6;

    RP2 = OCR1; // map OC1 to pin 6
    RP3 = OCR2; // map OC2 to pin 7
    RP6 = OCR3; // map OC3 to pin 15
    RP7 = OCR4; // map OC4 to pin 16

    OC1R = 0; //very important
    OC2R = 0;
    OC3R = 0;
    OC4R = 0;

    OC1RS = 0;
    OC2RS = 0;
    OC3RS = 0;
    OC4RS = 0;

    T3CONbits.TON = 1;
}

void changeDuty1(int percent)
{//changes the OC1 duty cycle
    //PR is 56
    //if(percent >= 0 || percent <= 100)
        OC1RS = (unsigned int) (100-percent)*0.56;
}

void changeDuty2(int percent)
{//Changes OC2 duty cycle
    //PR is 56
    //if(percent >= 0 || percent <= 100)
        OC2RS = (unsigned int) (100-percent)*0.56;
}

void changeDuty3(int percent)
{//changes OC3 duty cycle
    //PR is 56
    //if(percent >= 0 || percent <= 100)
        OC3RS = (unsigned int) (100-percent)*0.56;
}

void changeDuty4(int percent)
{//changes OC4 duty cycle
    //PR is 56
    //if(percent >= 0 || percent <= 100)
        OC4RS = (unsigned int) (100-percent)*0.56;
}