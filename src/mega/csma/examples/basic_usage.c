#include "inc/csma_api.h"

// Example callback for receiving data
uint8_t my_receive_callback(uint8_t sa, uint8_t da, uint8_t len, uint8_t *data) {
    // Process incoming data
    return 1; // Return 1 to indicate processing is done
}

int main(void) {
    // 1. Initialize the CSMA module
    csma_init();
    
    // 2. Configure as Client (0) or Server (1)
    csma_configure_node(0, 0x12345678); // Client with auth code
    
    // 3. Register your receive callback
    csma_set_on_host_request(my_receive_callback);
    
    // 4. Set your node address (usually done by management protocol, but can be manual)
    csma_set_node_addr(5);
    csma_set_node_ip(1); // Enable protocol
    
    while(1) {
        // 5. Run the driver in the main loop
        csma_driver();
        
        // Example: Send some data periodically (pseudo-code)
        // if (trigger) {
        //     uint8_t msg[] = {0xAA, 0xBB};
        //     csma_put_data(msg, 2, 0, 1); // Send to Server (addr 0)
        // }
    }
}
