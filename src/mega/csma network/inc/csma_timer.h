#ifndef CSMA_TIMER_H
#define CSMA_TIMER_H

#include "csma_types.h"

typedef enum {
    CSMA_TIMER_ACK = 0,
    CSMA_TIMER_BACKOFF,
    CSMA_TIMER_INTERFRAME,
    CSMA_TIMER_GENERAL
} csma_timer_type_t;

typedef struct {
    uint32_t start_time;
    uint32_t duration;
    bool active;
    csma_timer_callback_t callback;
} csma_timer_t;

csma_status_t csma_timer_init(void);
void csma_timer_process(void);
csma_status_t csma_timer_start(csma_timer_type_t type, uint32_t duration_us);
csma_status_t csma_timer_stop(csma_timer_type_t type);
bool csma_timer_is_expired(csma_timer_type_t type);
uint32_t csma_timer_elapsed(csma_timer_type_t type);
void csma_timer_register_callback(csma_timer_type_t type, csma_timer_callback_t callback);

#endif