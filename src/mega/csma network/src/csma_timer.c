#include "csma_timer.h"
#include <stddef.h>

static csma_timer_t timers[4];
static uint32_t system_time = 0;

csma_status_t csma_timer_init(void)
{
    for (int i = 0; i < 4; i++) {
        timers[i].active = false;
        timers[i].callback = NULL;
    }
    system_time = 0;
    return CSMA_STATUS_OK;
}

void csma_timer_process(void)
{
    system_time++;
    
    for (int i = 0; i < 4; i++) {
        if (timers[i].active && (system_time - timers[i].start_time >= timers[i].duration)) {
            timers[i].active = false;
            if (timers[i].callback != NULL) {
                timers[i].callback();
            }
        }
    }
}

csma_status_t csma_timer_start(csma_timer_type_t type, uint32_t duration_us)
{
    if (type >= 4) return CSMA_STATUS_INVALID_PARAM;
    
    timers[type].start_time = system_time;
    timers[type].duration = duration_us;
    timers[type].active = true;
    
    return CSMA_STATUS_OK;
}

csma_status_t csma_timer_stop(csma_timer_type_t type)
{
    if (type >= 4) return CSMA_STATUS_INVALID_PARAM;
    
    timers[type].active = false;
    return CSMA_STATUS_OK;
}

bool csma_timer_is_expired(csma_timer_type_t type)
{
    if (type >= 4) return true;
    
    return timers[type].active && 
           (system_time - timers[type].start_time >= timers[type].duration);
}

uint32_t csma_timer_elapsed(csma_timer_type_t type)
{
    if (type >= 4 || !timers[type].active) return 0;
    
    return system_time - timers[type].start_time;
}

void csma_timer_register_callback(csma_timer_type_t type, csma_timer_callback_t callback)
{
    if (type < 4) {
        timers[type].callback = callback;
    }
}