#include "inc/csma_api.h"
#include "inc/csma_internal.h"
#include <string.h>

// Forward declarations of state handlers
static void stateIdle(void);
static void stateReceive(void);
static void stateSend(void);
static void stateAck(void);
static void stateBlocking(void);
static void stateAckwait(void);

static void mngIdle(void);
static void mngServerBroadcastRemove(void);
static void mngClientRemoveAddr(void);
static void mngClientRequestAddr(void);

void csmaInit(void) {
    memset(&csma, 0, sizeof(csma));
    csma.isServer = 1;
    csma.cw = CSMA_CW_MIN;
    csma.stateHandler = stateIdle;
    csma.mngHandler = mngIdle;
    csmaHwTimerInit();
}

void csmaConfigureNode(uint8_t is_server, uint32_t activation_code) {
    csma.isServer = is_server;
    csma.authCode = activation_code;
    srand(activation_code);
    
    // Assign proper management handlers based on role
    // This removes the "if (is_server)" from the periodic driver
    if (is_server) {
        csma.mngHandler = mngIdle;
    } else {
        csma.mngHandler = (csma.nodeAddr == 0) ? mngClientRemoveAddr : mngIdle;
    }
}

// --- Management State Handlers ---

static void mngIdle(void) {
    // Basic idle, can be changed by external requests
}

static void mngServerBroadcastRemove(void) {
    if (csmaRequestRawFrame((FRAME_TYPE_MNG << 4) | MNG_REM_ADDR, NULL, 0xFF, 0, NULL)) {
        csma.mngHandler = mngIdle;
    }
}

static void mngClientRemoveAddr(void) {
    uint8_t type = csma.isServer; 
    if (csmaRequestRawFrame((FRAME_TYPE_MNG << 4) | MNG_REM_ADDR, &type, 0x00, 1, NULL)) {
        csma.mngHandler = mngClientRequestAddr; 
    }
}

static void mngClientRequestAddr(void) {
    if (csma.nodeAddr != 0) {
        csma.mngHandler = mngIdle;
        return;
    }
    if (csmaRequestRawFrame((FRAME_TYPE_MNG << 4) | MNG_GET_ADDR, NULL, 0x00, 0, NULL)) {
        // Wait for server to assign (handled in parsing)
    }
}

// --- Main Loop Driver ---

void csmaDriver(void) {
    if (csma.nodeIp == 0 && !csma.isServer) return;

    if (csmaPhyHasError()) {
        csmaPhyRxByte();
        csmaResetTxContext(0);
        return;
    }

    if (csma.mngHandler) {
        csma.mngHandler();
    }
    
    if (csma.userRxState != 0) {
        csmaProcessUserCb();
    }
}

// --- Timer State Handlers (Common Logic) ---

void stateIdle(void) {}

void stateReceive(void) {
    csmaProcessParsing();
}

void stateSend(void) {
    csma.txByteCount = 0;
    csma.rxByteCount = 0;
    csma.rxIntent = RX_TARGET_MY_FRAME;
    csmaPhyTxByte(csma.txBuffer[0]);
}

void stateAck(void) {
    csma.txByteCount = 0;
    csma.rxByteCount = 0;
    csma.rxIntent = RX_TARGET_MY_ACK;
    csmaPhyTxByte(csma.ackBuffer[0]);
}

void stateBlocking(void) {
    if (csma.txRequested == 1) {
        csma.stateHandler = stateSend;
        csmaHwTimerStart(csmaCalcBackoff(1));
    } else if (csma.txRequested == 2) {
        csma.stateHandler = stateAckwait;
        csmaHwTimerStart(CSMA_ACKO_TIMEOUT);
    } else {
        csma.stateHandler = stateIdle;
    }
}

void stateAckwait(void) {
    if (csma.retryCount < COM_MAX_RETRY) {
        csma.retryCount++;
        csma.stateHandler = stateSend;
        csmaHwTimerStart(csmaCalcBackoff(1));
    } else {
        csmaResetTxContext(0);
        csma.stateHandler = stateReceive;
    }
}

// Required symbols for the timer ISR to call
void csmaDispatchState(void) {
    if (csma.stateHandler) {
        csma.stateHandler();
    }
}

uint8_t csmaPutData(uint8_t *buf, uint8_t len, uint8_t da, uint8_t type) {
    if (csma.nodeAddr == 0 && !csma.isServer) return CSMA_ERROR;
    uint8_t code = (FRAME_TYPE_DATA << 4) | (type & 0x0F);
    return csmaRequestRawFrame(code, buf, da, len, NULL);
}

uint8_t csmaRequestRawFrame(uint8_t code, uint8_t *buffer, uint8_t da, uint8_t len, void (*state_cb)(uint8_t)) {
    if (csma.txRequested || csma.stateHandler != stateIdle) return 0;
    
    csma.txRequested = 1;
    csma.onTxDone = state_cb;
    
    csma_frame_t *frame = (csma_frame_t *)csma.txBuffer;
    frame->type_subtype = code;
    frame->sa = csma.nodeAddr;
    frame->da = da;
    frame->auth_code = csma.authCode;
    frame->length = CSMA_HDR_SIZE + len + 1;
    
    if (len && buffer) {
        memcpy(frame->data, buffer, len);
    }
    
    frame->data[len] = csmaCrc8(csma.txBuffer, frame->length - 1);
    
    csma.stateHandler = stateSend;
    csmaHwTimerStart(csmaCalcBackoff(0));
    
    return 1;
}

void csmaSetOnHostRequest(csmaCallback_t cb)   { csma.onRequest = cb; }
void csmaSetOnClientResponse(csmaCallback_t cb) { csma.onResponse = cb; }
void csmaRegisterSaveSerial(csmaSaveSerial_t cb) { csma.onSaveSerial = cb; }

void csmaSetNodeIp(uint8_t ip)     { csma.nodeIp = ip; }
void csmaSetNodeAddr(uint8_t addr) { csma.nodeAddr = addr; }
uint8_t csmaGetNodeAddr(void)      { return csma.nodeAddr; }

void csmaProcessUserCb(void) {
    // We can further optimize this by mapping user_rx_state to specific callbacks if needed
    if (csma.userRxState == 1 && csma.onRequest) {
        csma.onRequest(0, 0, 0, csma.userPayload);
    } else if (csma.userRxState == 2 && csma.onResponse) {
        csma.onResponse(0, 0, 0, csma.userPayload);
    }
    csma.userRxState = 0;
}
