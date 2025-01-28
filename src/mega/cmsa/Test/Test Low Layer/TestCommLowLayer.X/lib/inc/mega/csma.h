
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
#include "../mega.h"

#ifndef CSMA_H
#define	CSMA_H


#if defined CSMA_MODULE
#if CSMA_MODULE

/*
 * FrameSubType          : Data Frame
 */
typedef enum {
    RequestFrame = 3,
    ResponseFrame = 7,
} DataFrameSubType;

typedef uint8_t(*pFuncReceiveData_t)(uint8_t DA, uint8_t len,  uint8_t *Data);
typedef void (*pFuncPSaveSerail_t)(uint8_t *);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commTimerInit >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void commTimerInit                                                                                | 
 | < @Description       : configuration of timer 2 and External Interrupts                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaDriver >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriver                                                                |                                          
 | < @Description       : Handling Received Data                                                         |                                                              |                                                                                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
void csmaDriver();
#if NUMBER_OF_CHANNEL == 1
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0LoadData >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function                 : void ch0LoadData                                                         |                                          
 | < @Description              : load Data From app                                                       |                                                     |  
 | < @Param DeviceType         : Device worked as a client or server                                      |  
 | < @Param DeviceSerial     : serial number of the data                                                  |                                                 |
 | < @return                  : void                                                                      |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
void ch0LoadData(uint8_t DeviceType, time_t DeviceSerial);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameCh0(pFuncReceiveData_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnClientFrame  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnClientFrameV1                                                            |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnClientFrameCh0(pFuncReceiveData_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnSystemDownCh0  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnSystemDownCh0                                                            |
 | < @Description       : system have a fram error                                                    |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnSystemDownCh0(pAsyncFunc_t linkdownError);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_StationAddress  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_StationAddress()                                                          |
 | < @Description       : get Station Address                                                    |                    
 | < @return            : station address by channel 0                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_StationAddress();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_Free  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_Free()                                                            |
 | < @Description       : Free channel from block stage                                                 |                    
 | < @return            : 1 free channel is send ok  , 0 try Free Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_Free();

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_Block  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_Block()                                                            |
 | < @Description       : Block channel within Block Time (ms) Time                                      |                    
 | < @return            : 1 block channel is send ok  , 0 try block Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_Block();
#elif NUMBER_OF_CHANNEL == 2

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_Free  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_Free()                                                            |
 | < @Description       : Free channel from block stage                                                 |                    
 | < @return            : 1 free channel is send ok  , 0 try Free Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_Free();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_Block  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_Block()                                                            |
 | < @Description       : Block channel within Block Time (ms) Time                                      |                    
 | < @return            : 1 block channel is send ok  , 0 try block Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_Block();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_Free  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_Free()                                                            |
 | < @Description       : Free channel from block stage                                                 |                    
 | < @return            : 1 free channel is send ok  , 0 try Free Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch1_Free();

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch1_Block  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch1_Block()                                                            |
 | < @Description       : Block channel within Block Time (ms) Time                                      |                    
 | < @return            : 1 block channel is send ok  , 0 try block Channle                                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch1_Block();

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch0_StationAddress  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch0_StationAddress()                                                          |
 | < @Description       : get Station Address                                                    |                    
 | < @return            : station address by channel 0                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch0_StationAddress();

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < ch1_StationAddress  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ch1_StationAddress()                                                          |
 | < @Description       : get Station Address                                                    |                    
 | < @return            : station address by channel 1                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t ch1_StationAddress();
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameCh0(pFuncReceiveData_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnClientFrame  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnClientFrameV1                                                            |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnClientFrameCh0(pFuncReceiveData_t receiveFrame);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch0LoadData >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function                 : void ch0LoadData                                                         |                                          
 | < @Description              : load Data From app                                                       |                                                     |  
 | < @Param DeviceType         : Device worked as a client or server                                      |  
 | < @Param DeviceSerial     : serial number of the data                                                  |                                                 |
 | < @return                  : void                                                                      |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
void ch0LoadData(uint8_t DeviceType, time_t DeviceSerial);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ch1LoadData >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function                 : void ch1LoadData                                                         |                                          
 | < @Description              : load Data From app                                                       |                                                     |  
 | < @Param DeviceType         : Device worked as a client or server                                      |  
 | < @Param DeviceSerial     : serial number of the data                                                  |                                                 |
 | < @return                  : void                                                                      |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
void ch1LoadData(uint8_t DeviceType, time_t DeviceSerial);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameCh1(pFuncReceiveData_t receiveFrame);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnClientFrame  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnClientFrameV1                                                            |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnClientFrameCh1(pFuncReceiveData_t receiveFrame);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh1(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnSystemDownCh0  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnSystemDownCh0                                                            |
 | < @Description       : system have a fram error                                                    |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnSystemDownCh0(pAsyncFunc_t linkdownError);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnSystemDownCh1  >                                                       |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnSystemDownCh1                                                            |
 | < @Description       : system have a fram error                                                    |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnSystemDownCh1(pAsyncFunc_t linkdownError);
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaSaveSerialRegister >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function                 : void csmaSaveSerialRegister                                                         |                                          
 | < @Description              : save serial call back function                                                      |                                                     |  
 | < @Param x                  : Pointer to function                                     |                                                  |                                                 |
 | < @return                  : void                                                                      |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
void csmaSaveSerialRegister(pFuncPSaveSerail_t x);
#endif
#endif

#endif /*CSMA_H*/