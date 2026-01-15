#include "../inc/signal_gen_api.h"
#include "../../gpio/inc/gpio_api.h"
#include "../../system/inc/system_api.h"
#include <string.h>

typedef void (*signal_state_handler_t)(void *arg);

typedef struct {
    uint8_t               is_active;
    signal_config_t       config;
    uint8_t               cycle_counter;
    uint8_t               toggle_counter;
    system_timer_t        timer;
    signal_state_handler_t state_handler;
} signal_channel_t;

#ifndef MAX_SIGNAL_CHANNELS
#define MAX_SIGNAL_CHANNELS 4
#endif

static signal_channel_t channels[MAX_SIGNAL_CHANNELS];

// Simplified pin mapping for demonstration
static const uint8_t signal_pins[] = { 10, 11, 12, 13 };

static void state_idle(void *arg);
static void state_toggling(void *arg);
static void state_sleeping(void *arg);

// --- State Handlers ---

static void state_idle(void *arg) {
    // Wait for start
}

static void state_toggling(void *arg) {
    signal_channel_t *ch = (signal_channel_t *)arg;
    if (!system_is_timeout(&ch->timer)) return;

    // Toggle logic
    gpioWrite(signal_pins[ch - channels], GPIO_TGL);
    
    if (++ch->toggle_counter >= (ch->config.toggle_count * 2)) {
        ch->toggle_counter = 0;
        ch->state_handler = state_sleeping;
        system_set_timer_ms(&ch->timer, ch->config.period * ch->config.sleep_count);
    } else {
        uint16_t t = (ch->toggle_counter % 2 == 0) ? 
                     (ch->config.period * ch->config.duty / 100) :
                     (ch->config.period * (100 - ch->config.duty) / 100);
        system_set_timer_ms(&ch->timer, t);
    }
}

static void state_sleeping(void *arg) {
    signal_channel_t *ch = (signal_channel_t *)arg;
    if (!system_is_timeout(&ch->timer)) return;

    if (ch->config.repeat && ++ch->cycle_counter >= ch->config.repeat) {
        ch->is_active = 0;
        ch->state_handler = state_idle;
    } else {
        ch->state_handler = state_toggling;
        system_set_timer_ms(&ch->timer, 0);
    }
}

// --- Public API ---

void signalGenInit(void) {
    memset(channels, 0, sizeof(channels));
    for (int i = 0; i < MAX_SIGNAL_CHANNELS; i++) {
        channels[i].state_handler = state_idle;
        gpioSetMode(signal_pins[i], GPIO_MODE_OUTPUT);
    }
}

void signalGenDriver(void) {
    for (int i = 0; i < MAX_SIGNAL_CHANNELS; i++) {
        if (channels[i].state_handler) channels[i].state_handler(&channels[i]);
    }
}

void signalGenStart(uint8_t channel, const signal_config_t *config) {
    if (channel >= MAX_SIGNAL_CHANNELS) return;
    channels[channel].config = *config;
    channels[channel].is_active = 1;
    channels[channel].cycle_counter = 0;
    channels[channel].toggle_counter = 0;
    channels[channel].state_handler = state_toggling;
    system_set_timer_ms(&channels[channel].timer, 0);
}

void signalGenStop(uint8_t channel) {
    if (channel >= MAX_SIGNAL_CHANNELS) return;
    channels[channel].is_active = 0;
    channels[channel].state_handler = state_idle;
    gpioWrite(signal_pins[channel], 0);
}
