#include "../inc/lcd_menu_api.h"
#include "../../lcd/inc/lcd_api.h"
#include "../../keypad/inc/keypad_api.h"
#include <string.h>

typedef void (*lcd_menu_state_handler_t)(void);

typedef struct {
    const menueItem_t      *current_item;
    uint8_t                 is_open;
    uint8_t                 data_updated;
    lcd_menu_state_handler_t state_handler;
} lcd_menu_inst_t;

static lcd_menu_inst_t inst;

static void state_idle(void);
static void state_rendering(void);

// --- State Handlers ---

static void state_idle(void) {
    if (!inst.is_open) return;
    if (inst.data_updated) {
        inst.state_handler = state_rendering;
    }
}

static void state_rendering(void) {
    if (inst.current_item) {
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Menu:"); // Simplified
        lcd_set_cursor(1, 0);
        lcd_print(inst.current_item->menuLable);
    }
    inst.data_updated = 0;
    inst.state_handler = state_idle;
}

// --- Public API ---

void lcd_menu_init(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = state_idle;
}

void lcd_menu_driver(void) {
    if (inst.state_handler) inst.state_handler();
}

void lcd_menu_start(const menueItem_t *item) {
    inst.current_item = item;
    inst.is_open = 1;
    inst.data_updated = 1;
}

uint8_t lcd_menu_is_open(void) {
    return inst.is_open;
}
