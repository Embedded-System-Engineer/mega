#ifndef FIFO_TYPES_H
#define FIFO_TYPES_H

#include <stdint.h>

typedef enum {
    FIFO_OK,
    FIFO_ERR_NO_DAT,
    FIFO_ERR_BAD_OFFS,
    FIFO_NO_SPA
} fifo_status_t;

typedef struct {
    uint8_t  *buffer;
    uint16_t  capacity;
    uint16_t  read_idx;
    uint16_t  write_idx;
    uint16_t  free_size;
} fifo_t;

#endif // FIFO_TYPES_H
