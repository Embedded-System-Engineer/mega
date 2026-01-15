#include "../inc/fifo_api.h"
#include <string.h>

void fifo_init(fifo_t *fifo, uint8_t *buffer, uint16_t capacity) {
    fifo->buffer = buffer;
    fifo->capacity = capacity;
    fifo->read_idx = 0;
    fifo->write_idx = 0;
    fifo->free_size = capacity;
}

fifo_status_t fifo_write(fifo_t *fifo, const uint8_t *data, uint16_t size) {
    if (fifo->free_size < size) return FIFO_NO_SPA;
    
    uint16_t first_part = fifo->capacity - fifo->write_idx;
    if (size <= first_part) {
        memcpy(&fifo->buffer[fifo->write_idx], data, size);
        fifo->write_idx = (fifo->write_idx + size) % fifo->capacity;
    } else {
        memcpy(&fifo->buffer[fifo->write_idx], data, first_part);
        memcpy(fifo->buffer, &data[first_part], size - first_part);
        fifo->write_idx = size - first_part;
    }
    
    fifo->free_size -= size;
    return FIFO_OK;
}

fifo_status_t fifo_read(fifo_t *fifo, uint8_t *data, uint16_t size) {
    if (fifo_get_used(fifo) < size) return FIFO_ERR_NO_DAT;
    
    uint16_t first_part = fifo->capacity - fifo->read_idx;
    if (size <= first_part) {
        if (data) memcpy(data, &fifo->buffer[fifo->read_idx], size);
        fifo->read_idx = (fifo->read_idx + size) % fifo->capacity;
    } else {
        if (data) {
            memcpy(data, &fifo->buffer[fifo->read_idx], first_part);
            memcpy(&data[first_part], fifo->buffer, size - first_part);
        }
        fifo->read_idx = size - first_part;
    }
    
    fifo->free_size += size;
    return FIFO_OK;
}

uint16_t fifo_get_free(fifo_t *fifo) { return fifo->free_size; }
uint16_t fifo_get_used(fifo_t *fifo) { return fifo->capacity - fifo->free_size; }
uint8_t  fifo_is_empty(fifo_t *fifo) { return (fifo->free_size == fifo->capacity); }
uint8_t  fifo_is_full(fifo_t *fifo)  { return (fifo->free_size == 0); }

fifo_status_t fifo_peek(fifo_t *fifo, uint8_t *data, uint16_t size) {
    if (fifo_get_used(fifo) < size) return FIFO_ERR_NO_DAT;
    
    uint16_t first_part = fifo->capacity - fifo->read_idx;
    if (size <= first_part) {
        memcpy(data, &fifo->buffer[fifo->read_idx], size);
    } else {
        memcpy(data, &fifo->buffer[fifo->read_idx], first_part);
        memcpy(&data[first_part], fifo->buffer, size - first_part);
    }
    return FIFO_OK;
}
