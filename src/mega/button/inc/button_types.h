#ifndef BUTTON_TYPES_H
#define BUTTON_TYPES_H

#include <stdint.h>

typedef enum {
    BUTTON_KEY_PRESS,
    BUTTON_KEY_RELEASE,
    BUTTON_LONG_TAP
} button_state_t;

typedef struct {
    uint8_t        keycode;
    button_state_t state;
} button_event_t;

typedef uint8_t (*button_callback_t)(button_event_t *event);

typedef struct ButtonCode {
    uint8_t            code;
    uint8_t            index;
    const struct ButtonCode *next;
} button_code_t;

#endif // BUTTON_TYPES_H
