#ifndef LCD_MENU_API_H
#define LCD_MENU_API_H

#include "lcd_menu_types.h"

void lcd_menu_init(void);
void lcd_menu_driver(void);
void lcd_menu_start(const menueItem_t *item);
uint8_t lcd_menu_is_open(void);

#endif // LCD_MENU_API_H
