#ifndef ADC_TYPES_H
#define ADC_TYPES_H

#include <stdint.h>

typedef enum {
    ADC_CLOCK_DIV1,   // F_CPU/1
    ADC_CLOCK_DIV2,   // F_CPU/2
    ADC_CLOCK_DIV4,   // F_CPU/4
    ADC_CLOCK_DIV8,   // F_CPU/8
    ADC_CLOCK_DIV16,  // F_CPU/16
    ADC_CLOCK_DIV32,  // F_CPU/32
    ADC_CLOCK_DIV64,  // F_CPU/64
    ADC_CLOCK_DIV128  // F_CPU/128
} adc_clock_t;

typedef enum {
    ADC_CH0, ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5, ADC_CH6, ADC_CH7,
    ADC_DIF_0_0_10X,  ADC_DIF_1_0_10X,
    ADC_DIF_0_0_200X, ADC_DIF_1_0_200X,
    ADC_DIF_2_2_10X,  ADC_DIF_3_2_10X,
    ADC_DIF_2_2_200X, ADC_DIF_3_2_200X,
    ADC_DIF_0_1, ADC_DIF_1_1, ADC_DIF_2_1, ADC_DIF_3_1, ADC_DIF_4_1, ADC_DIF_5_1,
    ADC_DIF_6_1, ADC_DIF_7_1, ADC_DIF_0_2, ADC_DIF_1_2, ADC_DIF_2_2, ADC_DIF_3_2, ADC_DIF_4_2
} adc_channel_t;

typedef enum {
    ADC_TRIG_FREE_RUN,
    ADC_TRIG_COMP,
    ADC_TRIG_EXT0,
    ADC_TRIG_TIM0_COMP_MATCH,
    ADC_TRIG_TIM0_OVF,
    ADC_TRIG_TIM1_COMP_MATCH_B,
    ADC_TRIG_TIM1_OVF,
    ADC_TRIG_TIM1_CAPT
} adc_trigger_t;

typedef struct {
    adc_clock_t   clock;
    adc_channel_t channel;
    adc_trigger_t trigger;
} adc_config_t;

#endif // ADC_TYPES_H
