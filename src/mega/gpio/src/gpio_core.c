#include "../inc/gpio_api.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Macros for direct register access (Assuming they are defined in mega/macros.h or similar)
// For this optimization, we use standard AVR register logic

void gpio_set_mode(gpio_t pin, gpio_mode_t mode) {
    uint8_t bit = pin & 0x07;
    uint8_t port = pin >> 3;
    
    volatile uint8_t *ddr;
    volatile uint8_t *prt;
    
    // Simple mapping for ATmega (A=0, B=1, ...)
    switch(port) {
        case 0: ddr = &DDRA; prt = &PORTA; break;
        case 1: ddr = &DDRB; prt = &PORTB; break;
        case 2: ddr = &DDRC; prt = &PORTC; break;
        case 3: ddr = &DDRD; prt = &PORTD; break;
        default: return;
    }

    uint8_t sreg = SREG;
    cli();
    if (mode == GPIO_MODE_OUTPUT) {
        *ddr |= (1 << bit);
    } else {
        *ddr &= ~(1 << bit);
        if (mode == GPIO_MODE_INPUT_PULLUP) *prt |= (1 << bit);
        else *prt &= ~(1 << bit);
    }
    SREG = sreg;
}

void gpio_write(gpio_t pin, gpio_state_t state) {
    uint8_t bit = pin & 0x07;
    uint8_t port = pin >> 3;
    volatile uint8_t *prt;
    
    switch(port) {
        case 0: prt = &PORTA; break;
        case 1: prt = &PORTB; break;
        case 2: prt = &PORTC; break;
        case 3: prt = &PORTD; break;
        default: return;
    }

    uint8_t sreg = SREG;
    cli();
    if (state == GPIO_HIGH) *prt |= (1 << bit);
    else if (state == GPIO_LOW) *prt &= ~(1 << bit);
    else if (state == GPIO_TGL) *prt ^= (1 << bit);
    SREG = sreg;
}

gpio_state_t gpio_read(gpio_t pin) {
    uint8_t bit = pin & 0x07;
    uint8_t port = pin >> 3;
    volatile uint8_t *pin_reg;
    
    switch(port) {
        case 0: pin_reg = &PINA; break;
        case 1: pin_reg = &PINB; break;
        case 2: pin_reg = &PINC; break;
        case 3: pin_reg = &PIND; break;
        default: return GPIO_LOW;
    }
    
    return (*pin_reg & (1 << bit)) ? GPIO_HIGH : GPIO_LOW;
}
