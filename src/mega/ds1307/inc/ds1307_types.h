#ifndef DS1307_TYPES_H
#define DS1307_TYPES_H

#include <stdint.h>

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day_week;
    uint8_t day_month;
    uint8_t month;
    uint8_t year;
} ds1307_time_t;

#endif // DS1307_TYPES_H
