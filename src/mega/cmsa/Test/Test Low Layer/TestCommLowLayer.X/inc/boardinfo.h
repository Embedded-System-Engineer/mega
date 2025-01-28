/* 
 * File:   boardinfo.h
 * Author: hassa
 *
 * Created on April 11, 2023, 7:42 PM
 */

#ifndef BOARDINFO_H
#define	BOARDINFO_H



#define BoardInfoAddress            0x069
#define NUMBER_OF_DISPLAY_SUPPORT   (4)

typedef union {
    uint8_t Options;

    struct {
        unsigned MainView : 1;
        unsigned dangdongState : 1;
        unsigned MAX_MAIN_DIGIT : 3;
        unsigned MAX_EX_DIGIT : 2;
    };
} CallPointOptions_t;

typedef struct SystemSerial_s {
    time_t Time;
    uint8_t Code;
    uint8_t PatchNumber;
    uint16_t PrintCode;
    uint8_t CH0;
    uint8_t CH1;
} SystemSerial_t;

typedef struct SystemConfig_s {
    uint8_t DISPLAYID;
    uint8_t DisplayScollerTimePerSec;
    CallPointOptions_t Option;
} SystemConfig_t;

typedef struct bordinfo_s {
    uint8_t State;
    SystemSerial_t SystemSerial;
    SystemConfig_t SystemConfig;
} boardinfo_t;



#endif	/* BOARDINFO_H */

