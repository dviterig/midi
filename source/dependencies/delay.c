#include "delay.h"

#include <util/delay.h>   // header file for delay generation

void delay_ms(int time)
{
    while (time > 0)
    {
        _delay_ms(1);
        --time;
    }
}