#ifndef USART_API_H
#define USART_API_H

#include "usart_types.h"

void usartInit(void);
void usartPutByte(usart_port_t port, uint8_t byte);
uint8_t usartGetByte(usart_port_t port);
uint8_t usartHasError(usart_port_t port);

#endif // USART_API_H
