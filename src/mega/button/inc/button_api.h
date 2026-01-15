#ifndef BUTTON_API_H
#define BUTTON_API_H

#include "button_types.h"

void buttonInit(void);
void buttonScan(void);
void buttonDriver(void);

void buttonRegisterEvent(button_callback_t cb, uint8_t index);
void buttonAssignConstantEvents(const button_code_t *events);

#endif // BUTTON_API_H
