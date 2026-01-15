#ifndef EXEPROM_API_H
#define EXEPROM_API_H

#include "exeprom_types.h"

void exepromInit(void);
void exepromDriver(void);

void exepromRead(uint16_t addr, uint8_t *buf, uint8_t len);
void exepromWrite(uint16_t addr, uint8_t *buf, uint8_t len);
uint8_t exepromIsReady(void);

#endif // EXEPROM_API_H
