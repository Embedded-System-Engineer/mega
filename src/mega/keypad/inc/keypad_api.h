#ifndef KEYPAD_API_H
#define KEYPAD_API_H

#include "keypad_types.h"

void keypadInit(void);
void keypadDriver(void);

void keypadRegisterCallback(uint8_t key_code, keypad_callback_t cb);

#endif // KEYPAD_API_H
