#ifndef TONE_TYPES_H
#define TONE_TYPES_H

#include <stdint.h>
#include "../../system/inc/system_api.h"

#ifndef TONES_MAX_PINS_USED
#define TONES_MAX_PINS_USED 4
#endif

typedef struct {
    stTimer_TimeOut_t timer;
    uint8_t           duration;
    uint16_t          period[2]; // [0] is ON time, [1] is OFF time
    uint8_t           toggle;
    uint8_t           is_active;
    void (*state_handler)(void *arg);
} tone_channel_t;

#endif // TONE_TYPES_H
