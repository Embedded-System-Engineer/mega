#ifndef CSMA_CONFIG_H
#define CSMA_CONFIG_H

#include "../../../inc/mega.h"

// Hardware Configuration - Selection of UART
#if defined(USART1_ENABLED)
    #define CSMA_UART_CH            1
    #define CSMA_RIFS               USART1_BYTE_DURATION
    #define CSMA_BIT_DURATION       USART1_BIT_DURATION
#else
    #define CSMA_UART_CH            0
    #define CSMA_RIFS               USART0_BYTE_DURATION
    #define CSMA_BIT_DURATION       USART0_BIT_DURATION
#endif

// Timing Constants (in multiples of RIFS)
#define CSMA_SIFS               CSMA_RIFS
#define CSMA_DIFS               (2UL * CSMA_RIFS)
#define CSMA_ACKO_TIMEOUT       (12UL * CSMA_RIFS)
#define CSMA_BLOCK_TIME         (STATION_BLOCK_TIME * CSMA_RIFS)

// Contention Window Boundaries
#define CSMA_CW_MIN             31
#define CSMA_CW_MAX             1023

// Protocol Parameters
#ifndef COM_MAX_RETRY
    #define COM_MAX_RETRY       10
#endif

#ifndef COM_PAYLOAD_SIZE
    #define COM_PAYLOAD_SIZE    10
#endif

#ifndef STATION_BLOCK_TIME
    #define STATION_BLOCK_TIME  50
#endif

// Buffer Sizes
#define CSMA_HDR_SIZE           8  // Standard header size
#define CSMA_MAX_FRAME_LEN      (CSMA_HDR_SIZE + COM_PAYLOAD_SIZE + 1) // +1 for CRC

#endif // CSMA_CONFIG_H
