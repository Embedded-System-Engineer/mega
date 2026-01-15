#ifndef TONE_API_H
#define TONE_API_H

#include "tone_types.h"

void toneInit(void);
void toneDriver(void);

void tonePlay(uint8_t channel, uint16_t period, uint8_t duration, uint16_t on_time);
void toneStop(uint8_t channel);
uint8_t toneIsPlaying(uint8_t channel);

#endif // TONE_API_H
