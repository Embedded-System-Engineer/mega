#ifndef SYSTEM_API_H
#define SYSTEM_API_H

#include "system_types.h"
#include "scheduler_api.h"

void systemInit(void);
void systemStart(void);
void systemStop(void);

millis_t systemMillis(void);
micros_t systemMicros(void);
time_t   systemTime(void);

void systemSetTimerMs(system_timer_t *timer, millis_t period);
uint8_t systemIsTimeout(system_timer_t *timer);

#endif // SYSTEM_API_H
