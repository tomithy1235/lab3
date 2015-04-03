#include "p24FJ64GA002.h"
#include "adc.h"

#define TRIS_POT_IN TRISAbits.TRISA0
#define POT_IN LATAbits.LATA0

void initADC()
{//initializes ADC


    AD1PCFGbits.PCFG0 = 0;  //Set pin 2 to analog

    AD1CON1bits.FORM = 0;//sets output mode as int
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.ASAM = 1;
    AD1CON2bits.VCFG = 0;
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = 0b1111;
    AD1CON2bits.ALTS = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 1;
    AD1CON3bits.ADCS = 10;
    AD1CHS = 0;             //Configure input channels,
    AD1CSSL = 0;            //Channel scanning is disabled anyway.
    AD1CON1bits.ADON = 1; // Turn on A/D

    IEC0bits.AD1IE = 1;     //Enable the interrupt
    IFS0bits.AD1IF = 0;     //Put the flag down
}
