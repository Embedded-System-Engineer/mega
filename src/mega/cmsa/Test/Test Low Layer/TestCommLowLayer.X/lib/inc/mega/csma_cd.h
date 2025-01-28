/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_CSMA_CD_H
#define	XC_CSMA_CD_H

#include "../mega.h"
#if defined CSMA_CD_MODULE 
#if CSMA_CD_MODULE

#define  MASTER            (0x01)
#define  SLAVE_POINT        (0x02)
#define  SLAVE_DISPALY   (0x03)



#ifndef DECIVE_TYPE
#define DECIVE_TYPE    (MASTER)
#endif

#ifndef Master_Address
#define Master_Address    (0)
#endif
#define   CSMA_FREE_ADDRESS          0x81
#define   CSMA_BLOCK_ADDRESS         0x80
#if DECIVE_TYPE == SLAVE_POINT 
#ifndef       CSMA_A0 
#define      CSMA_A0                       NOT_A_PIN
#endif 

#ifndef       CSMA_A1 
#define      CSMA_A1                      NOT_A_PIN
#endif 
#ifndef       CSMA_A2 
#define      CSMA_A2                       NOT_A_PIN
#endif 
#ifndef       CSMA_A3 
#define      CSMA_A3                      NOT_A_PIN
#endif 
#ifndef       CSMA_A4 
#define      CSMA_A4                       NOT_A_PIN
#endif 
#ifndef       CSMA_A5 
#define      CSMA_A5                       NOT_A_PIN
#endif 
#ifndef       CSMA_A6 
#define      CSMA_A6                       NOT_A_PIN
#endif 
#endif


#define   CSMA_TYPED_BLOCKED       0x00
#define   CSMA_TYPED_NORMAL        0x01

typedef struct {
    uint8_t u8Address;
    uint8_t u8ByteCount;
    uint8_t u8Data[COM_PLAYLOAD_SIZE]; // 8byte data
} stFram_t;

typedef enum _eFrameIndex {
    Address = 0,
    bytecount = 1,
    startbyte = 2
} eFrameIndex;



extern stFram_t gsTransmissionFrame;
extern stFram_t gsReceiveFrame;


#define  COMM_BUFFER_LENGTH      (3+COM_PLAYLOAD_SIZE) 

#define DATA_REMOVED             (128)





#define  FREQUNCY_VALUE(x)        ((1000000UL) / x)+1       

#if defined USART0_ENABLED
#define  REGITER_RECIVE_VALUE      (F_CPU / (64UL * UART0_BUADRATE))
#define  REGISTER_BLOCKED_VALUE        (F_CPU / (64UL * 10UL))
#define  CSMA_BIT_DURATION            ((1000000UL)/UART0_BUADRATE)
#define  BYTE_DURATION           ((1000000UL)/UART0_BUADRATE)
#endif

#if defined USART1_ENABLED
#define  REGITER_RECIVE_VALUE      (F_CPU / (64UL * UART1_BUADRATE))
#define  REGISTER_BLOCKED_VALUE        (F_CPU / (64UL * 10UL))
#define  CSMA_BIT_DURATION            ((1000000UL)/UART1_BUADRATE)
#define  BYTE_DURATION           ((1000000UL)/UART1_BUADRATE)
#endif

#define          CSMA_RESPONSE_TIME_OUT_US        (127UL*2UL*CSMA_BIT_DURATION) + (COMM_BUFFER_LENGTH*BYTE_DURATION) + (2*BYTE_DURATION)
#define          CSMA_RESPONSE_TIME_OUT_MS        (CSMA_RESPONSE_TIME_OUT_US / 1000UL)

#define           REGITER_CONTROL_A              0x00
#define           REGITER_CONTROL_B              0x0B
#if  defined(__AVR_ATmega128A__) || defined (__AVR_ATmega128__)
#define           REFITER_CONTROL_E              0x10
#else
#define           REFITER_CONTROL_E              0x02
#endif








/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csmaInitV1  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitV1                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void csmaInitV1();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csmaDriverV1  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriverV1                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void csmaDriverV1();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < StartTransmissionV1  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void StartTransmissionV1                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void StartTransmissionV1();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrameV1  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameV1(pAsyncFunc_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnClientFrameV1  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnClientFrameV1                                                            |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnClientFrameV1(pAsyncFunc_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < csmaGetAddressV1  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaGetAddressV1                                                           |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t csmaGetAddressV1();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < IsCommunicationOpenV1  >                                                  |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void IsCommunicationOpenV1                                                      |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t IsCommunicationOpenV1();

#endif
#endif
#endif	/* XC_CSMA_CD_H */

