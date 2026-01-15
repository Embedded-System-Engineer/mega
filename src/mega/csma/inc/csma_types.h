#ifndef CSMA_TYPES_H
#define CSMA_TYPES_H

#include <stdint.h>
#include "csma_config.h"

// Frame types (Top 4 bits of first byte)
typedef enum {
    FRAME_TYPE_SERIAL = 0,
    FRAME_TYPE_MNG    = 1,
    FRAME_TYPE_DATA   = 2,
    FRAME_TYPE_CTRL   = 3
} fr_type_t;

// Control frame subtypes (Bottom 4 bits)
typedef enum {
    CTRL_NACK  = 10,
    CTRL_ACK   = 11,
    CTRL_BLOCK = 12,
    CTRL_FREE  = 13
} fr_ctrl_subtype_t;

// Management frame subtypes
typedef enum {
    MNG_GET_ADDR     = 10,
    MNG_ASSIGN_ADDR  = 11,
    MNG_REM_ADDR     = 12,
    MNG_SRV_CONF_REM = 13
} fr_mng_subtype_t;

// Internal timer states
typedef enum {
    CSMA_STATE_IDLE     = 0,
    CSMA_STATE_RECEIVE  = 1,
    CSMA_STATE_SEND     = 2,
    CSMA_STATE_ACK      = 3,
    CSMA_STATE_BLOCKING = 4,
    CSMA_STATE_ACKWAIT  = 5
} csma_state_t;

// Receiver intent
typedef enum {
    RX_TARGET_MY_FRAME = 0,
    RX_TARGET_MY_ACK   = 1,
    RX_TARGET_OTHER    = 2
} rx_intent_t;

// Structured Frame Header
typedef struct {
    uint8_t  type_subtype; // [7:4] Type, [3:0] Subtype
    uint8_t  sa;           // Source Address
    uint8_t  da;           // Destination Address
    union {
        uint32_t auth_code; // Activation code / Authentication
        uint8_t  auth_bytes[4];
    };
    uint8_t  length;       // Total frame length (including header and CRC)
    uint8_t  data[];       // Flexible array member for payload + CRC
} __attribute__((packed)) csma_frame_t;

#endif // CSMA_TYPES_H
