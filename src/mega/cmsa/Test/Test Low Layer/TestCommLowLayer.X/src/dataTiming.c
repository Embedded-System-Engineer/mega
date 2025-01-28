#include "../inc/appRes.h"

typedef union {
    uint8_t flags;

    struct {
        unsigned duration : 6;
        unsigned state : 1;
        unsigned toggle : 1;
    };
} utDataTimeFlags_t;

/*
 <@var Time of show Data on display
 */
static uint16_t gu16Period[2];
/*
 <@var number of repeat Period
 */
static utDataTimeFlags_t gutDataTimeFlags;
/*
 <@var Data of main Display
 */
static uint8_t gu8MainDisplay[5];
/*
 <@var Data of main Display
 */
static uint8_t gu8ExDisplay[5];
/*
 * <@var time traget is done
 */
static stTimer_TimeOut_t gstFrequncy;
/*
 * <@var start index if  main display
 */
static uint8_t gu8startIndexMain;
/*
 *  start index if  extention display
 */
static uint8_t gu8startIndexEx;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onWriteInMainDisplay>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onWriteInMainDisplay                                                   |
 | < @Description         : write value in main display                                                 |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static inline void onWriteInMainDisplay();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onWriteInExDisplay>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onWriteInExDisplay                                                   |
 | < @Description         : write value in extention display                                          |      
 | < @return              : void                                                                      |          
 --------------------------------------------------------------------------------------------------------
 */
static inline void onWriteInExDisplay();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnWriteDisplay>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnWriteDisplay                                                         |
 | < @Description         : write all IDs in Display disp  lay                                          |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnWriteDisplay();

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
void DataTimePlay(uint16_t swID, uint16_t RID, uint16_t Period, uint16_t Ton, uint8_t duration) {
    gu16Period[0] = Ton;
    gu16Period[1] = Period - Ton;
    gutDataTimeFlags.duration = duration;
    gutDataTimeFlags.state = 1;
    if (getMainView()) {
        gu8startIndexMain = u16ToBCD(gu8MainDisplay, swID);
        gu8startIndexEx = u16ToBCD(gu8ExDisplay, RID);
    } else {
        gu8startIndexMain = u16ToBCD(gu8MainDisplay, RID);
        gu8startIndexEx = u16ToBCD(gu8ExDisplay, swID);
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeCallBack>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeCallBack                                                       |
 | < @Description         : run task in background                                                      |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeCallBack() {
    if (!gutDataTimeFlags.state) {
        return;
    }
    if (sysIsTimeoutMs(&gstFrequncy) == 0) {
        if (gutDataTimeFlags.toggle == 0) {
            if (gutDataTimeFlags.duration == 0) {
                gutDataTimeFlags.flags = 0;
                ssdclearALL();
                return;
            }
            gutDataTimeFlags.duration--;
        }

        sysSetPeriodMS(&gstFrequncy, gu16Period[gutDataTimeFlags.toggle]);
        gutDataTimeFlags.toggle ^= 1;
        if (gu16Period[0] != 0) {
            if (gutDataTimeFlags.toggle) {
                /*ton*/
                OnWriteDisplay();
            } else {
                /*toff*/
                ssdclearALL();
            }
        } else {
            OnWriteDisplay();
        }
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <DataTimeInit>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void DataTimeInit                                                           |
 | < @Description         : init all data into this file                                                |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void DataTimeInit() {
    setBuff(gu8MainDisplay, 0x00, DISPLAY_MAX_MAIN_DIGIT);
    setBuff(gu8ExDisplay, 0x00, DISPLAY_MAX_EX_DIGIT);
    gutDataTimeFlags.flags = 0x00;
    setBuff(gu16Period, 0x00, 4);


}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onWriteInMainDisplay>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onWriteInMainDisplay                                                   |
 | < @Description         : write value in main display                                                 |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static inline void onWriteInMainDisplay() {
    uint8_t len = 1;
    if (MatchBufWithValue(gu8MainDisplay, 5, 0x00) == 0) {
        if (5 - gu8startIndexMain > getMainMaxDigit()) {
            return;
        }
        len = 5 - gu8startIndexMain;
    }

    ssdPrint(gu8MainDisplay, gu8startIndexMain, (SSD_MAX_DIGIT - getMainMaxDigit()), len);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <onWriteInExDisplay>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void onWriteInExDisplay                                                   |
 | < @Description         : write value in extention display                                          |      
 | < @return              : void                                                                      |          
 --------------------------------------------------------------------------------------------------------
 */
static inline void onWriteInExDisplay() {
    uint8_t len = 1;
    if (MatchBufWithValue(gu8ExDisplay, 5, 0x00) == 0) {
        if (5 - gu8startIndexEx > getExMaxDigit()) {
            return;
        }
        len = 5 - gu8startIndexEx;
    }
    ssdPrint(gu8ExDisplay, gu8startIndexEx, (SSD_MAX_DIGIT - DISPLAY_MAX_MAIN_DIGIT - getExMaxDigit()), len);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnWriteDisplay>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnWriteDisplay                                                         |
 | < @Description         : write all IDs in Display disp  lay                                          |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnWriteDisplay() {
    onWriteInMainDisplay();
    onWriteInExDisplay();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeReady>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeReady                                                          |
 | < @Description         : get status of the timing of the Data                                        |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t systemIsDateTimeReady() {
    return gutDataTimeFlags.state;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <systemIsDateTimeStop>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void systemIsDateTimeStop                                                   |
 | < @Description         : stop running time                                                           |      
 | < @return              : 0 done , 1 is busy                                                          |          
 --------------------------------------------------------------------------------------------------------
 */
void systemDateTimeStop() {
    setBuff(gu16Period, 0x00, 4); /*Reset Period*/
    gutDataTimeFlags.flags = 0x00; /*Reset all Data*/
}