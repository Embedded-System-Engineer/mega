#ifndef CSMA_MAC_H
#define CSMA_MAC_H

#include "csma_types.h"

typedef struct {
    uint8_t* data;
    uint16_t length;
    uint8_t destination;
    csma_frame_type_t frame_type;
    uint8_t retry_count;
} csma_tx_queue_item_t;

csma_status_t csma_mac_init(const csma_config_t* config);
void csma_mac_process(void);
csma_status_t csma_mac_queue_data(const uint8_t* data, uint16_t length, 
                                uint8_t destination, csma_frame_type_t frame_type);
void csma_mac_handle_rx_frame(const uint8_t* frame, uint16_t length);
void csma_mac_handle_tx_complete(csma_status_t status);
void csma_mac_handle_collision(void);
bool csma_mac_cca(void);
uint16_t csma_mac_calculate_backoff(void);

#endif