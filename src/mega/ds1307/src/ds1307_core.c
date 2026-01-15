#include "../inc/ds1307_api.h"
#include "../../twi/inc/twi_api.h"
#include "../../system/inc/system_api.h"
#include <string.h>

typedef void (*ds1307_state_handler_t)(void);

typedef struct {
    ds1307_time_t           current_time;
    ds1307_state_handler_t  state_handler;
    system_timer_t          timer;
    uint8_t                 data_buf[7];
} ds1307_inst_t;

static ds1307_inst_t inst;

static void state_wait_update(void);
static void state_reading(void);
static void state_process(void);

static void state_wait_update(void) {
    if (system_is_timeout(&inst.timer)) {
        uint8_t addr = 0x00;
        twi_package_t pkg = { .chip = 0xD0, .addr = &addr, .addr_length = 1, .buffer = inst.data_buf, .length = 7 };
        
        if (twi_master_transfer(&pkg, 1) == TWI_SUCCESS) {
            inst.state_handler = state_reading;
        }
    }
}

static void state_reading(void) {
    if (twi_get_status() == TWI_SUCCESS) {
        inst.state_handler = state_process;
    } else if (twi_get_status() == TWI_ERROR) {
        inst.state_handler = state_wait_update;
        system_set_timer_ms(&inst.timer, 1000);
    }
}

static void state_process(void) {
    // Process inst.data_buf and convert BCD to Dec
    inst.current_time.sec = ((inst.data_buf[0] >> 4) * 10) + (inst.data_buf[0] & 0x0F);
    // ... etc ...
    
    inst.state_handler = state_wait_update;
    system_set_timer_ms(&inst.timer, 1000);
}

void ds1307Init(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = state_wait_update;
    system_set_timer_ms(&inst.timer, 1000);
}

void ds1307Driver(void) {
    if (inst.state_handler) {
        inst.state_handler();
    }
}
