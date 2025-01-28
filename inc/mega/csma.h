
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
#define DATA_FRAME_SUCESS (1)
#define DATA_FRAME_ERROR  (2)
/*
 * FrameSubType          : Data Frame
 */
typedef enum {
    RequestFrame = 10,
    ResponseFrame = 11,
} DataFrameSubType;

typedef uint8_t(*pFuncReceiveData_t)(uint8_t SA,uint8_t DA, uint8_t len, uint8_t *Data);
typedef void (*pFuncPSaveSerail_t)(uint8_t *);

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < OnHostFrame  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void OnHostFrameV1                                                              |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void OnHostFrameCh0(pFuncReceiveData_t receiveFrame) ;

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


/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendFreeFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendFreeFrame                                                                                   | 
 | < @Description       : send Free Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sendFreeFrame();

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sendBlockFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sendBlockFrame                                                                                   | 
 | < @Description       : send Block Frame                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sendBlockFrame();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaGetStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaGetStationAddress                                                           | 
 | < @Description       : get value of the address                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t csmaGetStationAddress();

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
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type) ;

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaloadConfig >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void csmaloadConfig                                                                          | 
 | < @Description            : load system configuration                                                                    |                                                                                   
 | < @Param serverType       : 0 the deviceType is cleint , 1 is server 
 | < @Param  ActivationCode  : code of device 
 *  | < @return              : void                                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaloadConfig(uint8_t serverType, time_t ActivationCode);

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
void csmaSaveSerialRegister(pFuncPSaveSerail_t x) ;
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaGetMaxAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaGetMaxAddress                                                           | 
 | < @Description       : return max assignment address                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t csmaGetMaxAddress();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInitStationIp(uint8_t Ip);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
------------------------------------------------------------------------------------------------------------
 */
void csmaInitStationAddress(uint8_t address);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaInitStationAddress >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaInitStationAddress                                                           | 
 | < @Description       : load last address after reboot                                              |                                                                                   
 | < @return            : void                                                                                              |
------------------------------------------------------------------------------------------------------------
 */
void clearCurrentDataFrame();
#endif
#endif
#endif /*CSMA_H*/