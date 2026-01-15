#include "../inc/twi_api.h"
#include <avr/io.h>
#include <avr/interrupt.h>

typedef void (*twi_state_handler_t)(uint8_t status);

typedef struct {
    twi_package_t       *pkg;
    volatile uint8_t     busy;
    volatile twi_status_t status;
    uint16_t             byte_count;
    uint8_t              is_read;
    twi_state_handler_t  state_handler;
} twi_inst_t;

static twi_inst_t inst;

// Forward declarations of state handlers
static void state_start(uint8_t status);
static void state_address(uint8_t status);
static void state_write_data(uint8_t status);
static void state_read_data(uint8_t status);

static void state_start(uint8_t status) {
    if (status == 0x08 || status == 0x10) { // START / REPEATED START
        uint8_t addr = (inst.pkg->chip << 1) | (inst.is_read ? 1 : 0);
        TWDR = addr;
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
        inst.state_handler = state_address;
    } else {
        inst.status = TWI_ERROR;
        inst.busy = 0;
    }
}

static void state_address(uint8_t status) {
    if (status == 0x18 || status == 0x40) { // SLA+W ACK or SLA+R ACK
        if (inst.is_read) {
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE) | (inst.pkg->length > 1 ? (1 << TWEA) : 0);
            inst.state_handler = state_read_data;
        } else {
            inst.state_handler = state_write_data;
            state_write_data(0x28); // Trigger first byte write
        }
    } else {
        inst.status = TWI_ERROR;
        inst.busy = 0;
        TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    }
}

static void state_write_data(uint8_t status) {
    if (status == 0x28) { // Data ACK
        if (inst.byte_count < inst.pkg->length) {
            TWDR = inst.pkg->buffer[inst.byte_count++];
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
        } else {
            TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
            inst.status = TWI_SUCCESS;
            inst.busy = 0;
        }
    } else {
        inst.status = TWI_ERROR;
        inst.busy = 0;
        TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    }
}

static void state_read_data(uint8_t status) {
    if (status == 0x50 || status == 0x58) { // Data ACK or NACK
        inst.pkg->buffer[inst.byte_count++] = TWDR;
        if (inst.byte_count < inst.pkg->length) {
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE) | (inst.byte_count < (inst.pkg->length - 1) ? (1 << TWEA) : 0);
        } else {
            TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
            inst.status = TWI_SUCCESS;
            inst.busy = 0;
        }
    }
}

// --- Public API ---

void twi_init(uint32_t speed) {
    TWSR = 0;
    TWBR = ((F_CPU / speed) - 16) / 2;
    TWCR = (1 << TWEN);
    inst.busy = 0;
}

twi_status_t twi_master_transfer(twi_package_t *pkg, uint8_t is_read) {
    if (inst.busy) return TWI_BUSY;
    
    inst.pkg = pkg;
    inst.is_read = is_read;
    inst.byte_count = 0;
    inst.busy = 1;
    inst.status = TWI_BUSY;
    inst.state_handler = state_start;
    
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);
    return TWI_SUCCESS;
}

ISR(TWI_vect) {
    if (inst.state_handler) {
        inst.state_handler(TWSR & 0xF8);
    }
}

twi_status_t twi_get_status(void) {
    return inst.status;
}
