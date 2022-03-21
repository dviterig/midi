#include "MidiManager.h"

#include <avr/io.h>
#include <avr/interrupt.h>

static void startTimer(void);
static void stopTimer(void);
static void enableInterrupt(void);
static void disableInterrupt(void);

void MidiManager_Init(void)
{
    // setup Timer-0 
    TCCR0A |= (1 << WGM01); // Mode = CTC
    OCR0A = 0x01;           // f_t1/2 = 31,25Hz: MIDI sample freq
    stopTimer();

    // setup Interrupt-0
    EICRA |= (1 << ISC01);  // The falling edge of INT0 generates an interrupt request
    enableInterrupt();
}

ISR(INT0_vect) 
{
    disableInterrupt();
    startTimer();
}

ISR(TIMER0_COMPA_vect)
{
    static int counter = 0;
    counter++;

    if (counter == 8U)
    {
        counter = 0;

        stopTimer();
        enableInterrupt();
    }
}

static void startTimer(void)
{
    TCCR0B |= (1 << CS02);      // Clock/256, f_t1 = 62,5kHz
    TIMSK0 |= (1 << OCIE0A);    // Enable Interrupt TimerCounter-0 Compare Match A
}

static void stopTimer(void)
{
    TIMSK0 &= ~(1 << OCIE0A);   // Disable Interrupt TimerCounter-0 Compare Match A
    TCCR0B &= 0xFC;             // No clock source (Timer/Counter stopped)
    TCNT0 = 0;                  // Reset counter
}

static void enableInterrupt(void)
{
    EIFR |= (1 << INTF0);   // External Interrupt Flag 0
    EIMSK |= (1 << INT0);   // External pin interrupt is enabled
}

static void disableInterrupt(void)
{
    EIMSK &= ~(1 << INT0);  // External pin T0 interrupt is disabled
}