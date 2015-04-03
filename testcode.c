

#include "p24FJ64GA002.h"
int testPWMandADC(int ADCVal)
{//this tests the ADC against the PWM, to ensure both the ADC is getting the right
    //values and that the PWM is outputting correctly.

    //we connected RB2 (a pwm output) to RA0 (adc input)
    if(ADCVal > 2 && ADCVal < 3)//set at some intermediate value
        return 1;
    else return 0;
    
}
