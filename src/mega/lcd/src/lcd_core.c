#include "../inc/lcd_api.h"
#include "../../gpio/inc/gpio_api.h"
#include "../../system/inc/system_api.h"
#include <util/delay.h>
#include <string.h>

typedef void (*lcd_state_handler_t)(void);

typedef struct {
    uint8_t            buffer[LCD_ROWS * LCD_COLS];
    uint8_t            buf_idx;
    uint8_t            option;
    lcd_state_handler_t state_handler;
    system_timer_t     timer;
    uint8_t            init_step;
} lcd_inst_t;

static lcd_inst_t inst;

static void stateInit(void);
static void stateIdle(void);
static void stateUpdating(void);

// Helper for 4-bit pulse
static void lcdPulse(void) {
    gpioWrite(LCD_EN, 1);
    _delay_us(1);
    gpioWrite(LCD_EN, 0);
    _delay_us(1);
}

static void lcdSendNibble(uint8_t nibble) {
    gpioWrite(LCD_D4, (nibble >> 0) & 1);
    gpioWrite(LCD_D5, (nibble >> 1) & 1);
    gpioWrite(LCD_D6, (nibble >> 2) & 1);
    gpioWrite(LCD_D7, (nibble >> 3) & 1);
    lcdPulse();
}

static void lcdSend(uint8_t data, uint8_t rs) {
    gpioWrite(LCD_RS, rs);
    lcdSendNibble(data >> 4);
    lcdSendNibble(data & 0x0F);
    _delay_us(50);
}

// --- State Handlers ---

static void stateInit(void) {
    switch (inst.init_step) {
        case 0:
            // Startup delay
            if (systemIsTimeout(&inst.timer)) {
                lcdSendNibble(0x03);
                systemSetTimerMs(&inst.timer, 5);
                inst.init_step++;
            }
            break;
        case 1:
            if (systemIsTimeout(&inst.timer)) {
                lcdSendNibble(0x03);
                systemSetTimerMs(&inst.timer, 1);
                inst.init_step++;
            }
            break;
        case 2:
            if (systemIsTimeout(&inst.timer)) {
                lcdSendNibble(0x03);
                lcdSendNibble(0x02); // 4-bit mode
                lcdSend(0x28, 0); // 2 lines, 5x8
                lcdSend(0x0C, 0); // Display ON
                lcdSend(0x01, 0); // Clear
                _delay_ms(2);
                lcdSend(0x06, 0); // Entry mode
                inst.state_handler = stateIdle;
            }
            break;
    }
}

static void stateIdle(void) {
    // Wait for buffer updates or commands
}

static void stateUpdating(void) {
    if (inst.buf_idx < (LCD_ROWS * LCD_COLS)) {
        if (inst.buf_idx == 0) lcdSend(0x80, 0);
        if (inst.buf_idx == LCD_COLS) lcdSend(0xC0, 0);
        
        lcdSend(inst.buffer[inst.buf_idx++], 1);
    } else {
        inst.state_handler = stateIdle;
    }
}

// --- Public API ---

void lcdInit(void) {
    memset(&inst, 0, sizeof(inst));
    inst.state_handler = stateInit;
    inst.init_step = 0;
    systemSetTimerMs(&inst.timer, 20);
    
    // Pin init
    gpioSetMode(LCD_RS, GPIO_MODE_OUTPUT);
    gpioSetMode(LCD_EN, GPIO_MODE_OUTPUT);
    gpioSetMode(LCD_D4, GPIO_MODE_OUTPUT);
    gpioSetMode(LCD_D5, GPIO_MODE_OUTPUT);
    gpioSetMode(LCD_D6, GPIO_MODE_OUTPUT);
    gpioSetMode(LCD_D7, GPIO_MODE_OUTPUT);
}

void lcdDriver(void) {
    if (inst.state_handler) inst.state_handler();
}

void lcdPrint(const char *str) {
    uint8_t len = strlen(str);
    if (len > (LCD_ROWS * LCD_COLS)) len = LCD_ROWS * LCD_COLS;
    memcpy(inst.buffer, str, len);
    inst.buf_idx = 0;
    inst.state_handler = stateUpdating;
}

void lcdClear(void) {
    memset(inst.buffer, ' ', sizeof(inst.buffer));
    lcdSend(0x01, 0);
    _delay_ms(2);
}

void lcdSetCursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcdSend(addr, 0);
}

void lcdPrintAt(uint8_t row, uint8_t col, const char *str) {
    lcdSetCursor(row, col);
    while (*str) {
        lcdSend(*str++, 1);
    }
}
