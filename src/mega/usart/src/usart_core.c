#include "../inc/usart_api.h"
#include <avr/io.h>

// Register structure for USART mapping
typedef struct {
    volatile uint8_t *udr;
    volatile uint8_t *ucsra;
    volatile uint8_t *ucsrb;
    volatile uint8_t *ucsrc;
    volatile uint8_t *ubrrl;
    volatile uint8_t *ubrrh;
    uint8_t rxen_bit;
    uint8_t txen_bit;
    uint8_t rxcie_bit;
    uint8_t udre_bit;
    uint8_t fe_bit;
    uint8_t dor_bit;
} usart_hw_t;

// Port lookup table (Branchless dispatch)
static const usart_hw_t usart_hw[] = {
#ifdef UDR0
    { &UDR0, &UCSR0A, &UCSR0B, &UCSR0C, &UBRR0L, &UBRR0H, RXEN0, TXEN0, RXCIE0, UDRE0, FE0, DOR0 },
#endif
#ifdef UDR1
    { &UDR1, &UCSR1A, &UCSR1B, &UCSR1C, &UBRR1L, &UBRR1H, RXEN1, TXEN1, RXCIE1, UDRE1, FE1, DOR1 },
#endif
};

void usartInit(void) {
    // Note: BAUD_PRESCALE must be defined globally (e.g. in Makefile or config.h)
    for (uint8_t i = 0; i < (sizeof(usart_hw) / sizeof(usart_hw_t)); i++) {
        const usart_hw_t *hw = &usart_hw[i];
        *hw->ubrrh = (uint8_t)(BAUD_PRESCALE >> 8);
        *hw->ubrrl = (uint8_t)BAUD_PRESCALE;
        *hw->ucsrb = (1 << hw->rxen_bit) | (1 << hw->txen_bit) | (1 << hw->rxcie_bit);
        *hw->ucsrc = (3 << 1); // 8-bit (simplified mapping)
    }
}

void usartPutByte(usart_port_t port, uint8_t byte) {
    const usart_hw_t *hw = &usart_hw[port];
    while (!(*hw->ucsra & (1 << hw->udre_bit)));
    *hw->udr = byte;
}

uint8_t usartGetByte(usart_port_t port) {
    return *usart_hw[port].udr;
}

uint8_t usartHasError(usart_port_t port) {
    const usart_hw_t *hw = &usart_hw[port];
    return (*hw->ucsra & ((1 << hw->fe_bit) | (1 << hw->dor_bit)));
}
