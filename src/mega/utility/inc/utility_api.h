#ifndef UTILITY_API_H
#define UTILITY_API_H

#include <stdint.h>

uint8_t uXX_to_ascii(uint8_t *s, uint32_t x, uint8_t max);
uint8_t u32_to_ascii(uint8_t *s, uint32_t x);
uint8_t bcd_to_dec(uint8_t bcd);
uint8_t dec_to_bcd(uint8_t dec);
uint8_t map_value(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
uint8_t crc8_check(uint8_t *data, uint8_t len);

#endif // UTILITY_API_H
