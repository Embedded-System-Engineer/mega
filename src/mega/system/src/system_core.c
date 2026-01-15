#include "../inc/system_api.h"
#include <avr/interrupt.h>
#include <avr/io.h>

static volatile millis_t system_millis_cnt = 0;
static volatile time_t   system_time_cnt = 0;

micros_t system_micros(void) {
    millis_t m;
    uint8_t t;
    uint8_t sreg = SREG;
    cli();
    m = system_millis_cnt;
    t = TCNT0;
    if ((TIFR0 & (1 << OCF0A)) && (t < OCR0A)) m++;
    SREG = sreg;
    return (m * 1000) + (t * (64 * 1000000UL / F_CPU));
}

time_t system_time(void) {
    time_t t;
    uint8_t sreg = SREG;
    cli();
    t = system_time_cnt;
    SREG = sreg;
    return t;
}

ISR(TIMER0_COMPA_vect) {
    system_millis_cnt++;
    if (system_millis_cnt % 1000 == 0) {
        system_time_cnt++;
    }
}

void system_init(void) {
    // Configure Timer0 for 1ms interrupts based on F_CPU
    TCCR0A = (1 << WGM01); // CTC mode
    OCR0A = (F_CPU / 64 / 1000) - 1; // Assuming 64 prescaler
    TIMSK0 |= (1 << OCIE0A);
    TCCR0B = (1 << CS01) | (1 << CS00);
}

void system_start(void) { sei(); }
void system_stop(void) { cli(); }

millis_t system_millis(void) {
    millis_t m;
    uint8_t sreg = SREG;
    cli();
    m = system_millis_cnt;
    SREG = sreg;
    return m;
}

void system_set_timer_ms(system_timer_t *timer, millis_t period) {
    timer->end_time = system_millis() + period;
}

uint8_t system_is_timeout(system_timer_t *timer) {
    return (system_millis() >= timer->end_time);
}
