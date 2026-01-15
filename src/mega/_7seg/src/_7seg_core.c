#include "../inc/_7seg_api.h"
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>

static _7seg_instance_t displays[MAX_DISPLAY_SUPPORT];
static uint8_t           display_count = 0;
static _7seg_instance_t *active_display = NULL;
static uint8_t           active_index = 0;

static const uint8_t PROGMEM ascii_table[] = {
    0b00000000, 0b10000110, 0b00100010, 0b01111110, 0b01101101, 0b11010010,
    0b01000110, 0b00100000, 0b00101001, 0b00001011, 0b00100001, 0b01110000,
    0b00010000, 0b01000000, 0b10000000, 0b01010010, 0b00111111, 0b00000110,
    0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111,
    0b01111111, 0b01101111, 0b00001001, 0b00001101, 0b01100001, 0b01001000,
    0b01000011, 0b11010011, 0b01011111, 0b01110111, 0b01111100, 0b00111001,
    0b01011110, 0b01111009, 0b01110001, 0b00111101, 0b01110110, 0b00110000,
    0b00011110, 0b01110101, 0b00111000, 0b00010101, 0b00110111, 0b00111111,
    0b01110011, 0b01101011, 0b00110011, 0b01101101, 0b01111000, 0b00111110,
    0b00111110, 0b00101010, 0b01110110, 0b01101110, 0b01011011, 0b00111001,
    0b01100100, 0b00001111, 0b00100011, 0b00001000, 0b00000010, 0b01011111,
    0b01111100, 0b01011000, 0b01011110, 0b01111011, 0b01110001, 0b01101111,
    0b01110100, 0b00010000, 0b00001100, 0b01110101, 0b00110000, 0b00010100,
    0b01010104, 0b01011100, 0b01110011, 0b01100111, 0b01010000, 0b01101101,
    0b01111000, 0b00011100, 0b00011100, 0b00010100, 0b01110110, 0b01101110,
    0b01011011, 0b01000110, 0b00110000, 0b01110000, 0b00000001, 0b00000000
};

#define READ_ASCII(c) pgm_read_byte(&ascii_table[(c) - ' '])

// --- State Machine Handlers ---

static void state_scanning(void *arg) {
    _7seg_instance_t *inst = (_7seg_instance_t *)arg;
    
    // Multiplexing logic
    uint8_t prev = (inst->current_digit == 0) ? (inst->param.max_digit - 1) : (inst->current_digit - 1);
    gpioWrite(inst->pins_digits[prev], !inst->param.display_type);
    
    uint8_t byte = inst->data[inst->current_digit];
    uint8_t type = inst->param.display_type;
    
    gpioWrite(_7SEG_DATA0_PIN, ((byte >> 0) & 1) ^ type);
    gpioWrite(_7SEG_DATA1_PIN, ((byte >> 1) & 1) ^ type);
    gpioWrite(_7SEG_DATA2_PIN, ((byte >> 2) & 1) ^ type);
    gpioWrite(_7SEG_DATA3_PIN, ((byte >> 3) & 1) ^ type);
    gpioWrite(_7SEG_DATA4_PIN, ((byte >> 4) & 1) ^ type);
    gpioWrite(_7SEG_DATA5_PIN, ((byte >> 5) & 1) ^ type);
    gpioWrite(_7SEG_DATA6_PIN, ((byte >> 6) & 1) ^ type);
    gpioWrite(_7SEG_DATA7_PIN, ((byte >> 7) & 1) ^ type);
    
    gpioWrite(inst->pins_digits[inst->current_digit], inst->param.display_type);
    
    if (++inst->current_digit >= inst->param.max_digit) inst->current_digit = 0;
}

// --- Public API ---

void _7segInit(void) {
    display_count = 0;
    // Data pins (assumed macros)
    for(int i=0; i<8; i++) gpioSetMode(_7SEG_DATA0_PIN + i, GPIO_MODE_OUTPUT); 
}

_7seg_instance_t* _7segCreateDisplay(const uint8_t *digit_pins, uint8_t max_digit, uint8_t type) {
    if (display_count >= MAX_DISPLAY_SUPPORT) return NULL;
    
    _7seg_instance_t *inst = &displays[display_count++];
    inst->data = malloc(max_digit);
    if (!inst->data) return NULL;
    
    inst->pins_digits = (uint8_t*)digit_pins;
    inst->param.max_digit = max_digit;
    inst->param.display_type = type;
    inst->current_digit = 0;
    inst->state_handler = state_scanning;
    
    memset(inst->data, 0, max_digit);
    for (uint8_t i = 0; i < max_digit; i++) {
        gpioSetMode(digit_pins[i], GPIO_MODE_OUTPUT);
        gpioWrite(digit_pins[i], !type);
    }
    
    return inst;
}

void _7segScan(void) {
    // This function can be called from a timer ISR
    // In multi-display systems, we switch active display context here
    if (display_count == 0) return;
    
    // Cycle through displays if necessary, or just call the active one
    if (active_display && active_display->state_handler) {
        active_display->state_handler(active_display);
    }
    
    // Context switching for multiplexing multiple displays
    if (active_display->current_digit == 0 && display_count > 1) {
        active_index = (active_index + 1) % display_count;
        active_display = &displays[active_index];
    }
}

void _7segWriteNumber(_7seg_instance_t *display, uint32_t value, uint8_t justify) {
    if (!display) return;
    char buf[12];
    ultoa(value, buf, 10);
    _7segWriteString(display, buf, justify);
}

void _7segWriteString(_7seg_instance_t *display, const char *string, uint8_t justify) {
    if (!display || !string) return;
    uint8_t len = strlen(string);
    uint8_t write_len = (len > display->param.max_digit) ? display->param.max_digit : len;
    uint8_t offset = 0;
    if (justify == _7SEG_CENTER) offset = (display->param.max_digit - write_len) / 2;
    else if (justify == _7SEG_RIGHT) offset = (display->param.max_digit - write_len);
    
    memset(display->data, 0, display->param.max_digit);
    for (uint8_t i = 0; i < write_len; i++) display->data[offset + i] = READ_ASCII(string[i]);
}

void _7segWriteChar(_7seg_instance_t *display, uint8_t digit, char character) {
    if (!display || digit >= display->param.max_digit) return;
    display->data[digit] = READ_ASCII(character);
}

void _7segRemoveDisplay(_7seg_instance_t *display) {
    if (!display) return;
    for (uint8_t i = 0; i < display_count; i++) {
        if (&displays[i] == display) {
            if (display->data) free(display->data);
            // Shift remaining displays
            for (uint8_t j = i; j < (display_count - 1); j++) {
                displays[j] = displays[j + 1];
            }
            display_count--;
            if (active_display == display) {
                active_display = (display_count > 0) ? &displays[0] : NULL;
                active_index = 0;
            }
            break;
        }
    }
}

void _7segClear(_7seg_instance_t *display) {
    if (display) memset(display->data, 0, display->param.max_digit);
}
