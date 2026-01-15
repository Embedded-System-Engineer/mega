#include "../inc/adc_api.h"
#include "../inc/adc_internal.h"
#include <avr/interrupt.h>

adc_instance_t adc_inst;

ISR(ADC_vect) {
    adc_inst.last_result = ADC;
}

void adcInit(const adc_config_t *config) {
    if (!config) return;
    
    adc_inst.current_config = *config;
    
    // Select Reference Voltage (Standardized to Internal for this system as per original code)
    // ADMUX REFS1:0
    ADMUX = 0;
#ifdef ADC_REF_INTERNAL
    ADMUX |= (1 << REFS1) | (1 << REFS0);
#else
    ADMUX |= (1 << REFS0); // External AREF
#endif

    // Enable ADC, Set Prescaler
    ADCSRA = (ADCSRA & ADC_NUM_TO_CLEAR_FIRST_3_BITS) | (config->clock & 0x07);
    ADCSRA |= (1 << ADEN);

    // Set Trigger Mode if applicable
    if (config->trigger != ADC_TRIG_FREE_RUN) {
        ADCSRA |= (1 << ADATE);
        SFIOR = (SFIOR & 0x1F) | (config->trigger << 5);
    }

    // Enable Interrupt if requested (Standardizing based on system config)
#ifdef ADC_USE_INTERRUPTS
    ADCSRA |= (1 << ADIE);
#endif
}

void adcStartConversion(adc_channel_t channel) {
    ADMUX = (ADMUX & ADC_NUM_TO_CLEAR_FIRST_5_BITS) | (channel & 0x1F);
    ADCSRA |= (1 << ADSC);
}

uint16_t adcGetValue(void) {
    uint16_t result;
    // Disable interrupts to ensure atomic 16-bit read
    uint8_t sreg = SREG;
    cli();
    result = adc_inst.last_result;
    SREG = sreg;
    return result;
}

uint16_t adcReadPolling(adc_channel_t channel) {
    ADMUX = (ADMUX & ADC_NUM_TO_CLEAR_FIRST_5_BITS) | (channel & 0x1F);
    ADCSRA |= (1 << ADSC); // Start
    while (!(ADCSRA & (1 << ADIF))); // Wait
    ADCSRA |= (1 << ADIF); // Clear flag
    return ADC;
}
