/*
 ----------------------------------------------------------------------------------------------------------------------------
|                          < Module  Definition >                                                                           | 
 ----------------------------------------------------------------------------------------------------------------------------
| < FILE                   : system.h                                                                                      |                                  
| < Author                 : overflow problem solutions created by eng /Ahmed Saied and implementation by Hassan Elsaied    | 
| < Version                : Mega2v241022                                                                                   |
| < References             : no-used references in this documents                                                           |
| < SRAM_USAGE             : 17 Byte                                                                                        |
| < PROGRAM_USAGE          : 552 byte (347 Instruction)                                                                     |
| < Hardware Usage         : Timer 0                                                                                        |
| < File Created           : 24-10-2022                                                                                     |
-----------------------------------------------------------------------------------------------------------------------------
 */
#ifndef XC_SYS_H
#define	XC_SYS_H


#include "../mega.h"


/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < Macro Definition>                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 */
#define      SYSTEM_WAKE_UP    (0xFF)
/*
 -----------------------------------------------------------------------------------------------------------------
 |                          < Micro  Definition >                                                                |  
 -----------------------------------------------------------------------------------------------------------------
 | < marco SECS_PER_MIN          : one minute have a 60 second                                                   |
 | < marco RTC_BASE_TIME         : system start count from 2000                                                  |
 | < marco SECS_PER_HOUR         : one hour have a 60 min and one min have a 60 second one hour = 60*60 second   |
 | < marco DAY_PER_WEEK          : on week have a 7 day                                                          |
 | < marco SECS_PER_DAY          : one day have a 24 hour and one hour = 60*60 ==>one day = 24*60*60             |
 -----------------------------------------------------------------------------------------------------------------
 */


#define 	SECS_PER_MIN                  (60UL)
#define     RTC_BASE_TIME                 (2000UL)
#define 	SECS_PER_HOUR                 (3600UL)
#define 	DAY_PER_WEEK                  (7)
#define     SECS_PER_DAY                 ((SECS_PER_HOUR) * (24UL))

typedef struct {
    uint32_t Timer;
    uint32_t Period;
}
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                <  timer Access   >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < Description          : perodic timer struct                                                                            |
 | < Uasge                : 8 Byte                                                                                          |
 | < param Chip           : is a store current Time                                                                         |
 | < param address        : store difference time between current time and  time to be arriver                              |             
 ----------------------------------------------------------------------------------------------------------------------------
 */
stTimer_t;

typedef struct {
    uint32_t EndTime;
}
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                <  timer out   >                                                                          |
 ----------------------------------------------------------------------------------------------------------------------------
 | < Description          : time out struct                                                                                 |
 | < Uasge                : 4 Byte                                                                                          |
 | < param EndTime        : save a next time to generate event when arriver                                                 |             
 ----------------------------------------------------------------------------------------------------------------------------
 */
stTimer_TimeOut_t;
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                <  Functions Declarations    >                                                            |
 ----------------------------------------------------------------------------------------------------------------------------
 */
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemSleep >                                                                          | 
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void systemSleep                                                                                  | 
 | < @Description       : set system in sleep mode                                                                          |
 | < @Param Type     : Sleep mode stop or any select one of type sleep mode                   :                             |                                                                          |                                                                              
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
 void systemSleep(uint8_t Type);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < startHwTimer0 >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void startHwTimer0                                                                                | 
 | < @Description       : enable timer interrupt and general interrupt                                                      |                                                                 |                    
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
 void startHwTimer0();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < stopHwTimer0 >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void stopHwTimer0                                                                                 | 
 | < @Description       : disable timer interrupt and general interrupt is call this function the any driver  based general |
 |                      : interrupt  is not working after execution this function.                                          |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void stopHwTimer0();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysSetPeriodUs >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysSetPeriodUs                                                                               | 
 | < @Description       : set period micro in the software timer                                                            |
 | < @Param psTimer     : pointer of time out Timer                    :                                                    |
 | < @Param Period      : period required y microsecond                                                                     |                                                                              
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
 void sysSetPeriodUs(stTimer_TimeOut_t *psTimer, micros_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysSetPeriodMs >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysSetPeriodMs                                                                               | 
 | < @Description       : set period ms in the software timer                                                            |
 | < @Param psTimer     : pointer of time out Timer                    :                                                    |
 | < @Param Period      : period required y ms                                                                              |                                                                              
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
 void sysSetPeriodMS(stTimer_TimeOut_t * psTimer, millis_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysSetPeriodS >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysSetPeriodS                                                                                | 
 | < @Description       : set period seconds in the software timer                                                          |
 | < @Param psTimer     : pointer of time out Timer                    :                                                    |
 | < @Param Period      : period required y seconds                                                                         |                                                                              
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
 void sysSetPeriodS(stTimer_TimeOut_t * psTimer, time_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemInit >                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerInitUS                                                                               | 
 | < @Description       : initialization all variables in this modules with default value                                   |                                
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */

void systemInit();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerInitUS >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerInitUS                                                                               | 
 | < @Description       : Periodic timer initialization by period and current time and delay before start period            |
 |                      : when generate an event every 10us the the inti current micro second assignment into software time |
 |                      : in time value and assignment period (10us ) into period value after delay can be start task       |
 | < @Param psTimer     : pointer of software Timer                                                                         | 
 | < @Param Delay       : value of delay (task can be start after this dealy in first run by micro seconds                  |  
 | < @Param Period      : task run every this value  by micro seconds                                                       |                                     
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerInitUs(stTimer_t *psTimer, micros_t Delay, micros_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerInitMS >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerInitMS                                                                               | 
 | < @Description       : Periodic timer initialization by period and current time and delay before start period            |
 |                      : when generate an event every 1ms the the inti current milli seconds assignment into software time |
 |                      : in time value and assignment period (1 ms ) into period value after delay can be start task       |
 | < @Param psTimer     : pointer of software Timer                                                                         | 
 | < @Param Delay       : value of delay (task can be start after this dealy in first run by milli seconds                  |  
 | < @Param Period      : task run every this value  by milli seconds                                                       |                                     
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerInitMS(stTimer_t *psTimer, millis_t Delay, millis_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerInitS >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerInitS                                                                                | 
 | < @Description       : Periodic timer initialization by period and current time and delay before start period            |
 |                      : when generate an event every 1sec the the inti current seconds assignment into software time      |
 |                      : in time value and assignment period (1 second ) into period value after delay can be start task   |
 | < @Param psTimer     : pointer of software Timer                                                                         | 
 | < @Param Delay       : value of delay (task can be start after this dealy in first run   run by  seconds                 |  
 | < @Param Period      : task run every this value by seconds                                                              |                                     
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerInitS(stTimer_t *psTimer, time_t Delay, time_t Period);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysIsTimeoutUS >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysIsTimeoutUS                                                                            | 
 | < @Description       : check of the period is expired or not by compared micro secomds system and timer stored value     |
 |                      : the time out is return  after expired micro second period                                         |
 | < @Param psTimer     : pointer of time out Timer                                                                         |                                                                             
 | < @return            : 0 when timer does expired period                                                                  |
 |                      : 1 when timer doesn't expired period                                                                    |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysIsTimeoutUs(stTimer_TimeOut_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysIsTimeoutMS >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysIsTimeoutMS                                                                            | 
 | < @Description       : check of the period is expired or not by compared milli secomds system and timer stored value     |
 |                      : the time out is return  after expired milli second period                                         |
 | < @Param psTimer     : pointer of time out Timer                                                                         |                                                                             
 | < @return            : 0 when timer does expired period                                                                  |
 |                      : 1 when timer doesn't expired period                                                                   |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysIsTimeoutMs(stTimer_TimeOut_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysIsTimeoutS >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysIsTimeoutS                                                                             | 
 | < @Description       : check of the period is expired or not by compared second system and timer stored value            |
 |                      : the time out is return  after expired second period                                               |
 | < @Param psTimer     : pointer of time out Timer                                                                         |                                                                             
 | < @return            : 0 when timer does expired period                                                                  |
 |                      : 1 when timer doesn't expired period                                                                    |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysIsTimeoutS(stTimer_TimeOut_t *psTimer);

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < setupHwTimer0 >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void setupHwTimer0                                                                                | 
 | < @Description       : configuration of timer 0                                                                          |                                                                 |                    
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void setupHwTimer0();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerResetUS>                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerResetUS                                                                              | 
 | < @Description       : periodic timer is restart micro seconds                                                           |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerResetUS(stTimer_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerResetMS>                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerResetMS                                                                              | 
 | < @Description       : periodic timer is restart milli seconds                                                           |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerResetMS(stTimer_t *psTimer);

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerResetS>                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysTimerResetS                                                                               | 
 | < @Description       : periodic timer is restart seconds                                                                 |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysTimerResetS(stTimer_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerCheckUs>                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysTimerCheckUs                                                                           | 
 | < @Description       : periodic timer is restart with us                                                                 |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : 0 when the periodic period is done and restart the next period by same value                      |
 |                      : 1 when timer doesn't  expired current period                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysTimerCheckUs(stTimer_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerCheckMS>                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysTimerCheckMs                                                                           | 
 | < @Description       : periodic timer is restart with ms                                                                 |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : 0 when the periodic period is done and restart the next period by same value                      |
 |                      : 1 when timer doesn't  expired current period                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysTimerCheckMs(stTimer_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysTimerCheckS >                                                                       |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t sysTimerCheckS                                                                            | 
 | < @Description       : periodic timer is restart with second                                                             |
 | < @Param psTimer     : pointer of software Timer                                                                         |                                                                             
 | < @return            : 0 when the periodic period is done and restart the next period by same value                      |
 |                      : 1 when timer doesn't  expired current period                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t sysTimerCheckS(stTimer_t *psTimer);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < sysUpdateNow >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void sysUpdateNow                                                                                 |  
 | < @Description       : set current timestamp from external sources for example                                           |  
 | < @Param now         : up date no from computer or RTC module or network                                                 |                    
 | < @return            : number of milli seconds                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void sysUpdateNow(time_t now);
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemMillis >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : millis_t systemMillis                                                                             |  
 | < @Description       : current time by milli seconds                                                                     |                                                                 |                    
 | < @return            : number of milli seconds                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 */

millis_t systemMillis();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemMicros >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : micros_t systemMicros                                                                             |  
 | < @Description       : current time by micro seconds                                                                     |                                                                 |                    
 | < @return            : number of micro seconds                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 */
micros_t systemMicros();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemNow >                                                                            |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : time_t systemNow                                                                                  |  
 | < @Description       : current time by seconds                                                                           |                                                                 |                    
 | < @return            : number of seconds                                                                                 |
 ----------------------------------------------------------------------------------------------------------------------------
 */
time_t systemNow();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemSecondEvent >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : millis_t systemSecondEvent                                                                             |  
 | < @Description       : system Have a new Second                                                                    |                                                                 |                    
 | < @return            : 1 System Have Second , 0 System at same Secod                                                                           |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t systemSecondEvent();

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                <   inlineFunctions Implementations    >                                                  |
 ----------------------------------------------------------------------------------------------------------------------------
 */
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < ClearsystemSecondEvent >                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void systemSecondEvent                                                                             |  
 | < @Description       : forced system Have a new Second                                                                    |                                                                 |                    
 | < @return            :                                                                         |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void ClearsystemSecondEvent();
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < systemReadHalfSecond >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void systemReadHalfSecond                                                                                | 
 | < @Description       : get Half Event Value                                                                         |                                                                 |                    
 | < @return            : 0 or 1 (second Period)                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t systemReadHalfSecond();

#endif	/* XC_SYS_H */

