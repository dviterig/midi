//=====================================================================================================================
// copyright (c) 2021 MIDI controller
//=====================================================================================================================

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "MidiManager/MidiManager.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

int main(void)
{
    MidiManager_Init();
    sei();

    while(1)
    {
        // PORTB |= (1<<PORTB1);
        // _delay_ms(1000);
        // PORTB &= ~ (1<<PORTB1);
        // _delay_ms(1000);
    }
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
    cli();

    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);

    _delay_us(1800); /* Wait for completion of write */

    sei(); /* set Global Interrupt Enable */
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
    /* Set up address register */
    EEAR = uiAddress;
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}