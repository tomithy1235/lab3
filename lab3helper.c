#include "lab3helper.h"
#include "p24fj64ga002.h"
#include "pwm.h"

#define TRIS_LEFT_MOTOR_EN TRISAbits.TRISA2
#define TRIS_RIGHT_MOTOR_EN TRISAbits.TRISA3
#define LEFT_MOTOR_EN LATAbits.LATA2
#define RIGHT_MOTOR_EN LATAbits.LATA3

#define TRIS_BUTTON TRISBbits.TRISB5
#define BUTTON PORTBbits.RB5

void initMotors()
{//initializes the motors' enable pins and calls the initPWM()
    initPWM();
    TRIS_LEFT_MOTOR_EN = 0;
    TRIS_RIGHT_MOTOR_EN = 0;
    
    RIGHT_MOTOR_EN = 0;
    LEFT_MOTOR_EN = 0;
}

void motorControl(int l, int r)
{
    //should take in 2 ints in the range of [-100,100]
    //If it's outside of the range, it's handled accordingly
    //-100 is 100% speed backwards and +100 is 100% speed forwards
    //This also controls the motor enables accordingly

    if(l == 0)
        LEFT_MOTOR_EN = 0;
    else
        LEFT_MOTOR_EN = 1;

    if (l > 100)
        l = 100;
    else if (l < -100)
        l = -100;

    if(r == 0)
        RIGHT_MOTOR_EN = 0;
    else
        RIGHT_MOTOR_EN = 1;

    if (r > 100)
        r = 100;
    else if (r < -100)
        r = -100;


    //Handle the actual values now:
    if(l>=0){
        changeDuty1(0);
        changeDuty2(l);
    }
    else{
        changeDuty1(-l);
        changeDuty2(0);
    }

    if(r>=0){
        changeDuty3(r);
        changeDuty4(0);
    }
    else{
        changeDuty3(0);
        changeDuty4(-r);
    }
}

void initButton()
{
    TRIS_BUTTON = 1;//input
    //TODO: write all the interrupt enable stuff:
    CNPU2bits.CN27PUE = 1;//set pull up resistor
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;//enable interrupts
    IFS1bits.CNIF = 0;
}