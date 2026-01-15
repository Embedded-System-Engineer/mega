#ifndef LCD_TYPES_H
#define LCD_TYPES_H

#include <stdint.h>

#ifndef LCD_COLS
#define LCD_COLS 16
#endif

#ifndef LCD_ROWS
#define LCD_ROWS 2
#endif

typedef enum {
    LCD_SUCCESS,
    LCD_ERROR,
    LCD_BUSY
} lcd_status_t;

#endif // LCD_TYPES_H
