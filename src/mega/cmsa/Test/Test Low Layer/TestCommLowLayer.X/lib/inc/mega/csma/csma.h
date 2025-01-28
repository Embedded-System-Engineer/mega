
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                  : csma.h                                                                      |                                  
| < Author                : Hassan Elsaied                                                              |
| < Version               : Mega2v241022                                                                |
| < Refences              : no- ref                                                                     |  
| < SRAM USAGE            : channel 0 only used 62 Byte                                                 |
|                         : channel 0 and channel 1 with serial half-duplex 130 Byte                    |
|                         : channel 0 and channel 1 with serial Full-duplex 139 Byte                    |
| < PROGRAM USAGE         : channel 0 only used  Byte ( Instructions)                                   |
|                         : channel 0 and channel 1 with serial half-duplex  Byte (Instruction)         |
|                         : channel 0 and channel 1 with serial Full-duplex  Byte Byte (Instruction)    |                                     
| < Hardware Usage        : Timer 1 and USART 0 with channel 0 only used                                |
|                         : Timer 1 and Timer 2 and USART 0 and USART 1 with channel 0 and channel 1    |
| < File Created          : 24-10-2022                                                                  |
---------------------------------------------------------------------------------------------------------
 */


#ifndef CSMA_H
#define	CSMA_H
#include "../../mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE
/*
 *<@macro Data Index Into Buffer
 */
#define BUFFER_DATA_INDEX              8
/*
 *<@macro Data Index Into Buffer
 */
#define BUFFER_PERFIX_LENGTH           8
/*
 * <@macro Max Length of Frarme  
 */
#define BUFFER_MAX_LENGTH        BUFFER_PERFIX_LENGTH + COM_PAYLOAD_SIZE + 1 

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartPutByte(uint8_t byte);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline uint8_t ch0_usartGetByteByte();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartEmptyBuffer >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartEmptyBuffer                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartEmptyBuffer();

/*
 * FrameType          : Three Type Of Frame 
 */
typedef enum {
    setSerialFrame = 0,
    MangmentFrame = 1,
    DataFrame = 2,
    ControlFrame = 3
} FrameType;

/*
 * FrameSubType          : Control Frame
 */
typedef enum {
    NackFrame = 10,
    AckFrame = 11,
    BlockFrame = 12,
    FreeFrame = 13
} ControlFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    GetAddress = 10,
    AssignAddress = 11,
    RemoveAddress = 12
} ManagementFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    DataRequest = 10,
    DataResponse = 11,
} DataFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    SerialReady = 10,
    SerialSet = 11,
    SerialDone = 12
} SerialSubType;

/*
 * FrameType          : Three Type Of Frame 
 */
typedef enum {
    FrameCode = 0,
    FrameSA = 1,
    FrameDA = 2,
    FrameActiveCode = 3,
    FrameLength = 7,
    FrameDataIndex = 8,
} FrameIndex;

#if defined(USART0_ENABLED)
#define CH0_TRANSMIT_INTERRUPT    UART0_TRANSMIT_INTERRUPT
#define CH0_RECEIVE_INTERRUPT     UART0_RECEIVE_INTERRUPT

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartPutByte(uint8_t byte) {
    usart0PutByte(byte);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline uint8_t ch0_usartGetByteByte() {
    return usart0GetByte();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartEmptyBuffer >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartEmptyBuffer                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartEmptyBuffer() {
    while (!Empty_BUFFER0());
}

#elif defined  USART1_ENABLED
#define CH0_TRANSMIT_INTERRUPT    UART0_TRANSMIT_INTERRUPT
#define CH0_RECEIVE_INTERRUPT     UART0_RECEIVE_INTERRUPT

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartPutByte(uint8_t byte) {
    usart1PutByte(byte);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartPutByte >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartPutByte                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline uint8_t ch0_usartGetByteByte() {
    return usart1GetByte();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0_usartEmptyBuffer >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_usartEmptyBuffer                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static inline void ch0_usartEmptyBuffer() {
    while (!Empty_BUFFER1());
}
#endif


#include "csmaconfig.h"
#include "TransmitSystem.h"
#include "ReceiveCallBack.h"

#endif
#endif

#endif /*CSMA_H*/