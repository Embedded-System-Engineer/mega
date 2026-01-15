#ifndef CSMA_INTERNAL_H
#define CSMA_INTERNAL_H

#include "csma_types.h"

// --- Private Global State ---
// Grouped into a struct for encapsulation and potential multi-instance support
// --- State Handler types ---
typedef void (*csma_state_handler_t)(void);

typedef struct {
    // Protocol timing and states (Volatile for ISR safety)
    volatile csma_state_handler_t stateHandler;
    volatile rx_intent_t          rxIntent;
    volatile uint8_t              rxByteCount;
    volatile uint8_t              txByteCount;
    
    // Node configuration
    uint8_t  nodeAddr;
    uint8_t  nodeIp;
    uint32_t authCode;
    uint8_t  isServer;
    
    // Contention Window & Retries
    uint16_t cw;
    uint8_t  retryCount;
    uint8_t  collisionDetected;
    
    // Buffers
    uint8_t  txBuffer[CSMA_MAX_FRAME_LEN];
    uint8_t  rxBuffer[CSMA_MAX_FRAME_LEN];
    uint8_t  ackBuffer[CSMA_HDR_SIZE + 1];
    uint8_t  userPayload[COM_PAYLOAD_SIZE];
    
    // Logic flags and state machines
    uint8_t               txRequested;     // 0: None, 1: Frame, 2: Ack Wait
    csma_state_handler_t  mngHandler;      // Management state machine
    uint8_t               userTxState;    // User put_data state machine
    uint8_t               userRxState;    // User callback flag
    
    // Callbacks
    csmaCallback_t     onRequest;
    csmaCallback_t     onResponse;
    csmaSaveSerial_t   onSaveSerial;
    void (*onTxDone)(uint8_t);
} csma_instance_t;

extern csma_instance_t csma;

// --- Internal Helper Functions ---
void    csmaHwTimerInit(void);
void    csmaHwTimerStart(uint16_t time_us);
void    csmaHwTimerStop(void);

void    csmaPhyTxByte(uint8_t b);
uint8_t csmaPhyRxByte(void);
uint8_t csmaPhyHasError(void);

uint8_t  csmaCrc8(const uint8_t *data, uint8_t len);
uint16_t csmaCalcBackoff(uint8_t failure);
void     csmaResetTxContext(uint8_t status);

void csmaProcessParsing(void);
void csmaProcessUserCb(void);
void csmaDispatchState(void);

// State Handlers
void stateIdle(void);
void stateReceive(void);
void stateSend(void);
void stateAck(void);
void stateBlocking(void);
void stateAckwait(void);

#endif // CSMA_INTERNAL_H
