#include "../inc/keypad_api.h"
#include "../../gpio/inc/gpio_api.h"
#include "../../system/inc/system_api.h"
#include <string.h>

typedef void (*keypad_state_handler_t)(void);

typedef struct {
    uint8_t               key_code;
    uint8_t               row_idx;
    uint8_t               col_val;
    keypad_state_handler_t state_handler;
    system_timer_t        timer;
    keypad_callback_t     callbacks[16];
} keypad_inst_t;

static keypad_inst_t inst;

static void stateRowScan(void);
static void stateDebounce(void);
static void stateProcess(void);

// Pin mapping (simplified)
static const uint8_t row_pins[] = { KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN };
static const uint8_t col_pins[] = { KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN };

// --- State Machine Handlers ---

static void stateRowScan(void) {
    // Set all cols high, then pull one low and check rows
    for (uint8_t c = 0; c < 4; c++) {
        gpioWrite(col_pins[c], 0);
        for (uint8_t r = 0; r < 4; r++) {
            if (gpioRead(row_pins[r]) == 0) {
                inst.key_code = (r * 4) + c;
                inst.state_handler = stateDebounce;
                systemSetTimerMs(&inst.timer, 20);
                gpioWrite(col_pins[c], 1);
                return;
            }
        }
        gpioWrite(col_pins[c], 1);
    }
}

static void stateDebounce(void) {
    if (systemIsTimeout(&inst.timer)) {
        // Re-check same key
        uint8_t r = inst.key_code / 4;
        uint8_t c = inst.key_code % 4;
        gpioWrite(col_pins[c], 0);
        if (gpioRead(row_pins[r]) == 0) {
            inst.state_handler = stateProcess;
        } else {
            inst.state_handler = stateRowScan;
        }
        gpioWrite(col_pins[c], 1);
    }
}

static void stateProcess(void) {
    key_event_t event = { .code = inst.key_code, .state = KEY_PRESSED };
    if (inst.callbacks[inst.key_code]) {
        inst.callbacks[inst.key_code](&event);
    }
    
    // Wait for release
    uint8_t r = inst.key_code / 4;
    uint8_t c = inst.key_code % 4;
    gpioWrite(col_pins[c], 0);
    if (gpioRead(row_pins[r]) == 1) {
        inst.state_handler = stateRowScan;
    }
    gpioWrite(col_pins[c], 1);
}

// --- Public API ---

void keypadInit(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = stateRowScan;
    
    for (int i = 0; i < 4; i++) {
        gpioSetMode(row_pins[i], GPIO_MODE_INPUT_PULLUP);
        gpioSetMode(col_pins[i], GPIO_MODE_OUTPUT);
        gpioWrite(col_pins[i], 1);
    }
}

void keypadDriver(void) {
    if (inst.state_handler) inst.state_handler();
}
