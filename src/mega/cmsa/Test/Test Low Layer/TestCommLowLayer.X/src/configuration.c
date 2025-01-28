#include "../inc/appRes.h"
/*
 * < @macro APP_START : start of the application       
 */
#define  BOOT_START      asm("JMP 0x3E00")
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Variables>                                                       |
 --------------------------------------------------------------------------------------------------------
 */
/*
 *<@var : Board Info and configuration var
 */
static boardinfo_t gstboardInfo __attribute__((address(BoardInfoAddress)));

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Internal function Definitions>                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveSerial>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveSerial                                                           |
 | < @Description         : save serial number On boot section this function reboot system              |   
 | < @return              : void                                                     |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnSaveSerial(uint8_t *buf);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveConfiguration>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveConfiguration                                                    |
 | < @Description         : save configuartion On boot section this function reboot system              |   
 | < @return              : void                                                                         |          
 --------------------------------------------------------------------------------------------------------
 */
void OnSaveConfiguration(uint8_t *buf);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 <Internal function >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveSerial>                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveSerial                                                           |
 | < @Description         : save serial number On boot section this function reboot system              |   
 | < @return              : void                                                     |          
 --------------------------------------------------------------------------------------------------------
 */
static void OnSaveSerial(uint8_t *buf) {
    copyBuff(&gstboardInfo.SystemSerial, buf, sizeof (SystemSerial_t));
    gstboardInfo.State = 1;
    BOOT_START;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getBuzzerState>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getBuzzerState                                                         |
 | < @Description         : get State of the buzzer on Or off                                           |   
 | < @return              : 0 is off and  1 is on                                                       |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getDangdongState() {
    return gstboardInfo.SystemConfig.Option.dangdongState;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getMainView>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getMainView                                                            |
 | < @Description         : get system show switch id in main and room id in ex                         |   
 | < @return              : 0 is sytem show switch is in main , 1 system show room id in main           |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getMainView() {
    return gstboardInfo.SystemConfig.Option.MainView;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getBuzzerTimeFactor>                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getBuzzerTimeFactor                                                    |
 | < @Description         : get max value of actor to run buzzer                                        |   
 | < @return              :max number of Time Factor 0 To 255                                           |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getMainMaxDigit() {
    return gstboardInfo.SystemConfig.Option.MAX_MAIN_DIGIT;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getExMaxDigit>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getExMaxDigit                                                          |
 | < @Description         : get max extention digit                                                     |   
 | < @return              :max number of Time Factor 0 To 255                                           |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getExMaxDigit() {
    return gstboardInfo.SystemConfig.Option.MAX_EX_DIGIT;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getDisplayScollerTimePerms>                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getDisplayScollerTimePerms                                              |
 | < @Description         : getDisplayScollerTimePerms                                                   |   
 | < @return              : time per ms                                                                  |          
 --------------------------------------------------------------------------------------------------------
 */
time_t getDisplayScollerTimePerms() {
    return (time_t) (gstboardInfo.SystemConfig.DisplayScollerTimePerSec * 1000);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <ConfigurationInit>                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void ConfigurationInit                                                      |
 | < @Description         : get Init all data in this File                                              |   
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
void ConfigurationInit() {
    digitalpinMode(GPIO_B2 , MODE_INPUT_PULLUP);
    digitalpinMode(GPIO_B3 , MODE_INPUT_PULLUP);
    if (gstboardInfo.SystemConfig.Option.MAX_MAIN_DIGIT == 0) {
        gstboardInfo.SystemConfig.Option.MAX_MAIN_DIGIT = 3;
    }
    if (gstboardInfo.SystemConfig.Option.MAX_EX_DIGIT == 0) {
        gstboardInfo.SystemConfig.Option.MAX_EX_DIGIT = 2;
    }
    uint8_t x = digitalPinRead(GPIO_B2);
    uint8_t y = digitalPinRead(GPIO_B3);
    if (!y && !x) {
        gstboardInfo.SystemSerial.Time = 0x3D2F4C5B;
        gstboardInfo.SystemSerial.CH0 = 1;
    } else if (y && !x) {
        gstboardInfo.SystemSerial.Time = 0x4E3B5D6C;
        gstboardInfo.SystemSerial.CH0 = 0;
    } else if (!y && x) {
        gstboardInfo.SystemSerial.CH0 = 0;
        gstboardInfo.SystemSerial.Time = 0x5F4C6E7D;
    }else {
    gstboardInfo.SystemSerial.CH0 = 0;
        gstboardInfo.SystemSerial.Time = 0x23111996;
    }

    // csmaSaveSerialRegister(OnSaveSerial);
    csmaloadConfig(gstboardInfo.SystemSerial.CH0, gstboardInfo.SystemSerial.Time);


}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <OnSaveConfiguration>                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void OnSaveConfiguration                                                    |
 | < @Description         : save configuartion On boot section this function reboot system              |   
 | < @return              : 0 is off and  1 is on                                                       |          
 --------------------------------------------------------------------------------------------------------
 */
void OnSaveConfiguration(uint8_t *buf) {
    copyBuff(&gstboardInfo.SystemConfig, buf, sizeof (SystemConfig_t));
    gstboardInfo.State = 1;
    BOOT_START;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <noSerial>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void noSerial                                                               |
 | < @Description         : system have serial or not                                                   |   
 | < @return              : 0 is not have a serial and  1 system have a serial                          |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemIsSerial() {
    if (gstboardInfo.SystemSerial.Time == 0) {
        return (0);
    }
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <SystemIp>                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : uint8_t SystemIp                                                             |
 | < @Description         : get system ip                                                                |   
 | < @return              : void                                                                         |          
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemIp() {
    return gstboardInfo.SystemConfig.DISPLAYID;
}