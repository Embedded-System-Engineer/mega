#ifndef CSMA_MGMT_H
#define CSMA_MGMT_H

#include "csma_types.h"

csma_status_t csma_mgmt_init(const csma_config_t* config);
void csma_mgmt_process(void);
csma_status_t csma_mgmt_handle_frame(const uint8_t* frame, uint16_t length);
csma_status_t csma_mgmt_send_address_request(void);
csma_status_t csma_mgmt_send_address_assign(uint8_t address, uint32_t activation_code);
csma_status_t csma_mgmt_send_address_remove(uint8_t address);
void csma_mgmt_set_server_mode(bool is_server);
bool csma_mgmt_is_server(void);
uint8_t csma_mgmt_get_next_address(void);

#endif