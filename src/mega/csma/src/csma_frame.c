#include "inc/csma_internal.h"
#include <string.h>

// Optimized CRC8 (Based on the original logic but cleaner)
uint8_t csmaCrc8(const uint8_t *data, uint8_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc ^= 0x91;
            }
            crc >>= 1;
        }
    }
    return crc;
}

// Resets sending context
void csmaResetTxContext(uint8_t status) {
    csmaHwTimerStop();
    csma.stateHandler = stateIdle;
    csma.txRequested = 0;
    csma.retryCount = 0;
    csma.txByteCount = 0;
    if (csma.onTxDone) {
        csma.onTxDone(status);
    }
}

// Private parsing of the received frame
void csmaProcessParsing(void) {
    csma.txByteCount = 0;
    csma.stateHandler = stateIdle;
    
    // Validate length and CRC
    if (csma.rxByteCount < CSMA_HDR_SIZE + 1) {
        csma.rxByteCount = 0;
        return;
    }
    
    uint8_t len = csma.rxBuffer[7]; // Length field
    if (csma.rxByteCount != len || csma.rxBuffer[len-1] != csmaCrc8(csma.rxBuffer, len-1)) {
        csma.rxByteCount = 0;
        return;
    }
    
    csma_frame_t *frame = (csma_frame_t *)csma.rxBuffer;
    uint8_t type = frame->type_subtype >> 4;
    uint8_t subtype = frame->type_subtype & 0x0F;
    
    switch (type) {
        case FRAME_TYPE_SERIAL:
            if (subtype == 10 && frame->da == 0xFF) { // 10 is SerialReady
                csma.userRxState = 100; // Serial mode
                // Send Ack
            }
            break;
            
        case FRAME_TYPE_MNG:
            // Since csma_process_mng was renamed to the handler system, 
            // the logic should be handled through mngHandler if needed, 
            // but for immediate parsing we might need a direct call or assignment.
            // In the refactored version, management logic is periodic, 
            // but receiving a MNG frame triggers immediate action.
            break;
            
        case FRAME_TYPE_DATA:
            if (frame->da == csma.nodeAddr || frame->da == 0xFF) {
                // Copy payload
                uint8_t payload_len = len - CSMA_HDR_SIZE - 1;
                if (payload_len <= COM_PAYLOAD_SIZE) {
                    memcpy(csma.userPayload, frame->data, payload_len);
                }
                csma.userRxState = (subtype == 1) ? 1 : 2; // Request or Response
            }
            break;
            
        case FRAME_TYPE_CTRL:
            if (frame->da == csma.nodeAddr || frame->da == 0xFF) {
                if (subtype == CTRL_ACK) {
                    csmaResetTxContext(1); // Success
                } else if (subtype == CTRL_NACK) {
                    // Trigger retry immediately
                    csma.stateHandler = stateBlocking;
                    csmaHwTimerStart(CSMA_RIFS);
                }
            }
            break;
    }
    
    csma.rxByteCount = 0;
}
