#include "csma.h"
#include "csma_mac.h"
#include "csma_phy.h"
#include "csma_timer.h"
#include "csma_mgmt.h"
#include <string.h>

static csma_config_t system_config;
static csma_system_state_info_t system_state;
static csma_data_callback_t data_callback = NULL;
static csma_status_callback_t status_callback = NULL;
static bool system_initialized = false;

csma_status_t csma_init(const csma_config_t* config)
{
    if (config == NULL) {
        return CSMA_STATUS_INVALID_PARAM;
    }
    
    memset(&system_state, 0, sizeof(system_state));
    system_state.current_state = CSMA_STATE_IDLE;
    system_state.current_contention_window = config->contention_window_min;
    
    memcpy(&system_config, config, sizeof(csma_config_t));
    
    csma_status_t status = csma_phy_init();
    if (status != CSMA_STATUS_OK) return status;
    
    status = csma_mac_init(config);
    if (status != CSMA_STATUS_OK) return status;
    
    status = csma_timer_init();
    if (status != CSMA_STATUS_OK) return status;
    
    status = csma_mgmt_init(config);
    if (status != CSMA_STATUS_OK) return status;
    
    system_initialized = true;
    return CSMA_STATUS_OK;
}

void csma_deinit(void)
{
    csma_phy_deinit();
    system_initialized = false;
}

void csma_process(void)
{
    if (!system_initialized) return;
    
    csma_timer_process();
    csma_mac_process();
    csma_mgmt_process();
}

void csma_set_config(const csma_config_t* config)
{
    if (config != NULL) {
        memcpy(&system_config, config, sizeof(csma_config_t));
    }
}

void csma_get_config(csma_config_t* config)
{
    if (config != NULL) {
        memcpy(config, &system_config, sizeof(csma_config_t));
    }
}

csma_status_t csma_send_data(const uint8_t* data, uint16_t length, 
                           uint8_t destination, csma_frame_type_t frame_type)
{
    if (!system_initialized) return CSMA_STATUS_NOT_INITIALIZED;
    if (data == NULL || length == 0 || length > system_config.max_payload_size) {
        return CSMA_STATUS_INVALID_PARAM;
    }
    
    if (system_state.transmission_in_progress) {
        return CSMA_STATUS_BUSY;
    }
    
    return csma_mac_queue_data(data, length, destination, frame_type);
}

uint8_t csma_get_station_address(void)
{
    return system_config.station_address;
}

csma_status_t csma_set_station_address(uint8_t address)
{
    system_config.station_address = address;
    return CSMA_STATUS_OK;
}

void csma_register_data_callback(csma_data_callback_t callback)
{
    data_callback = callback;
}

void csma_register_status_callback(csma_status_callback_t callback)
{
    status_callback = callback;
}

csma_system_state_info_t csma_get_system_state(void)
{
    return system_state;
}

uint16_t csma_get_collision_count(void)
{
    return system_state.collision_count;
}

uint16_t csma_get_retry_count(void)
{
    return system_state.retry_count;
}

csma_status_t csma_start(void)
{
    if (!system_initialized) return CSMA_STATUS_NOT_INITIALIZED;
    csma_phy_enable();
    return CSMA_STATUS_OK;
}

csma_status_t csma_stop(void)
{
    csma_phy_disable();
    return CSMA_STATUS_OK;
}

bool csma_is_ready(void)
{
    return system_initialized && !system_state.transmission_in_progress;
}