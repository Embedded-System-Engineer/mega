#include "../inc/tone_api.h"
#include <string.h>

static tone_channel_t channels[TONES_MAX_PINS_USED];

// Pre-calculated pin mapping
static const uint8_t tone_pins[] = {
#if TONES_MAX_PINS_USED >= 1
    TONE_PIN0_GPIO,
#endif
#if TONES_MAX_PINS_USED >= 2
    TONE_PIN1_GPIO,
#endif
#if TONES_MAX_PINS_USED >= 3
    TONE_PIN2_GPIO,
#endif
#if TONES_MAX_PINS_USED >= 4
    TONE_PIN3_GPIO,
#endif
};

static const uint8_t tone_defaults[] = {
#if TONES_MAX_PINS_USED >= 1
    TONE_PIN0_DEFALUT_STATE,
#endif
#if TONES_MAX_PINS_USED >= 2
    TONE_PIN1_DEFALUT_STATE,
#endif
#if TONES_MAX_PINS_USED >= 3
    TONE_PIN2_DEFALUT_STATE,
#endif
#if TONES_MAX_PINS_USED >= 4
    TONE_PIN3_DEFALUT_STATE,
#endif
};

// --- State Machine Handlers ---

static void stateIdle(void *arg) {
    // Wait for tonePlay to change state/flag
}

static void stateToggling(void *arg) {
    uint8_t i = (uintptr_t)arg;
    tone_channel_t *ch = &channels[i];
    
    if (!sysIsTimeoutMs(&ch->timer)) return;

    if (ch->toggle == 0) {
        if (ch->duration == 0) {
            ch->is_active = 0;
            ch->state_handler = stateIdle;
            gpioWrite(tone_pins[i], tone_defaults[i]);
            return;
        }
        ch->duration--;
    }
    
    sysSetPeriodMS(&ch->timer, ch->period[ch->toggle]);
    ch->toggle ^= 1;
    
    if (ch->period[0] != 0) {
        gpioWrite(tone_pins[i], GPIO_TGL);
    }
}

// --- Public API ---

void toneInit(void) {
    memset(channels, 0, sizeof(channels));
    for (int i = 0; i < TONES_MAX_PINS_USED; i++) {
        gpioSetMode(tone_pins[i], GPIO_MODE_OUTPUT);
        gpioWrite(tone_pins[i], tone_defaults[i]);
        channels[i].state_handler = stateIdle;
    }
}

void toneDriver(void) {
    for (uintptr_t i = 0; i < TONES_MAX_PINS_USED; i++) {
        if (channels[i].state_handler) {
            channels[i].state_handler((void *)i);
        }
    }
}

void tonePlay(uint8_t channel, uint16_t period, uint8_t duration, uint16_t on_time) {
    if (channel >= TONES_MAX_PINS_USED) return;
    
    tone_channel_t *ch = &channels[channel];
    ch->period[0] = on_time;
    ch->period[1] = period - on_time;
    ch->toggle = 0;
    ch->duration = duration;
    ch->is_active = 1;
    ch->state_handler = stateToggling;
    sysSetPeriodMS(&ch->timer, 0);
}

void toneStop(uint8_t channel) {
    if (channel >= TONES_MAX_PINS_USED) return;
    channels[channel].is_active = 0;
    channels[channel].state_handler = stateIdle;
    gpioWrite(tone_pins[channel], tone_defaults[channel]);
}

uint8_t toneIsPlaying(uint8_t channel) {
    if (channel >= TONES_MAX_PINS_USED) return 0;
    return channels[channel].is_active;
}
