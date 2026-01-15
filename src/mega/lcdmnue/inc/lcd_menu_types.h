#ifndef LCD_MENU_TYPES_H
#define LCD_MENU_TYPES_H

#include <stdint.h>

typedef struct menueItem_s menueItem_t;
typedef uint8_t (*pFuncMenueCallBack_t)(void);

struct menueItem_s {
    const menueItem_t *menuNext;
    const menueItem_t *menuPre;
    const menueItem_t *menuParent;
    const menueItem_t *menuChild;
    pFuncMenueCallBack_t menuCallback;
    const char *menuLable;
};

#endif // LCD_MENU_TYPES_H
