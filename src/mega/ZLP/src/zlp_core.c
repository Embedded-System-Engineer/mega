#include "../inc/zlp_api.h"
#include "../../usart/inc/usart_api.h"
#include "../../utility/inc/utility_api.h"
#include <avr/pgmspace.h>
#include <string.h>

typedef void (*zlp_state_handler_t)(void);

typedef struct {
    uint8_t            tx_buffer[64];
    uint8_t            tx_len;
    uint8_t            tx_idx;
    zlp_status_t       status;
    zlp_state_handler_t state_handler;
} zlp_inst_t;

static zlp_inst_t inst;

static void state_idle(void);
static void state_transmitting(void);

// --- State Handlers ---

static void state_idle(void) {
    // Waiting for print command
}

static void state_transmitting(void) {
    if (inst.tx_idx < inst.tx_len) {
        if (usart_send_byte(USART_PORT0, inst.tx_buffer[inst.tx_idx]) == 0) {
            inst.tx_idx++;
        }
    } else {
        inst.status = ZLP_IDLE;
        inst.state_handler = state_idle;
    }
}

// --- Public API ---

void zlpInit(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = state_idle;
    inst.status = ZLP_IDLE;
}

void zlpDriver(void) {
    if (inst.state_handler) inst.state_handler();
}

void zlpSendData(const uint8_t *data, uint8_t len) {
    if (inst.status != ZLP_IDLE) return;
    if (len > sizeof(inst.tx_buffer)) len = sizeof(inst.tx_buffer);
    
    memcpy(inst.tx_buffer, data, len);
    inst.tx_len = len;
    inst.tx_idx = 0;
    inst.status = ZLP_BUSY;
    inst.state_handler = state_transmitting;
}

void zlpPrintLabel(uint8_t copies) {
    uint8_t cmd[10];
    uint8_t len = u8_to_ascii(cmd, copies);
    // Simplified Zebra print command: P<copies>\r\n
    uint8_t final_cmd[16] = "P";
    strcat((char*)final_cmd, (char*)cmd);
    strcat((char*)final_cmd, "\r\n");
    zlpSendData(final_cmd, strlen((char*)final_cmd));
}

uint8_t zlpIsBusy(void) {
    return inst.status != ZLP_IDLE;
}
