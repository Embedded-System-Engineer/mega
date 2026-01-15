#ifndef LCD_API_H
#define LCD_API_H

#include "lcd_types.h"

void lcdInit(void);
void lcdDriver(void);

void lcdClear(void);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdPrint(const char *str);
void lcdPrintAt(uint8_t row, uint8_t col, const char *str);

#endif // LCD_API_H
