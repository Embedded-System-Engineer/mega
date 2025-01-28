/* 
 * File:   dataTiming.h
 * Author: hassa
 *
 * Created on April 26, 2023, 7:47 AM
 */

#ifndef DATATIMING_H
#define	DATATIMING_H
#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimePlay>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimePlay                                                           |
 | < @Description         : flahing data Into buffer                                                    |   
 | < @Param swID          : Switch id  display data show                                                |
 | < @PAram RID           : room id display data show                                                   |
 | < @Param Period        : Time Required Ton and off display                                           |
 | < @Param  Toff         : off Time of the Display                                                     |
 | < @Param duration      : number of repeat counter                                                    |
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimePlay(uint16_t swID, uint16_t RID, uint16_t Period, uint16_t Ton, uint8_t duration);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeCallBack2>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeCallBack2                                                       |
 | < @Description         : run task in background                                                      |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeInit>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeInit                                                           |
 | < @Description         : init all data into this file                                                |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeReady>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeReady                                                          |
 | < @Description         : get status of the timing of the Data                                        |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t systemIsDateTimeReady();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeStop>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeStop                                                   |
 | < @Description         : stop running time                                                           |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
void systemDateTimeStop();
#endif	/* DATATIMING_H */

