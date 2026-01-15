#ifndef GPIO_API_H
#define GPIO_API_H

#include "gpio_types.h"

void gpioSetMode(gpio_t pin, gpio_mode_t mode);
void gpioWrite(gpio_t pin, gpio_state_t state);
gpio_state_t gpioRead(gpio_t pin);

#endif // GPIO_API_H
