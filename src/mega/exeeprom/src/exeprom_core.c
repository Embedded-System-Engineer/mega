#include "../inc/exeprom_api.h"
#include "../../twi/inc/twi_api.h"
#include "../../system/inc/system_api.h"
#include <string.h>

typedef void (*exeprom_state_handler_t)(void);

typedef struct {
    uint16_t                addr;
    uint8_t                *buffer;
    uint8_t                 length;
    uint8_t                 read_buf[16];
    exeprom_status_t       status;
    exeprom_state_handler_t state_handler;
    system_timer_t         timer;
} exeprom_inst_t;

static exeprom_inst_t inst;

static void state_idle(void);
static void state_reading(void);
static void state_comparing(void);
static void state_writing(void);

// --- State Handlers ---

static void state_idle(void) {
    // Wait for command
}

static void state_reading(void) {
    twi_package_t pkg = {
        .chip = 0xA0,
        .addr_length = 2,
        .buffer = inst.read_buf,
        .length = inst.length
    };
    pkg.addr[0] = inst.addr >> 8;
    pkg.addr[1] = inst.addr & 0xFF;

    if (twi_master_read(&pkg) == TWI_SUCCESS) {
        if (inst.status == EXEPROM_READING) {
            inst.status = EXEPROM_IDLE;
            inst.state_handler = state_idle;
        } else {
            inst.state_handler = state_comparing;
        }
    }
}

static void state_comparing(void) {
    if (memcmp(inst.buffer, inst.read_buf, inst.length) == 0) {
        inst.status = EXEPROM_IDLE;
        inst.state_handler = state_idle;
    } else {
        inst.state_handler = state_writing;
    }
}

static void state_writing(void) {
    twi_package_t pkg = {
        .chip = 0xA0,
        .addr_length = 2,
        .buffer = inst.buffer,
        .length = inst.length
    };
    pkg.addr[0] = inst.addr >> 8;
    pkg.addr[1] = inst.addr & 0xFF;

    if (twi_master_write(&pkg) == TWI_SUCCESS) {
        inst.status = EXEPROM_IDLE;
        inst.state_handler = state_idle;
    }
}

// --- Public API ---

void exepromInit(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = state_idle;
    inst.status = EXEPROM_IDLE;
}

void exepromDriver(void) {
    if (inst.state_handler) inst.state_handler();
}

void exepromRead(uint16_t addr, uint8_t *buf, uint8_t len) {
    if (inst.status != EXEPROM_IDLE) return;
    inst.addr = addr;
    inst.buffer = buf;
    inst.length = len;
    inst.status = EXEPROM_READING;
    inst.state_handler = state_reading;
}

void exepromWrite(uint16_t addr, uint8_t *buf, uint8_t len) {
    if (inst.status != EXEPROM_IDLE) return;
    inst.addr = addr;
    inst.buffer = buf;
    inst.length = len;
    inst.status = EXEPROM_WRITING; // We usually read before write to compare (update pattern)
    inst.state_handler = state_reading; 
}

uint8_t exepromIsReady(void) {
    return inst.status == EXEPROM_IDLE;
}
