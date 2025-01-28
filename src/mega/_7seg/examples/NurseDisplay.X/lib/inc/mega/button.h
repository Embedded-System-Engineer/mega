/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : buuton.h                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no refence                                                               |
| < SRAM USAGE               : 14 Byte + BUTTON_MAX_BUFFER + 2 Byte Pointer of signal when enable       |                                             |
| < PROGRAM USAGE            : (966) 624 Byte (312 Instruction) +(342 Byte whan add signal)             |                                      
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#ifndef XC_BUTTON_H
#define	XC_BUTTON_H

#include "../mega.h"
#if defined  BUTTON_MODULE
#if BUTTON_MODULE

typedef enum BUTTON_KEY_STATE {
    BUTTON_KEY_PRESS = 0,
    BUTTON_LONG_TAP = 1,
    BUTTON_KEY_RELEASE = 2,
    CANCELED = 3
} BUTTONSTATE_t;

typedef struct {
    uint8_t Keycode;
    uint8_t State;
} stButton_t;

typedef enum {
    BUTTON_KEY_00 = 0x00, BUTTON_KEY_01 = 0x01, BUTTON_KEY_02 = 0x02, BUTTON_KEY_03 = 0x03, BUTTON_KEY_04 = 0x04, BUTTON_KEY_05 = 0x05, BUTTON_KEY_06 = 0x06, BUTTON_KEY_07 = 0x07, BUTTON_KEY_08 = 0x08, BUTTON_KEY_09 = 0x09, BUTTON_KEY_0A = 0x0A, BUTTON_KEY_0B = 0x0B, BUTTON_KEY_0C = 0x0C, BUTTON_KEY_0D = 0x0D, BUTTON_KEY_0E = 0x0E, BUTTON_KEY_0F,
    BUTTON_KEY_10 = 0x10, BUTTON_KEY_11 = 0x11, BUTTON_KEY_12 = 0x12, BUTTON_KEY_13 = 0x13, BUTTON_KEY_14 = 0x14, BUTTON_KEY_15 = 0x15, BUTTON_KEY_16 = 0x16, BUTTON_KEY_17 = 0x17, BUTTON_KEY_18 = 0x18, BUTTON_KEY_19 = 0x19, BUTTON_KEY_1A = 0x1A, BUTTON_KEY_1B = 0x1B, BUTTON_KEY_1C = 0x1C, BUTTON_KEY_1D = 0x1D, BUTTON_KEY_1E = 0x1E, BUTTON_KEY_1F,
    BUTTON_KEY_20 = 0x20, BUTTON_KEY_21 = 0x21, BUTTON_KEY_22 = 0x22, BUTTON_KEY_23 = 0x23, BUTTON_KEY_24 = 0x24, BUTTON_KEY_25 = 0x25, BUTTON_KEY_26 = 0x26, BUTTON_KEY_27 = 0x27, BUTTON_KEY_28 = 0x28, BUTTON_KEY_29 = 0x29, BUTTON_KEY_2A = 0x2A, BUTTON_KEY_2B = 0x2B, BUTTON_KEY_2C = 0x2C, BUTTON_KEY_2D = 0x2D, BUTTON_KEY_2E = 0x2E, BUTTON_KEY_2F,
    BUTTON_KEY_30 = 0x30, BUTTON_KEY_31 = 0x31, BUTTON_KEY_32 = 0x32, BUTTON_KEY_33 = 0x33, BUTTON_KEY_34 = 0x34, BUTTON_KEY_35 = 0x35, BUTTON_KEY_36 = 0x36, BUTTON_KEY_37 = 0x37, BUTTON_KEY_38 = 0x38, BUTTON_KEY_39 = 0x39, BUTTON_KEY_3A = 0x3A, BUTTON_KEY_3B = 0x3B, BUTTON_KEY_3C = 0x3C, BUTTON_KEY_3D = 0x3D, BUTTON_KEY_3E = 0x3E, BUTTON_KEY_3F,
    BUTTON_KEY_40 = 0x40, BUTTON_KEY_41 = 0x41, BUTTON_KEY_42 = 0x42, BUTTON_KEY_43 = 0x43, BUTTON_KEY_44 = 0x44, BUTTON_KEY_45 = 0x45, BUTTON_KEY_46 = 0x46, BUTTON_KEY_47 = 0x47, BUTTON_KEY_48 = 0x48, BUTTON_KEY_49 = 0x49, BUTTON_KEY_4A = 0x4A, BUTTON_KEY_4B = 0x4B, BUTTON_KEY_4C = 0x4C, BUTTON_KEY_4D = 0x4D, BUTTON_KEY_4E = 0x4E, BUTTON_KEY_4F,
    BUTTON_KEY_50 = 0x50, BUTTON_KEY_51 = 0x51, BUTTON_KEY_52 = 0x52, BUTTON_KEY_53 = 0x53, BUTTON_KEY_54 = 0x54, BUTTON_KEY_55 = 0x55, BUTTON_KEY_56 = 0x56, BUTTON_KEY_57 = 0x57, BUTTON_KEY_58 = 0x58, BUTTON_KEY_59 = 0x59, BUTTON_KEY_5A = 0x5A, BUTTON_KEY_5B = 0x5B, BUTTON_KEY_5C = 0x5C, BUTTON_KEY_5D = 0x5D, BUTTON_KEY_5E = 0x5E, BUTTON_KEY_5F,
    BUTTON_KEY_60 = 0x60, BUTTON_KEY_61 = 0x61, BUTTON_KEY_62 = 0x62, BUTTON_KEY_63 = 0x63, BUTTON_KEY_64 = 0x64, BUTTON_KEY_65 = 0x65, BUTTON_KEY_66 = 0x66, BUTTON_KEY_67 = 0x67, BUTTON_KEY_68 = 0x68, BUTTON_KEY_69 = 0x69, BUTTON_KEY_6A = 0x6A, BUTTON_KEY_6B = 0x6B, BUTTON_KEY_6C = 0x6C, BUTTON_KEY_6D = 0x6D, BUTTON_KEY_6E = 0x6E, BUTTON_KEY_6F,
    BUTTON_KEY_70 = 0x70, BUTTON_KEY_71 = 0x71, BUTTON_KEY_72 = 0x72, BUTTON_KEY_73 = 0x73, BUTTON_KEY_74 = 0x74, BUTTON_KEY_75 = 0x75, BUTTON_KEY_76 = 0x76, BUTTON_KEY_77 = 0x77, BUTTON_KEY_78 = 0x78, BUTTON_KEY_79 = 0x79, BUTTON_KEY_7A = 0x7A, BUTTON_KEY_7B = 0x7B, BUTTON_KEY_7C = 0x7C, BUTTON_KEY_7D = 0x7D, BUTTON_KEY_7E = 0x7E, BUTTON_KEY_7F,
    BUTTON_KEY_80 = 0x80, BUTTON_KEY_81 = 0x81, BUTTON_KEY_82 = 0x82, BUTTON_KEY_83 = 0x83, BUTTON_KEY_84 = 0x84, BUTTON_KEY_85 = 0x85, BUTTON_KEY_86 = 0x86, BUTTON_KEY_87 = 0x87, BUTTON_KEY_88 = 0x88, BUTTON_KEY_89 = 0x89, BUTTON_KEY_8A = 0x8A, BUTTON_KEY_8B = 0x8B, BUTTON_KEY_8C = 0x8C, BUTTON_KEY_8D = 0x8D, BUTTON_KEY_8E = 0x8E, BUTTON_KEY_8F,
    BUTTON_KEY_90 = 0x90, BUTTON_KEY_91 = 0x91, BUTTON_KEY_92 = 0x92, BUTTON_KEY_93 = 0x93, BUTTON_KEY_94 = 0x94, BUTTON_KEY_95 = 0x95, BUTTON_KEY_96 = 0x96, BUTTON_KEY_97 = 0x97, BUTTON_KEY_98 = 0x98, BUTTON_KEY_99 = 0x99, BUTTON_KEY_9A = 0x9A, BUTTON_KEY_9B = 0x9B, BUTTON_KEY_9C = 0x9C, BUTTON_KEY_9D = 0x9D, BUTTON_KEY_9E = 0x9E, BUTTON_KEY_9F,
    BUTTON_KEY_A0 = 0xA0, BUTTON_KEY_A1 = 0xA1, BUTTON_KEY_A2 = 0xA2, BUTTON_KEY_A3 = 0xA3, BUTTON_KEY_A4 = 0xA4, BUTTON_KEY_A5 = 0xA5, BUTTON_KEY_A6 = 0xA6, BUTTON_KEY_A7 = 0xA7, BUTTON_KEY_A8 = 0xA8, BUTTON_KEY_A9 = 0xA9, BUTTON_KEY_AA = 0xAA, BUTTON_KEY_AB = 0xAB, BUTTON_KEY_AC = 0xAC, BUTTON_KEY_AD = 0xAD, BUTTON_KEY_AE = 0xAE, BUTTON_KEY_AF,
    BUTTON_KEY_B0 = 0xB0, BUTTON_KEY_B1 = 0xB1, BUTTON_KEY_B2 = 0xB2, BUTTON_KEY_B3 = 0xB3, BUTTON_KEY_B4 = 0xB4, BUTTON_KEY_B5 = 0xB5, BUTTON_KEY_B6 = 0xB6, BUTTON_KEY_B7 = 0xB7, BUTTON_KEY_B8 = 0xB8, BUTTON_KEY_B9 = 0xB9, BUTTON_KEY_BA = 0xBA, BUTTON_KEY_BB = 0xBB, BUTTON_KEY_BC = 0xBC, BUTTON_KEY_BD = 0xBD, BUTTON_KEY_BE = 0xBE, BUTTON_KEY_BF,
    BUTTON_KEY_C0 = 0xC0, BUTTON_KEY_C1 = 0xC1, BUTTON_KEY_C2 = 0xC2, BUTTON_KEY_C3 = 0xC3, BUTTON_KEY_C4 = 0xC4, BUTTON_KEY_C5 = 0xC5, BUTTON_KEY_C6 = 0xC6, BUTTON_KEY_C7 = 0xC7, BUTTON_KEY_C8 = 0xC8, BUTTON_KEY_C9 = 0xC9, BUTTON_KEY_CA = 0xCA, BUTTON_KEY_CB = 0xCB, BUTTON_KEY_CC = 0xCC, BUTTON_KEY_CD = 0xCD, BUTTON_KEY_CE = 0xCE, BUTTON_KEY_CF,
    BUTTON_KEY_D0 = 0xD0, BUTTON_KEY_D1 = 0xD1, BUTTON_KEY_D2 = 0xD2, BUTTON_KEY_D3 = 0xD3, BUTTON_KEY_D4 = 0xD4, BUTTON_KEY_D5 = 0xD5, BUTTON_KEY_D6 = 0xD6, BUTTON_KEY_D7 = 0xD7, BUTTON_KEY_D8 = 0xD8, BUTTON_KEY_D9 = 0xD9, BUTTON_KEY_DA = 0xDA, BUTTON_KEY_DB = 0xDB, BUTTON_KEY_DC = 0xDC, BUTTON_KEY_DD = 0xDD, BUTTON_KEY_DE = 0xDE, BUTTON_KEY_DF,
    BUTTON_KEY_E0 = 0xE0, BUTTON_KEY_E1 = 0xE1, BUTTON_KEY_E2 = 0xE2, BUTTON_KEY_E3 = 0xE3, BUTTON_KEY_E4 = 0xE4, BUTTON_KEY_E5 = 0xE5, BUTTON_KEY_E6 = 0xE6, BUTTON_KEY_E7 = 0xE7, BUTTON_KEY_E8 = 0xE8, BUTTON_KEY_E9 = 0xE9, BUTTON_KEY_EA = 0xEA, BUTTON_KEY_EB = 0xEB, BUTTON_KEY_EC = 0xEC, BUTTON_KEY_ED = 0xED, BUTTON_KEY_EE = 0xEE, BUTTON_KEY_EF,
    BUTTON_NO_KEY = 0xFF
} ButtonsCode;


typedef uint8_t(*pFuncButtonsEvent_t)(stButton_t *);

/*
 --------------------------------------------------------------------------------------------------
 |                                <   mnue Descirption   >                                        |
 --------------------------------------------------------------------------------------------------
 | < Description                   : mnue struct                                                  |
 | < Uasge                         : 5 Byte in Progrm Memeory                                     |                                     
 | < param ButtonNext              : next button in list created                                  |
 | < param Pin                     : Input Pin GPIO                                               |
 | < Param ButtonOptions           : Bit 0 Inicator the button active high or low                 |
 | <                               : Bit 1 Incator the button is Pullup Enable or not             |
 --------------------------------------------------------------------------------------------------
 */
typedef struct ButtonConstantCode_t {
    const uint8_t Code; /*pin ass*/
    const uint8_t Index;
    struct ButtonConstantCode_t const *Next;
} ButtonConstantCode_t;
/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
extern const ButtonConstantCode_t PROGMEM NO_BUTTONCODE;
#elif COMPILER_TYPE == XC
extern const ButtonConstantCode_t NO_BUTTONCODE;
#endif
/*
 --------------------------------------------------------------------------------------------------
 |                           < Create Event  >                                                    | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Event                                            |
 ---------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
#define ButtonCreateEvent(Name,Code,Index, Next) \
extern const ButtonConstantCode_t PROGMEM   Next; \
    const ButtonConstantCode_t PROGMEM Name = {Code,Index,&Next};
#elif COMPILER_TYPE == XC
#define ButtonCreateEvent(Name,Code ,Index, Next) \
extern const ButtonConstantCode_t    Next; \
    const ButtonConstantCode_t  Name = {Code ,Index,&Next};
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonAssignCosntEvents >                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonAssignCosntEvents                                                   |  
 | < @Description       : run Callbacks of The Const Events                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonAssignCosntEvents(const ButtonConstantCode_t * keyEventsFixed);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonScan >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonScan                                                               |  
 | < @Description       : scan buttonScan                                                       | 
 | < @return            : void                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonScan();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonInit >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonInit                                                               |  
 | < @Description       : Init all data into button driver                                                       | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonDriver >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonDriver                                                               |  
 | < @Description       :  button driver  run in background                                                     | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonDriver();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadRegisterEvent >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonRegisterEvent                                                       |  
 | < @Description       : register call back function into Array                                         | 
 | < @Param callback    : callback Function                                                              |
 | < @Param Index       : Event Index                                                                    | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonRegisterEvent(pFuncButtonsEvent_t callback, uint8_t Index);
#endif
#endif


#endif	/* XC_BUTTON_H */