#ifndef TWI_API_H
#define TWI_API_H

#include "twi_types.h"

void twiInit(uint32_t speed);
twi_status_t twiMasterTransfer(twi_package_t *pkg, uint8_t is_read);
twi_status_t twiGetStatus(void);

#endif // TWI_API_H
