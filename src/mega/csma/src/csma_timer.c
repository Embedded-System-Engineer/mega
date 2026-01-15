#include "inc/csma_internal.h"
#include "../../../inc/mega.h"

// Timer configuration for 16-bit Timer1 on ATMega platforms
// Using CTC mode (4) with OCR1A as top.

void csmaHwTimerInit(void) {
    TCCR1B = 0x00; // Stop
    TCNT1  = 0;
    TIMSK &= ~_BV(OCIE1A);
}

void csmaHwTimerStart(uint16_t time_us) {
    if (time_us == 0) return;

    TCCR1B = 0x00; // Stop
    TCNT1  = 0;
    TCCR1A = 0x00; 
    
    uint16_t freq = (uint16_t)((1000000UL / time_us) + 1UL);
    uint16_t value = (uint16_t)(F_CPU / (64UL * freq));
    
    OCR1A = value;
    TCCR1B = 0x0B; // Prescaler 64, Mode 4 (CTC)
    TIMSK |= _BV(OCIE1A);
}

void csmaHwTimerStop(void) {
    TCCR1B = 0x00;
    TIMSK &= ~_BV(OCIE1A);
}

// Timer1 Compare Match A ISR
ISR(TIMER1_COMPA_vect) {
    csmaHwTimerStop();
    csmaDispatchState();
}
