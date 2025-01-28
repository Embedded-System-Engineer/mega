/* 
 * File:   csmaconfig.h
 * Author: Smart-H
 *
 * Created on 11 ????, 2023, 08:20 ?
 */

#ifndef CSMACONFIG_H
#define	CSMACONFIG_H
#include "csma.h"

#if defined CSMA_MODULE
#if CSMA_MODULE




/*
 ----------------------------------------------------------------------------------------------------------------
 |                  Timer Worked                                                                                |
 ----------------------------------------------------------------------------------------------------------------
 | <                                                                                                            |
 | 1- sync timer with first bit received by interrupt request the sync by reset value in                        |
 |   timer by 0 and start timer to increment bit rate after byte received (reset timer to zero and set value    |
 |   with frame parsing if any in this case mesurement the frame time and lastbyte receive Time                 |
 |  can mesurement buadrate (wire speed and detect any error between acual buadrate and design buadrate)        |
 |  T required = n  * Timer Time  ==  Frequency of Timer  = n *   Frequency Required                            |
 |  n= Frequency of Timer / Frequency Required                                                                  |      
 |  the parsing frame start after Last byte Received(TP) = xByteTime + y BitTime = (x/ByteRate) + (y/BitRate)   |
 | the bit Rate = nBit * Byte Rate == nBit is number of bit per Byte                                            |
 | TP =(nBit*x/BitRate)+(y/BitRate) = (nBit*x+y) / (BitRate)                                                    |
 | FP = 1/TP = (BitRate/(nBit*x+y)) the any Time Required when x is number of byte and y number of bit          |                                                                     
 | when the nBit Per Byte is 10 Bit and x =1 and  y = 2 BitRate = Baud rate = 19200 bps                         |
 | FP = (19200/(10*1+2)) = 1600bps == TP = 625usec =  xByteTime + y BitTime = 1*520.8+2*52.08=624.96us          |                          
 | @note 1 when any Required Time by Timer 2 from any Channel 0 or 1 can apply this eq n=(nBit*x)+y             |
 | @note 2 baud rate error detect from first start Bit enable to start BitCounte increment every Time2interrupt |
 | Frame n = has 10Byte*10Bit = 100Bit and Timer Frequency is 19200 Hz , nCount = 100 Count or nCount = 50      |
 | Frequency Required  =(BitRate/(nBit*x+y)) when nBit*x+y = number of Bit                                      |
 | Frequency Required  = 192 and nCount is 100 Count                                                            |
 | Frequency of Timer  = n *  192  = 100*192 = 19200 or 50*192 = 9600                                           |
 | when count is 50 the buad rate worked is 9600 and when count is 100 the buadrate is worked is 19200          |
 | main Function to Generate any Time  n =(nBit*x)+y when (nBit*x)+y = number of bits when x is channel number  |
 | nFrameParsingChx =   (10Bit * 1Byte)+0Bit = 10Bit time is 12*52.08us = 520.8us                               |
 | nFrameMasterBus = (10Bit*1Byte)+2Bit = 12Bit time is 12*52.08us = 624.96us                                   |
 | nFrameSlaveBus  = (10Bit*1Byte)+3Bit = 13Bit time is 677.04us when x is channel number                       |                                                                                                                      
 | Back off Time = (CW min/ sqr(Cwmax)) * CW * slot time and  slot time is 4usec,Cw min = 32 , Cw max = 1024    |
 | when CW (Contention Window) based on the number of the frame which is sent successfully                      |                                   |
 | When we have many nodes using the medium, we require small value of Back off therhlod relative to current    |
 | CW size to reduce collisionsand when we have few nodes using the medium, we require high value of backoff    |
 | to current CW size to fast collision resolution                                                              |
 | when Cw = Cw min BackOff Time is 64us and Cw = 128us and Cw = Cw max = 1024 the Bacoff time = 4096us         |                                                         
 | @case 1  the Time is   128us  + 677 us = 15 *52.08=781us                                                     |
 | @case 2  the time is  4096us  +677 us  = 92*52.08 = 4860us                                                   |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 * < @macro BIT_TIME                        : Bit time 
 */
#define  BIT_TIME                              (1000000UL/UART0_BUADRATE)/*52 us*/
/*
 * < @macro N_BITs  (nBit,x,y)              :  (nBit*x)+y   x = number of byte and y = number of bit , nBit number of bit in byte
 */
#define  N_BITs(nBit,x,y)                     (nBit*x)+y 
/*
 * < @macro  PCC(Ni,Nb,Nc,Ns)              : probability of the collision at transmission Frame 
 */
#define   PCC(Ni,Nb,Nc,Ns)                  (((Nb+Nc+Ns)/(Ni+Nb+Nc+Ns)) * Nc)
/*
 *< @macro       RIFS                       : Redused Inter-Frame Spacing Time 
 */
#define         RIFS                          N_BITs(10,1,0)/*wait for one byte received*/
/*
 *< @macro nFrameSlaveBus                    : Distrbuited Inter-Frame Spacing Time
 */
#define         DIFS                         N_BITs(10,3,0)/*wait for three byte received*/
/*
 * < @macro     SIFS                         : Shorter Inter-Farme Spacing Time 
 */
#define         SIFS                          N_BITs(10,2,0)/*wait for two byte received*/
/*
 * < @macro  ACKO                           : Ack time out Received 
 */
#define         ACKO                            N_BITs(10,STATION_BLOCK_TIME,0) /*416 us*/       
/*
 * < @macro     BIFS                        : Block Inter-Frame Space
 */
#define         BIFS                          N_BITs(10,STATION_BLOCK_TIME,0) /*416 us*/
/*
 * < @macro     SNIFS                        : Serial Number Inter-Frame Space
 */
#define         SNIFS                          N_BITs(10,STATION_SERIAL_TIME,0) /*416 us*/
/*
 *< @macro CW_MIN                            : min value of  Contention Window              
 */
#define CW_MIN                                      2
/*
 * @macro CW_MAX                             : max value of  Contention Window min 22us and max 1024us
 */
#define CW_MAX                                     128 
#ifndef    STATION_BLOCK_TIME 
#define    STATION_BLOCK_TIME                              (50) 
#endif

#ifndef    COM_MAX_RETARY
#define    COM_MAX_RETARY                                  (10)
#endif

#ifndef   COM_PAYLOAD_SIZE                                 
#define   COM_PAYLOAD_SIZE                                 (10)
#endif
#ifndef  STATION_ASSIGN_ADDRESS
#define  STATION_ASSIGN_ADDRESS                            (0)
#endif
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaConfig >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaConfig                                                                                | 
 | < @Description       : configuration of timer 2 and External Interrupts                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaConfig();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < getActiveCode>                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void getActiveCode                                                                          | 
 | < @Description            : get Active Code Of The System                                                                   |                                                                                   
 | < @return                 : void                                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 */
time_t getActiveCode();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < getServerType>                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function               : void getServerType                                                                          | 
 | < @Description            : system is client or server                                                               |                                                                                   
 | < @return                 : void                                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t getServerType();
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
#endif
#endif
#endif	/* CSMACONFIG_H */

