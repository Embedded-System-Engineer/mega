#include "../inc/eeprom_api.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

typedef void (*eeprom_state_handler_t)(void);

typedef struct {
    uint16_t               addr;
    uint8_t               *buf;
    uint8_t                size;
    uint8_t                idx;
    eeprom_state_handler_t state_handler;
} eeprom_inst_t;

static eeprom_inst_t inst;

static void state_idle(void);
static void state_writing(void);
static void state_reading(void);

static void state_idle(void) {
    // Do nothing, wait for API call to change state
}

static void state_writing(void) {
    if (!(EECR & (1 << EEWE))) { // If not busy
        if (inst.idx < inst.size) {
            EEAR = inst.addr + inst.idx;
            EEDR = inst.buf[inst.idx];
            EECR |= (1 << EEMWE);
            EECR |= (1 << EEWE);
            inst.idx++;
        } else {
            inst.state_handler = state_idle;
        }
    }
}

static void state_reading(void) {
    if (inst.idx < inst.size) {
        EEAR = inst.addr + inst.idx;
        EECR |= (1 << EERE);
        inst.buf[inst.idx] = EEDR;
        inst.idx++;
    } else {
        inst.state_handler = state_idle;
    }
}

void eeprom_init(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = state_idle;
}

void eeprom_driver(void) {
    if (inst.state_handler) {
        inst.state_handler();
    }
}

void eeprom_write(uint16_t addr, const uint8_t *data, uint8_t size) {
    if (inst.state_handler != state_idle) return;
    inst.addr = addr;
    inst.buf = (uint8_t *)data;
    inst.size = size;
    inst.idx = 0;
    inst.state_handler = state_writing;
}
