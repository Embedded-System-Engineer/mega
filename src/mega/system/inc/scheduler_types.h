#ifndef SCHEDULER_TYPES_H
#define SCHEDULER_TYPES_H

#include <stdint.h>

typedef void (*task_func_t)(void *arg);

typedef struct {
    task_func_t func;
    void       *arg;
    uint32_t    period_ms;
    uint32_t    last_run_ms;
    uint8_t     enabled;
} task_t;

#ifndef MAX_TASKS
#define MAX_TASKS 16
#endif

#endif // SCHEDULER_TYPES_H
