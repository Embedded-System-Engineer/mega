#ifndef SIGNAL_GEN_TYPES_H
#define SIGNAL_GEN_TYPES_H

#include <stdint.h>

typedef struct {
    uint16_t period;
    uint8_t  duty;
    uint8_t  toggle_count;
    uint8_t  sleep_count;
    uint8_t  repeat;
} signal_config_t;

#endif // SIGNAL_GEN_TYPES_H
