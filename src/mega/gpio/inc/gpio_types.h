#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

#include <stdint.h>

typedef uint8_t gpio_t;

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_INPUT_PULLUP
} gpio_mode_t;

typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1,
    GPIO_TGL  = 2
} gpio_state_t;

#endif // GPIO_TYPES_H
