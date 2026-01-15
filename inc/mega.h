/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : mega.h                                                            |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef XC_MEGA_H
#define	XC_MEGA_H
//#include <xc.h> /*xc compiler*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "mega/clock.h"
#include "mega/mainTones.h"
#include "mega/buffers.h"
#include "mega/utility.h"
#include "resource.h"
#include "mega/macros.h"
#include "mega/bootloadercmd.h"
#include "mega/types.h"


#include <stdint-gcc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

/* Standardized APIs - New Structure */
#include "../src/mega/gpio/inc/gpio_api.h"
#include "../src/mega/system/inc/system_api.h"
#include "../src/mega/system/inc/scheduler_api.h"
#include "../src/mega/usart/inc/usart_api.h"
#include "../src/mega/lcd/inc/lcd_api.h"
#include "../src/mega/twi/inc/twi_api.h"
#include "../src/mega/exeeprom/inc/exeprom_api.h"
#include "../src/mega/ds1307/inc/ds1307_api.h"
#include "../src/mega/csma/inc/csma_api.h"
#include "../src/mega/SSD/inc/ssd_api.h"
#include "../src/mega/_7seg/inc/_7seg_api.h"
#include "../src/mega/lcdmnue/inc/lcd_menu_api.h"
#include "../src/mega/eeprom/inc/eeprom_api.h"
#include "../src/mega/signalGenertor/inc/signal_gen_api.h"
#include "../src/mega/keypad/inc/keypad_api.h"
#include "../src/mega/button/inc/button_api.h"
#include "../src/mega/Tone/inc/tone_api.h"
#include "../src/mega/ZLP/inc/zlp_api.h"
#include "../src/mega/ADC/inc/adc_api.h"
#include "../src/mega/fifo/inc/fifo_api.h"
#include "../src/mega/utility/inc/utility_api.h"


extern int main(void);
// Application Functions
extern void appMain(void);
extern void appBoot(void);
extern void appInit(void);
extern void appSync(void);

#endif	/* XC_MEGA_H */

