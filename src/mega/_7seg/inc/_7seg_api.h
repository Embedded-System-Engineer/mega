#ifndef _7SEG_API_H
#define _7SEG_API_H

#include "_7seg_types.h"

// Lifecycle
void _7segInit(void);
void _7segScan(void);

// Instance Management
_7seg_instance_t* _7segCreateDisplay(const uint8_t *digit_pins, uint8_t max_digit, uint8_t type);
void              _7segRemoveDisplay(_7seg_instance_t *display);

// Functional API
void _7segWriteNumber(_7seg_instance_t *display, uint32_t value, uint8_t justify);
void _7segWriteString(_7seg_instance_t *display, const char *string, uint8_t justify);
void _7segWriteChar(_7seg_instance_t *display, uint8_t value);
void _7segClear(_7seg_instance_t *display);

// Justification constants
#define _7SEG_LEFT   0
#define _7SEG_CENTER 1
#define _7SEG_RIGHT  2

#endif // _7SEG_API_H
