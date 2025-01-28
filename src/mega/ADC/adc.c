
#include "../../../inc/mega.h"
#if defined ADC_MODULE
#if ADC_MODULE





/* -----------------------------------------------------------------------------
 *                          Global Variables                                   *
------------------------------------------------------------------------------*/

static volatile uint16_t gu16AdcResult = 0;

/* -----------------------------------------------------------------------------
 *                          ISR's Definitions                                  *
------------------------------------------------------------------------------*/

ISR(ADC_vect) {
#if ADC_MODE == ADC_INTERRUPT_MODE
    gu16AdcResult = ADC;
#endif
}

void adcInit(const st_adc_config_type * config_Ptr) {
    /* ADMUX Register Bits Description:
     * REFS1:0 = 00 to choose to connect external reference voltage by input
     * this voltage through AREF pin
     * ADLAR   = 0 right adjusted
     * MUX4:0  = 00000 to choose channel 0 as initialization
     */
    ADMUX = 0;
    
    
#if ADC_REF == ADC_REF_IN
    bitSet(ADMUX, REFS0);
    bitSet(ADMUX, REFS1);
#endif


#if ADC_REF == ADC_REF_EX
    bitSet(ADMUX, REFS0);
    bitClear(ADMUX, REFS1);
#endif

    /* ADCSRA Register Bits Description:
     * ADEN    = 1 Enable ADC
     * ADIE    = 0 Disable ADC Interrupt
     * ADPS2:0 pre-scalar value should be assigned as the config_Ptr to be
     * configurable
     */
    bitSet(ADCSRA, ADEN);
    bitClear(ADCSRA, ADATE);
    bitClear(ADCSRA, ADSC);

#if ADC_MODE == ADC_INTERRUPT_MODE
    bitSet(ADCSRA, ADIE);
#ifdef AUTO_TRIGGER_MODE
    bitSet(ADCSRA, ADATE);
    SFIOR = (SFIOR & NUM_TO_CLEAR_LAST_3_BITS) | \
 ((config_Ptr -> triggersource & NUM_TO_CLEAR_LAST_5_BITS) << 5);
#endif
#endif


#if ADC_MODE == ADC_POLLING_MODE
    bitClear(ADCSRA, ADIE);
#endif

    ADCSRA = (ADCSRA & NUM_TO_CLEAR_FIRST_3_BITS) | \
			(config_Ptr -> clock & NUM_TO_CLEAR_LAST_5_BITS);

}



#if ADC_MODE == ADC_INTERRUPT_MODE

void adcReadChannel(const Adc_ChannelNumber channel) {
    ADMUX = (ADMUX & NUM_TO_CLEAR_FIRST_5_BITS) |
            (channel & NUM_TO_CLEAR_LAST_5_BITS);
    bitSet(ADCSRA, ADSC); /* start conversion write '1' to ADSC */
}

uint16_t adc_value() {
    uint16_t adcRead = 0;
    ATOMIC_BEGIN;
    adcRead = gu16AdcResult;
    ATOMIC_END;
    return (adcRead);
}
#endif

#if ADC_MODE == ADC_POLLING_MODE

uint16_t adcReadChannel(Adc_ChannelNumber channel) {
    ADMUX = (ADMUX & NUM_TO_CLEAR_FIRST_5_BITS) | \
			(channel & NUM_TO_CLEAR_LAST_5_BITS);
    bitSet(ADCSRA, ADSC); /* start conversion write '1' to ADSC */
    while (bitIsClear(ADCSRA, ADIF)); /* wait for conversion to complete ADIF becomes '1' */
    bitSet(ADCSRA, ADIF); /* clear ADIF by write '1' to it :) */
    return ADC; /* return the data register */
}
#endif

#endif
#endif
