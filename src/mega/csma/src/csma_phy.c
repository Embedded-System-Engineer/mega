#include "inc/csma_internal.h"
#include "../../../inc/mega.h"

// Global Instance
csma_instance_t csma;

void csmaPhyTxByte(uint8_t b) {
#if CSMA_UART_CH == 1
    usartPutByte(USART_PORT1, b);
#else
    usartPutByte(USART_PORT0, b);
#endif
}

uint8_t csmaPhyRxByte(void) {
#if CSMA_UART_CH == 1
    return usartGetByte(USART_PORT1);
#else
    return usartGetByte(USART_PORT0);
#endif
}

uint8_t csmaPhyHasError(void) {
#if CSMA_UART_CH == 1
    return usartHasError(USART_PORT1);
#else
    return usartHasError(USART_PORT0);
#endif
}

// External Interrupt for Sync (Pin Change or External Int)
#if (defined (EICRA)) && (defined (EICRB))
    #if CSMA_UART_CH == 1
        ISR(INT2_vect) {
            csmaHwTimerStop();
            csma.stateHandler = stateReceive;
        }
    #else
        ISR(INT4_vect) {
            csmaHwTimerStop();
            csma.stateHandler = stateReceive;
        }
    #endif
#elif defined GICR
    ISR(INT0_vect) {
        csmaHwTimerStop();
        csma.stateHandler = stateReceive;
    }
#endif

// UART Receive ISR
#if CSMA_UART_CH == 1
ISR(USART1_RX_vect) 
#else
ISR(USART0_RX_vect)
#endif
{
    csmaHwTimerStop();
    uint8_t b = csmaPhyRxByte();
    
    if (csma.rxByteCount < CSMA_MAX_FRAME_LEN) {
        csma.rxBuffer[csma.rxByteCount] = b;
        
        // Collision detection or sequence validation
        if (csma.rxIntent == RX_TARGET_MY_FRAME) {
            if (csma.txBuffer[csma.txByteCount] != b) {
                csma.collisionDetected = 1;
                csma.txByteCount = 0;
                csma.rxIntent = RX_TARGET_OTHER;
            } else {
                csma.txByteCount++;
                if (csma.txByteCount < csma.txBuffer[7]) { // 7 is length index
                    csmaPhyTxByte(csma.txBuffer[csma.txByteCount]);
                } else {
                    csma.txByteCount = 0;
                    csma.collisionDetected = 0;
                }
            }
        }
        else if (csma.rxIntent == RX_TARGET_MY_ACK) {
            // Simplified ACK checking (can be expanded)
            if (csma.ackBuffer[csma.txByteCount] != b) {
                csma.txByteCount = 0;
                csma.rxIntent = RX_TARGET_OTHER;
            } else {
                csma.txByteCount++;
                if (csma.txByteCount < 9) {
                    csmaPhyTxByte(csma.ackBuffer[csma.txByteCount]);
                } else {
                    csma.txByteCount = 0;
                }
            }
        }
        
        csma.rxByteCount++;
    } else {
        csma.rxByteCount = 0;
    }

    csmaHwTimerStart(CSMA_RIFS);
    csma.stateHandler = stateReceive;
}
