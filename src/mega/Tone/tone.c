/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : Tone.h                                                                   |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 11 Byte Used by one Pin                                                  |
| < PROGRAM USAGE            : 430 Byte by One Pin Used                                                 |                                                                         |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */
#include "../../../inc/mega.h"
#if defined TONE_MODULE
#if TONE_MODULE

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef struct {
    stTimer_TimeOut_t Freq;
    uint8_t duration;
    uint16_t Period[2];
    uint8_t toggle;
    uint8_t State;
} stTone_t;

/*
 *<@var gstTones : max tones used in system
 */
static stTone_t gstTones[TONES_MAX_PINS_USED];
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < myTone >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t myTone                                                                 |  
 | < @Description       : run Timer                                                                      |                                               |
 | < @return            :void                                                   |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void myTone(gpio_t pin, EN_GPIO_t defalutstate, stTone_t *tone);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < myTone >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t myTone                                                                 |  
 | < @Description       : run Timer                                                                      |                                               |
 | < @return            :void                                                   |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void myTone(gpio_t pin, EN_GPIO_t defalutstate, stTone_t *tone) {
    if (!tone->State) {
        return;
    }


    if (sysIsTimeoutMs(&tone->Freq) == 0) {
        if (tone->toggle == 0) {
            if (tone->duration == 0) {
                tone->State = 0;
                tone->toggle = 0;
                digitalPinWrite(pin, defalutstate);
                return;
            }
            tone->duration--;
        }
        
        sysSetPeriodMS(&tone->Freq, tone->Period[tone->toggle]);
        tone->toggle ^= 1;
        if (tone->Period[0] != 0) {
            digitalPinWrite(pin, GPIO_TGL);
        }
        
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < isTonePlaying >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : check the Tone is Playing or not                                               |   
 | < @Param Index       : Signal Index in array                                                          |
 | < @return            : 1 is Playing , 0 is not Playing                                                |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t isTonePlaying(uint8_t Index) {
    return gstTones[Index].State;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Toneplay >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void Toneplay                                                                  |  
 | < @Description       : Play Tone                                                                      | 
 | < @Param Pin         : GPIO Pin access                                                                |
 | < @Param Period      : Period gnerated                                                                |  
 | < @Param duration    : time to generate this Frequncy                                                 |
 | < @Param Index       : Index of the Pin From 0 to max pin used -1                                     |
 | <@Param Ton          : Time of on                                                                    |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void Toneplay(uint8_t Index, uint16_t Period, uint8_t duration, uint16_t Ton) {
    gstTones[Index].Period[0] = Ton;
    gstTones[Index].Period[1] = Period - Ton;
    gstTones[Index].toggle = 0;
    gstTones[Index].duration = duration;
    gstTones[Index].State = 1;
    sysSetPeriodMS(&gstTones[Index].Freq, 0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Tonestop >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : stop this tone                                                                 |  
 | < @Param pin         : access gpio pin                                                                |
 | < @Param  Index      : Signel Index in array                                                          |
 | < @param default     : state low or high                                                              |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void Tonestop(gpio_t pin, uint8_t Index, EN_GPIO_t defaultState) {
    gstTones[Index].State = 0;
    gstTones[Index].toggle = 0;
    digitalPinWrite(pin, defaultState);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneInit >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneInit                                                                  |  
 | < @Description       : Init I/O with MAX_PIN Used                                                     |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneInit() {
#if TONES_MAX_PINS_USED == 4
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN2_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN3_GPIO, MODE_OUTPUT);

    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN3_GPIO, TONE_PIN3_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 3
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN2_GPIO, MODE_OUTPUT);

    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 2
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 1
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
#else 
#error "max Pin is suppor from 1 to 4 pins"
#endif

    for (uint8_t i = 0; i < TONES_MAX_PINS_USED; i++) {
        gstTones[i].State = 0;
        gstTones[i].Period[0] = 0;
        gstTones[i].Period[1] = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneDriver >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneDriver                                                                |  
 | < @Description       : run in background task                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneDriver() {
#if TONES_MAX_PINS_USED == 4
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
    myTone(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE, &gstTones[2]);
    myTone(TONE_PIN3_GPIO, TONE_PIN3_DEFALUT_STATE, &gstTones[3]);
#elif TONES_MAX_PINS_USED == 3
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
    myTone(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE, &gstTones[2]);
#elif TONES_MAX_PINS_USED == 2
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
#elif TONES_MAX_PINS_USED == 1
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
#else 
#error "max Pin is suppor from 1 to 4 pins"
#endif
}

#endif
#endif