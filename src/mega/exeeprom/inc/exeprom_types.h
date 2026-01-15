#ifndef EXEPROM_TYPES_H
#define EXEPROM_TYPES_H

#include <stdint.h>

typedef enum {
    EXEPROM_IDLE,
    EXEPROM_READING,
    EXEPROM_COMPARING,
    EXEPROM_WRITING,
    EXEPROM_ERROR
} exeprom_status_t;

#endif // EXEPROM_TYPES_H
