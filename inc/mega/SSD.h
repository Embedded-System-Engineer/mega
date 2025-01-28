/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_SSD_H
#define	XC_SSD_H

#include "../mega.h"


#if defined  SSD_MODULE                 
#if SSD_MODULE


#ifndef     SSD_MAX_DIGIT  
#define     SSD_MAX_DIGIT             (8)
#endif


#define    SSD_COMMON_CATHOD     0
#define    SSD_COMMON_ANADOD     1

#ifndef     SSD_DIGIT0_PIN          
#define     SSD_DIGIT0_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DIGIT1_PIN          
#define     SSD_DIGIT1_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DIGIT2_PIN          
#define     SSD_DIGIT2_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DIGIT3_PIN          
#define     SSD_DIGIT3_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DIGIT4_PIN          
#define     SSD_DIGIT4_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DIGIT5_PIN          
#define     SSD_DIGIT5_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DIGIT6_PIN          
#define     SSD_DIGIT6_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DIGIT7_PIN          
#define     SSD_DIGIT7_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DATA0_PIN          
#define     SSD_DATA0_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DATA1_PIN          
#define     SSD_DATA1_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DATA2_PIN          
#define     SSD_DATA2_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DATA3_PIN          
#define     SSD_DATA3_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DATA4_PIN          
#define     SSD_DATA4_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DATA5_PIN          
#define     SSD_DATA5_PIN       NOT_A_PIN
#endif


#ifndef     SSD_DATA6_PIN          
#define     SSD_DATA6_PIN       NOT_A_PIN
#endif

#ifndef     SSD_DATA7_PIN          
#define     SSD_DATA7_PIN       NOT_A_PIN
#endif

#ifndef     SSD_TYPE_LED
#define     SSD_TYPE_LED            SSD_COMMON_CATHOD
#endif



#define  NUMBER_INDEX          0
#define  CHAR_INDEX            10
#define  CHAR_OFF_INDEX        0B00000000
#define  CHAR_NEG              0b00000001
#define   CHAR_ZERO            0b01111110 
#define  TEST_LED       0x00
#define  TEST_DIGIT     0x01

/*set Pin*/
#if SSD_TYPE_LED == SSD_COMMON_CATHOD
#define  SSD_PIN_INIT      MODE_OUTPUT
#else 
#define  SSD_PIN_INIT      MODE_OUTPUT
#endif

#define    SSD_RIGHT   0x01
#define    SSD_LEFT    0x02

#define SSD_NEG_ALLOW           0x00
#define SSD_NEG_NOT_ALLOW       0x01

#ifndef  SSD_DIR 
#define  SSD_DIR          SSD_LEFT
#endif


#ifndef  SSD_PRINT_NEG_ALOW 
#define  SSD_PRINT_NEG_ALOW    SSD_NEG_ALLOW
#endif
void ssdSync();
void ssdInit();
void ssdDriver();
void ssdClearData(uint8_t *Data);
void ssdPrint(uint8_t *Data, uint8_t startData, uint8_t startDigit, uint8_t length);
void ssdCloseTest();
void ssdOpenTest(uint8_t startDigit, uint8_t EndDigit, uint8_t TypeTest);
void ssdClearWithDefault(uint8_t defaultChar, uint8_t startDigit, uint8_t length);
void ssdclearALL();
#endif
#endif

#endif	/* XC_HEADER_TEMPLATE_H */

