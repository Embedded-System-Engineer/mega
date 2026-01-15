#include "../inc/utility_api.h"
#include <string.h>

uint8_t uXX_to_ascii(uint8_t *s, uint32_t x, uint8_t max) {
    uint8_t i = 0;
    memset(s, '0', max);
    if (x == 0) return max - 1;

    while (i < max && x > 0) {
        s[max - 1 - i] = (x % 10) + '0';
        x /= 10;
        i++;
    }
    return (max - i);
}

uint8_t u32_to_ascii(uint8_t *s, uint32_t x) {
    return uXX_to_ascii(s, x, 10);
}

uint8_t bcd_to_dec(uint8_t bcd) {
    return ((bcd & 0x0F) + ((bcd >> 4) * 10));
}

uint8_t dec_to_bcd(uint8_t dec) {
    return (((dec / 10) << 4) | (dec % 10));
}

uint8_t map_value(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
    if (in_max == in_min) return out_min;
    return (uint8_t)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

uint8_t crc8_check(uint8_t *data, uint8_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x01) crc ^= 0x91;
            crc >>= 1;
        }
    }
    return crc;
}
