/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.h                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 22-Byte                                                                  |
| < PROGRAM USAGE            : 388 Byte  (0 Instruction)                                                |                                    
| < Hardware Usage           : External eeprom Modeule                                                  |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */
#include <mega.h>

#include "mega/_7seg.h"

/*Register som Function */

pst_7seg_t display1;
pst_7seg_t display2;


static const gpio_t pins1[] = {GPIO_B0, GPIO_A0, GPIO_A1, GPIO_A2};
static const gpio_t pins2[] = {GPIO_A3, GPIO_A4, GPIO_A5};


static stTimer_TimeOut_t gstTimeOut;

void appBoot(void) {

}

void appInit(void) {
    display1 = Create_7seg_Display(pins1, 4, 0);
    display2 = Create_7seg_Display(pins2, 3, 0);
    _7seg_Display_write_string(display1, "oFF", 1);
    _7seg_Display_write_string(display2, "oFF", 1);
    sysSetPeriodMS(&gstTimeOut, 1000);
}

void appSync(void) {

}

void appMain(void) {
    static uint8_t appState = 0;
    if (appState == 0) {
        if (sysIsTimeoutMs(&gstTimeOut) == 0) {
            _7seg_Display_write_string(display1, "   ", 1);
            appState = 1;
        }
    }


    if (appState == 1) {
        if (ssd_test_digit_app(display1, 500, false)) {
            _7seg_Display_write_string(display1, "oFF", 1);
            sysSetPeriodMS(&gstTimeOut, 1000);
            appState = 0;
        }
    }

}



