#ifndef CSMA_API_H
#define CSMA_API_H

#include <stdint.h>
#include "csma_types.h"

// Lifecycle
void csmaInit(void);
void csmaDriver(void);
void csmaConfigureNode(uint8_t is_server, uint32_t activation_code);

// Communication API
typedef uint8_t (*csmaCallback_t)(uint8_t sa, uint8_t da, uint8_t len, uint8_t *data);
typedef void (*csmaSaveSerial_t)(uint8_t *frame_data);

void csmaSetOnHostRequest(csmaCallback_t cb);
void csmaSetOnClientResponse(csmaCallback_t cb);
void csmaRegisterSaveSerial(csmaSaveSerial_t cb);

uint8_t csmaPutData(uint8_t *buf, uint8_t len, uint8_t da, uint8_t type);
uint8_t csmaRequestRawFrame(uint8_t code, uint8_t *buffer, uint8_t da, uint8_t len, void (*state_cb)(uint8_t));

// Address Management
void    csmaSetNodeIp(uint8_t ip);
void    csmaSetNodeAddr(uint8_t addr);
uint8_t csmaGetNodeAddr(void);
uint8_t csmaGetMaxAddr(void);

// Utils
uint8_t csmaSendFreeFrame(void);
uint8_t csmaSendBlockFrame(void);
void    csmaClearTxBuffer(void);

// Result codes for csma_put_data
#define CSMA_SUCCESS    1
#define CSMA_ERROR      2
#define CSMA_BUSY       0

#endif // CSMA_API_H
