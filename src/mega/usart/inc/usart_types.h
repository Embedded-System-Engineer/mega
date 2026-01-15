#ifndef USART_TYPES_H
#define USART_TYPES_H

#include <stdint.h>

typedef enum {
    USART_PORT0,
    USART_PORT1,
    USART_PORT2,
    USART_PORT3
} usart_port_t;

typedef struct {
    uint32_t baud;
    uint8_t  data_bits;
    uint8_t  stop_bits;
    uint8_t  parity;
} usart_config_t;

#endif // USART_TYPES_H
