/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : res.h                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */

#ifndef RES_H
#define	RES_H

#define  COMPILER_TYPE                       GCC

/*
 ---------------------------------------------------------------------------------------
 |                                <System MODULE>                                      | 
 ---------------------------------------------------------------------------------------
 | <macro F_CPU                  : F_CPU CLOCK  >look clock.h                          |                                        |
 | <macro @N_OF_US_REQUIRED      : each F_CPU has base number of micro                 |
 |                               : select one of number of micro seconds               |
 |                               : _number+us  > is defined and supported time         |  
 | <macro SRAM_USAGE             : 14 Byte                                             |
 | <macro PROGRAM_USAGE          : 694 byte (347 Instruction)                          |
 ---------------------------------------------------------------------------------------
 */
#define     F_CPU                          XTAL_11059200
#define     N_OF_US_REQUIRED               (_1250us)
/*
 ---------------------------------------------------------------------------------------
 |                                <GPIO MODULE>                                        | 
 ---------------------------------------------------------------------------------------
 | < macro GPIO2_PREFER_SPEED     : gpio speed acess                                   |
 |                                : 0 the  function called used                        |
 |                                : 1 the  function not called and used inline         |
 | < macro GPIO2_IOREGS_ABOVEFF   : enable or disable access gpio with in atomic block |
 |                                : 0 gpio acess without atomic                        |
 |                                : 1 gpio acess with in atomic                        |
 |                                : @note : atomic means disable any extrnal interrupt |
 |                                :       : to not effect in gpio pins at write or...  |
 ---------------------------------------------------------------------------------------
 */
#define     GPIO2_PREFER_SPEED               (1)
#define     GPIO2_IOREGS_ABOVEFF             (0)














/*
 ----------------------------------------------------------------------------------------
 |                                <SSD_MODULE>                                         | 
 ----------------------------------------------------------------------------------------
 | < SSD_MODULE             : 0 module is not active                                   | 
 |                           : 1 module is active                                       |
 | <MAX_PINS_USED            : Number of Pin Used                                       |
 | < SRAM USAGE              :  Byte Per Pin  +2 Byte Pinter to first signal            |      
 | < PROGRAM USAGE           :                                                          |  
 ----------------------------------------------------------------------------------------
 */
#define  __7SEG_MODULE                   (1)
#if __7SEG_MODULE
#define     MAX_DISPLAY_SUPPORT             (2)
#define     _7SEG_DATA0_PIN            GPIO_C0
#define     _7SEG_DATA1_PIN            GPIO_C1
#define     _7SEG_DATA2_PIN            GPIO_C2
#define     _7SEG_DATA3_PIN            GPIO_C3
#define     _7SEG_DATA4_PIN            GPIO_C4
#define     _7SEG_DATA5_PIN            GPIO_C5
#define     _7SEG_DATA6_PIN            GPIO_C6
#define     _7SEG_DATA7_PIN            GPIO_C7
#endif


/*
 ----------------------------------------------------------------------------------------
 |                                <SSD_MODULE>                                         | 
 ----------------------------------------------------------------------------------------
 | < SSD_MODULE             : 0 module is not active                                   | 
 |                           : 1 module is active                                       |
 | <MAX_PINS_USED            : Number of Pin Used                                       |
 | < SRAM USAGE              :  Byte Per Pin  +2 Byte Pinter to first signal            |      
 | < PROGRAM USAGE           :                                                          |  
 ----------------------------------------------------------------------------------------
 */
#define  SSD_MODULE                   (0)
#if SSD_MODULE
#define     SSD_MAX_DIGIT             (7)
#define     SSD_TYPE_LED            SSD_COMMON_ANADOD
#define     SSD_DIR                 SSD_RIGHT

#define      SSD_DIGIT0_PIN          GPIO_B0
#define      SSD_DIGIT1_PIN          GPIO_A0
#define      SSD_DIGIT2_PIN          GPIO_A1
#define      SSD_DIGIT3_PIN          GPIO_A2
#define      SSD_DIGIT4_PIN          GPIO_A3
#define      SSD_DIGIT5_PIN          GPIO_A4
#define      SSD_DIGIT6_PIN          GPIO_A5

#define     SSD_DATA0_PIN            GPIO_C0
#define     SSD_DATA1_PIN            GPIO_C1
#define     SSD_DATA2_PIN            GPIO_C2
#define     SSD_DATA3_PIN            GPIO_C3
#define     SSD_DATA4_PIN            GPIO_C4
#define     SSD_DATA5_PIN            GPIO_C5
#define     SSD_DATA6_PIN            GPIO_C6
#define     SSD_DATA7_PIN            GPIO_C7

#endif
#endif	/* RES_H */

