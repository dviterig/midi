//=====================================================================================================================
// copyright (c) 2021 MIDI controller
//=====================================================================================================================

#include <avr/io.h>       // Header file for basic avr input/output

#include "dependencies/delay.h"

int main(void)
{
    //printf("Hello World\n");

    DDRC=0xFF;      // PORTC declared as output
    PORTC=0xFF;     // PORTC is initially high to off the led initially

    while(1)     // infinite loop as 1 is always equals 1
    {
        PORTB |= (1<<PORTB1);
        delay_ms(1000);
        PORTB &= ~ (1<<PORTB1);
        delay_ms(1000);
    }
}