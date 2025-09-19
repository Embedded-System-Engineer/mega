#include "csma_mgmt.h"
#include "csma_mac.h"
#include <string.h>

static csma_config_t mgmt_config;
static bool is_server = false;
static uint8_t next_address = 1;

csma_status_t csma_mgmt_init(const csma_config_t* config)
{
    if (config == NULL) return CSMA_STATUS_INVALID_PARAM;
    
    memcpy(&mgmt_config, config, sizeof(csma_config_t));
    is_server = (config->device_type == CSMA_DEVICE_TYPE_SERVER);
    next_address = 1;
    
    return CSMA_STATUS_OK;
}

void csma_mgmt_process(void)
{
    // Management frame processing logic
    if (!is_server) {
        // Client-side management tasks
    } else {
        // Server-side management tasks
    }
}

csma_status_t csma_mgmt_handle_frame(const uint8_t* frame, uint16_t length)
{
    if (frame == NULL || length < CSMA_FRAME_HEADER_SIZE) {
        return CSMA_STATUS_INVALID_PARAM;
    }
    
    uint8_t frame_type = (frame[0] >> 4) & 0x0F;
    
    if (frame_type == CSMA_FRAME_TYPE_MANAGEMENT) {
        uint8_t mgmt_subtype = frame[0] & 0x0F;
        
        switch (mgmt_subtype) {
            case CSMA_MGMT_GET_ADDRESS:
                return csma_mgmt_handle_address_request(frame, length);
                
            case CSMA_MGMT_ASSIGN_ADDRESS:
                return csma_mgmt_handle_address_assign(frame, length);
                
            case CSMA_MGMT_REMOVE_ADDRESS:
                return csma_mgmt_handle_address_remove(frame, length);
                
            default:
                return CSMA_STATUS_INVALID_PARAM;
        }
    }
    
    return CSMA_STATUS_OK;
}

csma_status_t csma_mgmt_send_address_request(void)
{
    if (is_server) return CSMA_STATUS_ERROR;
    
    uint8_t request_frame[CSMA_FRAME_HEADER_SIZE];
    request_frame[0] = (CSMA_FRAME_TYPE_MANAGEMENT << 4) | CSMA_MGMT_GET_ADDRESS;
    request_frame[1] = mgmt_config.station_address;
    request_frame[2] = CSMA_SERVER_ADDRESS;
    request_frame[3] = CSMA_FRAME_HEADER_SIZE;
    
    return csma_mac_queue_data(NULL, 0, CSMA_SERVER_ADDRESS, CSMA_FRAME_TYPE_MANAGEMENT);
}

csma_status_t csma_mgmt_send_address_assign(uint8_t address, uint32_t activation_code)
{
    if (!is_server) return CSMA_STATUS_ERROR;
    
    uint8_t assign_frame[CSMA_FRAME_HEADER_SIZE + 5];
    assign_frame[0] = (CSMA_FRAME_TYPE_MANAGEMENT << 4) | CSMA_MGMT_ASSIGN_ADDRESS;
    assign_frame[1] = mgmt_config.station_address;
    assign_frame[2] = CSMA_BROADCAST_ADDRESS;
    assign_frame[3] = CSMA_FRAME_HEADER_SIZE + 5;
    
    assign_frame[4] = address;
    memcpy(&assign_frame[5], &activation_code, 4);
    
    return csma_mac_queue_data(&assign_frame[4], 5, CSMA_BROADCAST_ADDRESS, CSMA_FRAME_TYPE_MANAGEMENT);
}

void csma_mgmt_set_server_mode(bool server_mode)
{
    is_server = server_mode;
}

bool csma_mgmt_is_server(void)
{
    return is_server;
}

uint8_t csma_mgmt_get_next_address(void)
{
    uint8_t address = next_address;
    next_address++;
    if (next_address > 127) {
        next_address = 1;
    }
    return address;
}

static csma_status_t csma_mgmt_handle_address_request(const uint8_t* frame, uint16_t length)
{
    if (!is_server) return CSMA_STATUS_ERROR;
    
    // Process address request and assign new address
    uint8_t new_address = csma_mgmt_get_next_address();
    uint32_t activation_code = 0;
    memcpy(&activation_code, &frame[4], 4);
    
    return csma_mgmt_send_address_assign(new_address, activation_code);
}

static csma_status_t csma_mgmt_handle_address_assign(const uint8_t* frame, uint16_t length)
{
    if (is_server) return CSMA_STATUS_ERROR;
    
    if (length >= CSMA_FRAME_HEADER_SIZE + 5) {
        uint8_t assigned_address = frame[4];
        uint32_t received_activation_code;
        memcpy(&received_activation_code, &frame[5], 4);
        
        if (received_activation_code == mgmt_config.activation_code) {
            mgmt_config.station_address = assigned_address;
            return CSMA_STATUS_OK;
        }
    }
    
    return CSMA_STATUS_ERROR;
}

static csma_status_t csma_mgmt_handle_address_remove(const uint8_t* frame, uint16_t length)
{
    // Handle address removal logic
    return CSMA_STATUS_OK;
}