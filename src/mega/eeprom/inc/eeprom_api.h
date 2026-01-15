#ifndef EEPROM_API_H
#define EEPROM_API_H

#include "eeprom_types.h"

void eepromInit(void);
void eepromDriver(void);

void eepromWrite(uint16_t addr, const uint8_t *data, uint8_t size);
uint8_t eepromRead(uint16_t addr, uint8_t *data, uint8_t size);
uint8_t eepromIsBusy(void);

#endif // EEPROM_API_H
