#ifndef TWI_TYPES_H
#define TWI_TYPES_H

#include <stdint.h>

typedef enum {
    TWI_SUCCESS,
    TWI_BUSY,
    TWI_ERROR,
    TWI_TIMEOUT
} twi_status_t;

typedef struct {
    uint8_t  chip;
    uint8_t *addr;
    uint8_t  addr_length;
    uint8_t *buffer;
    uint16_t length;
} twi_package_t;

#endif // TWI_TYPES_H
