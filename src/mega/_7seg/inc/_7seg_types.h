#ifndef _7SEG_TYPES_H
#define _7SEG_TYPES_H

#include <stdint.h>

#ifndef MAX_DISPLAY_SUPPORT
#define MAX_DISPLAY_SUPPORT 4
#endif

typedef struct {
    uint8_t   max_digit;
    uint8_t   display_type; // 1: Common Cathode, 0: Common Anode
} _7seg_param_t;

typedef struct {
    uint8_t       *data;
    uint8_t       *pins_digits;
    _7seg_param_t  param;
    uint8_t        current_digit;
    void (*state_handler)(void *arg);
} _7seg_instance_t;

#endif // _7SEG_TYPES_H
