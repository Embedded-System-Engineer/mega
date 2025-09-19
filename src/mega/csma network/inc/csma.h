#ifndef CSMA_H
#define CSMA_H

#include "csma_types.h"
#include "csma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

csma_status_t csma_init(const csma_config_t* config);
void csma_deinit(void);
void csma_process(void);

void csma_set_config(const csma_config_t* config);
void csma_get_config(csma_config_t* config);

csma_status_t csma_send_data(const uint8_t* data, uint16_t length, 
                           uint8_t destination, csma_frame_type_t frame_type);

uint8_t csma_get_station_address(void);
csma_status_t csma_set_station_address(uint8_t address);

void csma_register_data_callback(csma_data_callback_t callback);
void csma_register_status_callback(csma_status_callback_t callback);

csma_system_state_info_t csma_get_system_state(void);
uint16_t csma_get_collision_count(void);
uint16_t csma_get_retry_count(void);

csma_status_t csma_start(void);
csma_status_t csma_stop(void);
bool csma_is_ready(void);

#ifdef __cplusplus
}
#endif

#endif