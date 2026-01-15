#ifndef DS1307_API_H
#define DS1307_API_H

#include "ds1307_types.h"

void ds1307Init(void);
void ds1307Driver(void);

void ds1307SetTime(const ds1307_time_t *time);
void ds1307GetTime(ds1307_time_t *time);

#endif // DS1307_API_H
