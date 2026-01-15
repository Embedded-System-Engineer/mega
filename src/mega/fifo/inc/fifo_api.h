#ifndef FIFO_API_H
#define FIFO_API_H

#include "fifo_types.h"

void fifoInit(fifo_t *fifo, uint8_t *buffer, uint16_t capacity);

fifo_status_t fifoWrite(fifo_t *fifo, const uint8_t *data, uint16_t size);
fifo_status_t fifoRead(fifo_t *fifo, uint8_t *data, uint16_t size);
fifo_status_t fifoPeek(fifo_t *fifo, uint8_t *data, uint16_t offset, uint16_t size);

uint16_t fifoGetFree(fifo_t *fifo);
uint16_t fifoGetUsed(fifo_t *fifo);
uint8_t  fifoIsEmpty(fifo_t *fifo);
uint8_t  fifoIsFull(fifo_t *fifo);

#endif // FIFO_API_H
