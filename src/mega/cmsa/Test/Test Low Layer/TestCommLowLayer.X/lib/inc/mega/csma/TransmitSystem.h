/* 
 * File:   TransmitSystem.h
 * Author: Smart-H
 *
 * Created on 11 ????, 2023, 01:12 ?
 */

#ifndef TRANSMITSYSTEM_H
#define	TRANSMITSYSTEM_H
#include "csma.h"
#if defined CSMA_MODULE
#if CSMA_MODULE
/*
 * <@macro ACK tpye
 */
#define ACK_TYPE       (1)
/*
 * <@macro NACK tpye
 */
#define NACK_TYPE      (0)

/*
 * <@macro frame has error to no send
 */
#define ON_ERROR_FRAME       (0)

/*
 * <@macro fram is done To send 
 */
#define  ON_SUCCESS_FRAME     (1)

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaAckControlFrame >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaAckControlFrame                                                                                   | 
 | < @Description       : external action of the of frame                                                              |                                                                                   
 | < @Param Type        : system Have Ack Or Not 
 * | < @return          : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaAckControlFrame(uint8_t type);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTransmitCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTransmitCallBack                                                                                   | 
 | < @Description       : this function run in ISR of receive Byte                                                              |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaTransmitCallBack(uint8_t byte);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerTransmitCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerTransmitCallBack                                                                                   | 
 | < @Description       : this function run in every bit Rate to Transmitt Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaTimerTransmitCallBack();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < CsmaRequestNewFrame >                                                                  |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : uint16_t  CsmaRequestNewFrame                                                                |                 
 | < @Description            : Request New Frame To send Data                                                               |  
 | < @Param Code             : code of frame Type                                                                           |                                                                              
 | < @Param buffer           : buffer data to send                                                                          |
 | < @Param desAddress       : station address to receive this frame                                                        |
 | < @Param len              : number of byte used of this Frame                                                            |
 | < @Param FunOnFrameState  : Pointer to Frame Function State                                                              |
 * | < @return               : void                                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t CsmaRequestNewFrame(uint8_t Code, uint8_t *buffer, uint8_t desAddress, uint8_t len, pFuncParam_t FunOnFrameState);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTransmitReadCurrentFramePerfix >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTransmitReadCurrentFramePerfix                                                           | 
 | < @Description       : Read Frame Perfix data from  0 to data start                                                      |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaTransmitReadCurrentFramePerfix(uint8_t *Perfix);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaResetChannelAssignment >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaResetChannelAssignment                                                           | 
 | < @Description       : csma Reset Channel Assignment                                                     |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaResetChannelAssignment();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaResetSendState >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaResetSendState                                                           | 
 | < @Description       : get state of the send state and reset                                                     |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t csmaResetSendState();
/*
 ---------------------------------------------------------------------------------------------------------
 |                            < CRC-check   >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function           : void CRC-check                                                                |
 | < @Description        : CRC is based on polynomial function and divide this by polynomial             |
 |                       : for example the message  X^7+x^6+X^5+X^4+X^3+X^2+X+1 the is bit               |
 |                       : is 7 bit and divide this message by x^3 + X + 1                               |
 |                       : the quotient (Q) = X^4+X^3+1 and reminder is (R) =  X^2 + 1                   |
 |                       : result  polynomial message = Q*G + R                                          |
 |                       : the message contains m-bit message and number of bis and                      |
 |                       : check sum contains r-bit  mX^r =  Q*G + R  when G G should be of degree r     |
 |                       : The generator polynomial  x+1 creates a checksum of length 1, which           |
 |                       : applies even parity to the message                                            |
 |                       : G polynomial x^12 + x^11 +x^3+ x2 +x+ 1   with r = 12bit this function        |
 |                       : generate by this function  mX^r + R mod G = 0                                 |
 |                       : required function G polynomial  division circuit using shift                  |
 |                       : @example G = 1101  and mX = 100100000  divide mx/G and get R                  |
 |                       : 1/1 = 1 * 1101 = 1001-1101 = 1000 / 1101 = 1  .........etc                    |
 | < @Param crc          : Init value                                                                    |
 | < @Param data         : pointer to data checked                                                       | 
 | < @Param len          : length of the data check                                                      |
 | < @Referenc           : https://perswww.kuleuven.be/~u0068190/Onderwijs/Extra_info/crc.pdf            |                     
 | < @return             : void                                                                          |
 ---------------------------------------------------------------------------------------------------------
 */
 uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len);
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
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaSetChannelAssignment >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaSetChannelAssignment                                                           | 
 | < @Description       : csma set Channel Assignment                                                     |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaSetChannelAssignment();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < InitValues >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void InitValues                                                           | 
 | < @Description       : init all values                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void InitValuesTransmit();
#endif
#endif
#endif	/* TRANSMITSYSTEM_H */

