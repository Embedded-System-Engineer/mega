#ifndef ZLP_API_H
#define ZLP_API_H

#include "zlp_types.h"

void zlpInit(void);
void zlpDriver(void);

void zlpSendData(const uint8_t *data, uint8_t len);
void zlpPrintLabel(uint8_t copies);
uint8_t zlpIsBusy(void);

#endif // ZLP_API_H
