#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include <stdint.h>

typedef uint32_t millis_t;
typedef uint32_t micros_t;
typedef uint32_t tick_t;
typedef uint32_t time_t;

typedef struct {
    uint32_t end_time;
} system_timer_t;

#endif // SYSTEM_TYPES_H
