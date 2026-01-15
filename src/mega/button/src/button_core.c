#include "../inc/button_api.h"
#include "../../system/inc/system_api.h"
#include <string.h>

// State handler function pointer type
typedef void (*button_state_handler_t)(void);

// Internal state structure
typedef struct {
    uint8_t                key_code;
    uint8_t                current_code;
    uint8_t                debounce_counter;
    button_state_handler_t state_handler;
    button_callback_t      callbacks[8];
} button_inst_t;

static button_inst_t inst;

#include "../../gpio/inc/gpio_api.h"

// Pin mapping for buttons
static const uint8_t button_pins[] = { 4, 5, 6, 7 }; // Assuming pins for now

static uint8_t performPinScan(void) {
    uint8_t code = 0;
    for (uint8_t i = 0; i < 4; i++) {
        if (gpioRead(button_pins[i]) == 0) {
            code = i + 1; // Return 1-based index of pressed button
            break;
        }
    }
    return code;
}

static void stateIdle(void);
static void stateDebounce(void);
static void statePressed(void);

// --- State Machine Implementation ---

static void stateIdle(void) {
    uint8_t current = performPinScan();
    if (current != 0) { // Some button pressed
        inst.key_code = current;
        inst.debounce_counter = 10; // 10ms debounce
        inst.state_handler = stateDebounce;
    }
}

static void stateDebounce(void) {
    uint8_t current = performPinScan();
    if (current != inst.key_code) {
        inst.state_handler = stateIdle;
    } else {
        if (--inst.debounce_counter == 0) {
            inst.current_code = inst.key_code;
            inst.state_handler = statePressed;
            // Trigger events if needed
        }
    }
}

static void statePressed(void) {
    uint8_t current = performPinScan();
    if (current == 0) { // All buttons released
        inst.current_code = 0;
        inst.state_handler = stateIdle;
    }
}

// --- Public API ---

void buttonInit(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = stateIdle;
    // Initialize GPIOs here...
}

void buttonScan(void) {
    if (inst.state_handler) {
        inst.state_handler();
    }
}

void buttonDriver(void) {
    // This can be registered in the scheduler
    buttonScan();
}
