#include "../inc/mega.h"

int main(void)
{
    // Hardware & System Initialization
    appBoot();
    system_init();
    // Module Initializations
    gpio_init(); // If needed
    appInit();

    system_start(); // Starts interrupts

    while (1)
    {
        scheduler_dispatch();
        appMain();
    }

    return 0;
}
