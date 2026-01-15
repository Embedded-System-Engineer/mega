#include "../inc/scheduler_api.h"
#include "../inc/system_api.h"
#include <string.h>

static task_t tasks[MAX_TASKS];
static uint8_t task_count = 0;

void schedulerInit(void) {
    memset(tasks, 0, sizeof(tasks));
    task_count = 0;
}

int8_t schedulerAddTask(task_func_t func, void *arg, uint32_t period_ms) {
    if (task_count >= MAX_TASKS) return -1;
    
    tasks[task_count].func = func;
    tasks[task_count].arg = arg;
    tasks[task_count].period_ms = period_ms;
    tasks[task_count].last_run_ms = 0;
    tasks[task_count].enabled = 1;
    task_count++;
    
    return task_count - 1;
}

void schedulerDispatch(void) {
    uint32_t current_time = systemMillis();
    
    for (uint8_t i = 0; i < task_count; i++) {
        if (!tasks[i].enabled) continue;
        
        if ((current_time - tasks[i].last_run_ms) >= tasks[i].period_ms) {
            tasks[i].func(tasks[i].arg);
            tasks[i].last_run_ms = current_time;
        }
    }
}
