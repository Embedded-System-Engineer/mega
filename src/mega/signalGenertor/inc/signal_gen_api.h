#ifndef SIGNAL_GEN_API_H
#define SIGNAL_GEN_API_H

#include "signal_gen_types.h"

void signalGenInit(void);
void signalGenDriver(void);

void signalGenStart(uint8_t channel, const signal_config_t *config);
void signalGenStop(uint8_t channel);

#endif // SIGNAL_GEN_API_H
