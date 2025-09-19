#ifndef CSMA_CONFIG_H
#define CSMA_CONFIG_H

#define CSMA_DEFAULT_MAX_RETRY_COUNT       5
#define CSMA_DEFAULT_MAX_PAYLOAD_SIZE      32
#define CSMA_DEFAULT_ACK_TIMEOUT_MS        100
#define CSMA_DEFAULT_BACKOFF_MIN_MS        2
#define CSMA_DEFAULT_BACKOFF_MAX_MS        100
#define CSMA_DEFAULT_CW_MIN                31
#define CSMA_DEFAULT_CW_MAX                1023
#define CSMA_DEFAULT_BAUD_RATE             19200

#define CSMA_MAX_FRAME_SIZE                64
#define CSMA_ACK_FRAME_SIZE                8
#define CSMA_FRAME_HEADER_SIZE             8

#define CSMA_BIT_TIME(baudrate)           (1000000UL / (baudrate))
#define CSMA_BYTE_TIME(baudrate)          (10 * CSMA_BIT_TIME(baudrate))
#define CSMA_SIFS_TIME(baudrate)          (2 * CSMA_BYTE_TIME(baudrate))
#define CSMA_DIFS_TIME(baudrate)          (4 * CSMA_BYTE_TIME(baudrate))

#define CSMA_TX_BUFFER_SIZE               128
#define CSMA_RX_BUFFER_SIZE               128
#define CSMA_QUEUE_SIZE                   10

#define CSMA_BROADCAST_ADDRESS            0xFF
#define CSMA_SERVER_ADDRESS               0x00

#define CSMA_SLOT_TIME_US                 52
#define CSMA_ACK_TIMEOUT_US               625

#endif