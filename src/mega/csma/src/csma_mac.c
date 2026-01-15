#include "inc/csma_internal.h"
#include <stdlib.h>

// Optimized backoff calculator
uint16_t csmaCalcBackoff(uint8_t failure) {
    if (csma.isServer) return CSMA_DIFS;
    
    // Fixed bias if assigned an address
    if (!csma.isServer && csma.nodeAddr) {
        return CSMA_DIFS + (CSMA_BIT_DURATION * 8 * csma.nodeAddr);
    }
    
    // Binary exponential backoff
    if (failure) {
        // Double CW up to MAX
        uint16_t next_cw = (csma.cw + 1) << 1;
        csma.cw = (next_cw > CSMA_CW_MAX) ? CSMA_CW_MAX : (next_cw - 1);
    } else {
        // Shrink CW
        uint16_t next_cw = (csma.cw + 1) >> 1;
        csma.cw = (next_cw < CSMA_CW_MIN) ? CSMA_CW_MIN : (next_cw - 1);
    }
    
    // Return DIFS + random slot
    uint16_t slots = rand() % (csma.cw + 1);
    return CSMA_DIFS + (slots * CSMA_BIT_DURATION);
}
