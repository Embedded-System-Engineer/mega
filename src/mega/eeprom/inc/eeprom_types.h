#ifndef EEPROM_TYPES_H
#define EEPROM_TYPES_H

#include <stdint.h>

typedef enum {
    EEPROM_IDLE,
    EEPROM_READING,
    EEPROM_WRITING,
    EEPROM_BUSY
} eeprom_state_t;

#endif // EEPROM_TYPES_H
