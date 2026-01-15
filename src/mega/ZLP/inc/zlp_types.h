#ifndef ZLP_TYPES_H
#define ZLP_TYPES_H

#include <stdint.h>

typedef enum {
    ZLP_IDLE,
    ZLP_CONFIGURING,
    ZLP_PRINTING,
    ZLP_BUSY
} zlp_status_t;

#endif // ZLP_TYPES_H
