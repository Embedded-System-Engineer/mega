#ifndef CSMA_PHY_H
#define CSMA_PHY_H

#include "csma_types.h"

csma_status_t csma_phy_init(void);
void csma_phy_deinit(void);
csma_status_t csma_phy_send(const uint8_t* data, uint16_t length);
void csma_phy_receive(uint8_t* buffer, uint16_t* length);
bool csma_phy_is_busy(void);
void csma_phy_set_baud_rate(uint32_t baud_rate);
uint32_t csma_phy_get_baud_rate(void);
void csma_phy_enable(void);
void csma_phy_disable(void);

#endif