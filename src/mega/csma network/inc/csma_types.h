#ifndef CSMA_TYPES_H
#define CSMA_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    CSMA_STATUS_OK = 0,
    CSMA_STATUS_ERROR,
    CSMA_STATUS_BUSY,
    CSMA_STATUS_TIMEOUT,
    CSMA_STATUS_INVALID_PARAM,
    CSMA_STATUS_BUFFER_FULL,
    CSMA_STATUS_NO_ACK,
    CSMA_STATUS_COLLISION,
    CSMA_STATUS_NOT_INITIALIZED,
    CSMA_STATUS_CHANNEL_BUSY
} csma_status_t;

typedef enum {
    CSMA_DEVICE_TYPE_CLIENT = 0,
    CSMA_DEVICE_TYPE_SERVER = 1
} csma_device_type_t;

typedef enum {
    CSMA_FRAME_TYPE_DATA = 0,
    CSMA_FRAME_TYPE_MANAGEMENT = 1,
    CSMA_FRAME_TYPE_CONTROL = 2,
    CSMA_FRAME_TYPE_SERIAL = 3
} csma_frame_type_t;

typedef enum {
    CSMA_CONTROL_ACK = 0,
    CSMA_CONTROL_NACK = 1,
    CSMA_CONTROL_BLOCK = 2,
    CSMA_CONTROL_FREE = 3
} csma_control_frame_subtype_t;

typedef enum {
    CSMA_MGMT_GET_ADDRESS = 0,
    CSMA_MGMT_ASSIGN_ADDRESS = 1,
    CSMA_MGMT_REMOVE_ADDRESS = 2,
    CSMA_MGMT_CONFIRM_REMOVAL = 3
} csma_management_frame_subtype_t;

typedef enum {
    CSMA_STATE_IDLE = 0,
    CSMA_STATE_RECEIVING,
    CSMA_STATE_SENDING,
    CSMA_STATE_WAITING_ACK,
    CSMA_STATE_BACKOFF,
    CSMA_STATE_BLOCKED
} csma_system_state_t;

typedef enum {
    CSMA_MAC_STATE_IDLE = 0,
    CSMA_MAC_STATE_CCA,
    CSMA_MAC_STATE_BACKOFF,
    CSMA_MAC_STATE_SENDING,
    CSMA_MAC_STATE_WAITING_ACK,
    CSMA_MAC_STATE_RECEIVING
} csma_mac_state_t;

typedef void (*csma_data_callback_t)(uint8_t source, uint8_t destination, 
                                   const uint8_t* data, uint16_t length);
typedef void (*csma_status_callback_t)(csma_status_t status, void* context);
typedef void (*csma_timer_callback_t)(void);

typedef struct {
    uint8_t device_type;
    uint32_t activation_code;
    uint8_t station_address;
    uint16_t max_retry_count;
    uint16_t max_payload_size;
    uint16_t ack_timeout_ms;
    uint16_t backoff_time_min_ms;
    uint16_t backoff_time_max_ms;
    uint16_t contention_window_min;
    uint16_t contention_window_max;
    uint32_t baud_rate;
} csma_config_t;

typedef struct {
    csma_system_state_t current_state;
    uint16_t collision_count;
    uint16_t retry_count;
    uint16_t current_contention_window;
    bool transmission_in_progress;
    uint32_t last_activity_time;
} csma_system_state_info_t;

#endif