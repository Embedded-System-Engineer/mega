/* 
 * File:   ReceiveCallBack.h
 * Author: Smart-H
 *
 * Created on 11 ????, 2023, 04:10 ?
 */

#ifndef RECEIVECALLBACK_H
#define	RECEIVECALLBACK_H
#include "csma.h"
#if defined CSMA_MODULE
#if CSMA_MODULE
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerReceiverCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerReceiverCallBack                                                                                   | 
 | < @Description       : this function run in every bit Rate to Transmitt Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaTimerBlockallBack() ;
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < csmaTimerReceiverCallBack >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaTimerReceiverCallBack                                                                                   | 
 | < @Description       : this function run in every bit Rate to Transmitt Frame                                                               |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaTimerReceiverCallBack();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < InitValuesReceiver >                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void InitValuesReceiver                                                           | 
 | < @Description       : init all values                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void InitValuesReceiver();
#endif
#endif
#endif	/* RECEIVECALLBACK_H */

