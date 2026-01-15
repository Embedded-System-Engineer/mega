#ifndef ADC_API_H
#define ADC_API_H

#include "adc_types.h"

// Lifecycle
void adcInit(const adc_config_t *config);

// Functional API
void     adcStartConversion(adc_channel_t channel);
uint16_t adcGetValue(void);
uint16_t adcReadPolling(adc_channel_t channel);

// Result Codes
#define ADC_SUCCESS 1
#define ADC_ERROR   0

#endif // ADC_API_H
