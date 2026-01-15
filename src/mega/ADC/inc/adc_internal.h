#ifndef ADC_INTERNAL_H
#define ADC_INTERNAL_H

#include "adc_types.h"
#include <avr/io.h>

typedef struct {
    volatile uint16_t last_result;
    adc_config_t      current_config;
} adc_instance_t;

extern adc_instance_t adc_inst;

// Internal Helpers
#define ADC_NUM_TO_CLEAR_FIRST_3_BITS 0xF8
#define ADC_NUM_TO_CLEAR_LAST_3_BITS 0x1F
#define ADC_NUM_TO_CLEAR_LAST_5_BITS 0x07
#define ADC_NUM_TO_CLEAR_FIRST_5_BITS 0xE0

#endif // ADC_INTERNAL_H
