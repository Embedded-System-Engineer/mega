#include "csma_mac.h"
#include "csma_phy.h"
#include "csma_timer.h"
#include "csma_mgmt.h"
#include <string.h>
#include <stdlib.h>

static csma_mac_state_t mac_state;
static csma_config_t mac_config;
static uint8_t tx_buffer[CSMA_MAX_FRAME_SIZE];
static uint8_t rx_buffer[CSMA_MAX_FRAME_SIZE];
static csma_tx_queue_item_t tx_queue[CSMA_QUEUE_SIZE];
static uint8_t queue_head = 0;
static uint8_t queue_tail = 0;
static uint8_t queue_size = 0;
static uint16_t current_backoff = 0;
static uint8_t current_retry = 0;

static uint8_t calculate_crc(const uint8_t* data, uint16_t length);

csma_status_t csma_mac_init(const csma_config_t* config)
{
    if (config == NULL) return CSMA_STATUS_INVALID_PARAM;
    
    memset(&mac_state, 0, sizeof(mac_state));
    mac_state.current_state = CSMA_MAC_STATE_IDLE;
    memcpy(&mac_config, config, sizeof(csma_config_t));
    
    memset(tx_buffer, 0, sizeof(tx_buffer));
    memset(rx_buffer, 0, sizeof(rx_buffer));
    memset(tx_queue, 0, sizeof(tx_queue));
    
    queue_head = queue_tail = queue_size = 0;
    current_backoff = 0;
    current_retry = 0;
    
    return CSMA_STATUS_OK;
}

void csma_mac_process(void)
{
    switch (mac_state.current_state) {
        case CSMA_MAC_STATE_IDLE:
            if (queue_size > 0) {
                mac_state.current_state = CSMA_MAC_STATE_CCA;
            }
            break;
            
        case CSMA_MAC_STATE_CCA:
            if (!csma_mac_cca()) {
                mac_state.current_state = CSMA_MAC_STATE_BACKOFF;
                current_backoff = csma_mac_calculate_backoff();
                csma_timer_start(CSMA_TIMER_BACKOFF, current_backoff * CSMA_SLOT_TIME_US);
            } else {
                mac_state.current_state = CSMA_MAC_STATE_SENDING;
                csma_mac_send_frame();
            }
            break;
            
        case CSMA_MAC_STATE_BACKOFF:
            if (csma_timer_is_expired(CSMA_TIMER_BACKOFF)) {
                mac_state.current_state = CSMA_MAC_STATE_CCA;
            }
            break;
            
        case CSMA_MAC_STATE_SENDING:
            break;
            
        case CSMA_MAC_STATE_WAITING_ACK:
            if (csma_timer_is_expired(CSMA_TIMER_ACK)) {
                csma_mac_handle_tx_complete(CSMA_STATUS_NO_ACK);
            }
            break;
            
        case CSMA_MAC_STATE_RECEIVING:
            break;
    }
}

csma_status_t csma_mac_queue_data(const uint8_t* data, uint16_t length, 
                                uint8_t destination, csma_frame_type_t frame_type)
{
    if (queue_size >= CSMA_QUEUE_SIZE) return CSMA_STATUS_BUFFER_FULL;
    
    tx_queue[queue_tail].data = (uint8_t*)data;
    tx_queue[queue_tail].length = length;
    tx_queue[queue_tail].destination = destination;
    tx_queue[queue_tail].frame_type = frame_type;
    tx_queue[queue_tail].retry_count = 0;
    
    queue_tail = (queue_tail + 1) % CSMA_QUEUE_SIZE;
    queue_size++;
    
    return CSMA_STATUS_OK;
}

static void csma_mac_send_frame(void)
{
    if (queue_size == 0) return;
    
    csma_tx_queue_item_t* item = &tx_queue[queue_head];
    uint16_t frame_length = CSMA_FRAME_HEADER_SIZE + item->length + 1;
    
    if (frame_length > CSMA_MAX_FRAME_SIZE) {
        csma_mac_handle_tx_complete(CSMA_STATUS_BUFFER_FULL);
        return;
    }
    
    tx_buffer[0] = (item->frame_type << 4);
    tx_buffer[1] = mac_config.station_address;
    tx_buffer[2] = item->destination;
    tx_buffer[3] = frame_length;
    
    if (item->length > 0) {
        memcpy(&tx_buffer[CSMA_FRAME_HEADER_SIZE], item->data, item->length);
    }
    
    tx_buffer[CSMA_FRAME_HEADER_SIZE + item->length] = calculate_crc(tx_buffer, CSMA_FRAME_HEADER_SIZE + item->length);
    
    csma_status_t status = csma_phy_send(tx_buffer, frame_length);
    if (status == CSMA_STATUS_OK) {
        csma_timer_start(CSMA_TIMER_ACK, CSMA_ACK_TIMEOUT_US);
        mac_state.current_state = CSMA_MAC_STATE_WAITING_ACK;
    } else {
        csma_mac_handle_tx_complete(status);
    }
}

void csma_mac_handle_tx_complete(csma_status_t status)
{
    if (queue_size == 0) return;
    
    csma_tx_queue_item_t* item = &tx_queue[queue_head];
    
    if (status != CSMA_STATUS_OK) {
        item->retry_count++;
        if (item->retry_count < mac_config.max_retry_count) {
            mac_state.current_state = CSMA_MAC_STATE_BACKOFF;
            current_backoff = csma_mac_calculate_backoff();
            csma_timer_start(CSMA_TIMER_BACKOFF, current_backoff * CSMA_SLOT_TIME_US);
            return;
        }
    }
    
    queue_head = (queue_head + 1) % CSMA_QUEUE_SIZE;
    queue_size--;
    mac_state.current_state = CSMA_MAC_STATE_IDLE;
}

void csma_mac_handle_collision(void)
{
    current_retry++;
    if (current_retry < mac_config.max_retry_count) {
        mac_state.current_state = CSMA_MAC_STATE_BACKOFF;
        current_backoff = csma_mac_calculate_backoff();
        csma_timer_start(CSMA_TIMER_BACKOFF, current_backoff * CSMA_SLOT_TIME_US);
    } else {
        csma_mac_handle_tx_complete(CSMA_STATUS_COLLISION);
    }
}

bool csma_mac_cca(void)
{
    return !csma_phy_is_busy();
}

uint16_t csma_mac_calculate_backoff(void)
{
    uint16_t max_backoff = (1 << current_retry) * mac_config.contention_window_min;
    if (max_backoff > mac_config.contention_window_max) {
        max_backoff = mac_config.contention_window_max;
    }
    return rand() % max_backoff;
}

static uint8_t calculate_crc(const uint8_t* data, uint16_t length)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
    }
    return crc;
}