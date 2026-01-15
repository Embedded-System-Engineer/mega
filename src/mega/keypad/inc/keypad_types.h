#ifndef KEYPAD_TYPES_H
#define KEYPAD_TYPES_H

#include <stdint.h>

typedef enum {
    KEY_IDLE,
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_LONG_PRESS
} key_state_t;

typedef struct {
    uint8_t     code;
    key_state_t state;
} key_event_t;

typedef uint8_t (*keypad_callback_t)(key_event_t *event);

#endif // KEYPAD_TYPES_H
