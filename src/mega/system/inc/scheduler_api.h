#ifndef SCHEDULER_API_H
#define SCHEDULER_API_H

#include "scheduler_types.h"

void schedulerInit(void);
int8_t schedulerAddTask(task_func_t func, void *arg, uint32_t period_ms);
void schedulerRun(void);
void schedulerDispatch(void); // Call this in main loop

#endif // SCHEDULER_API_H
