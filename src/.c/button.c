/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : buuton.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no refence                                                               |
| < SRAM USAGE               : 14 Byte + BUTTON_MAX_BUFFER + 2 Byte Pointer of signal when enable       |                                             |
| < PROGRAM USAGE            : (966) 624 Byte (312 Instruction) +(342 Byte whan add signal)             |                                      
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"

#if defined  BUTTON_MODULE
#if BUTTON_MODULE
#define       BUTTONS_DEBOUND_COUNT          ((BUTTON_DEDEBOUND_TIME * 1000UL) / (BUT_PERIDIC_TASK*N_OF_US_REQUIRED))
#if          BUTTONS_DEBOUND_COUNT < 255
#define       KEYPAD_DE_COUNT                BUTTONS_DEBOUND_COUNT-1
#else 
#define       KEYPAD_DE_COUNT      255
#endif

#ifndef      BUTTONS_QUEUE_SIZE  
#define      BUTTONS_QUEUE_SIZE               (3)
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < KEYPAD_COMMONS_PINS  >                                                   |
 ---------------------------------------------------------------------------------------------------------
 */
#ifndef   BUTTON_01_PIN
#define   BUTTON_01_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_03_PIN
#define   BUTTON_03_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_04_PIN
#define   BUTTON_04_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_05_PIN
#define   BUTTON_05_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_06_PIN
#define   BUTTON_06_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_07_PIN
#define   BUTTON_07_PIN                   NOT_A_PIN
#endif
#ifndef   BUTTON_08_PIN
#define   BUTTON_08_PIN                   NOT_A_PIN
#endif



/****************************KEYPAD MAX EVENT****************/
#ifndef   BUTTON_MAX_EVENT  
#define   BUTTON_MAX_EVENT          8
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < Create keyCloumn Keypad Definition  >                                     |
 ---------------------------------------------------------------------------------------------------------
 */
#if BUTTON_MAX_EVENT == 8
#define  MAX_VALUE_READ           255
#elif BUTTON_MAX_EVENT == 7
#define  MAX_VALUE_READ           127
#elif BUTTON_MAX_EVENT == 6
#define  MAX_VALUE_READ           63
#elif BUTTON_MAX_EVENT == 5
#define  MAX_VALUE_READ           31
#elif  BUTTON_MAX_EVENT ==  4    
#define  MAX_VALUE_READ           15
#elif  BUTTON_MAX_EVENT ==  3    
#define  MAX_VALUE_READ           7
#elif  BUTTON_MAX_EVENT ==  2    
#define  MAX_VALUE_READ           3
#elif  BUTTON_MAX_EVENT ==  1    
#define  MAX_VALUE_READ           1
#else
#error BUTTON_MAX_EVENT Rang from 1 to 8
#endif

#define  BUTTON_MAX_BIT_OF_CODE        BUTTON_MAX_EVENT
/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
const ButtonConstantCode_t PROGMEM NO_BUTTONCODE = {MAX_VALUE_READ, 0, (ButtonConstantCode_t *) NULL};
#elif COMPILER_TYPE == XC
const ButtonConstantCode_t NO_CODE = {0xFF, 0, (keypadConstantCode_t *) NULL};
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef union {
    uint8_t Flags;

    struct {
        unsigned LongTabFlag : 1;
        unsigned NewCallBackHandle : 1;
        unsigned KeyState : 2;
    };
} ubuttonStates_t;

static ubuttonStates_t gu8buttonFlags;
/*
 * @var gu8KeyCode              : System Have a New Code  form ISR
 */
static volatile uint8_t gu8ButtonKeyCode;
/*
 * @var gu8CurrentCode              : System Have a New Code 
 */
static volatile uint8_t gu8ButtonCurrentCode;
/*
 * @var gu8LastCode              : System Have a Last  Code 
 */
static volatile uint8_t gu8ButtonLastCode;
/*
 * @var save button state 
 */
static volatile uint8_t gu8ButtonState;
/*
 * @var save button state 
 */
static stButton_t gu8ButtonStateFromQueue;
/*
 * @var gu8KeyDounceCounter     : bounce Counter to event Key
 */
static volatile uint8_t gu8ButtonDounceCounter;
/*
 * <@var gpFunKeyEvents :save Call Packs array of Key events
 */
static pFuncButtonsEvent_t gpFunButtonKeyEvents[BUTTON_MAX_EVENT];
/*
 * <@var gKeyEventQueue  :array of Keys  Save Last 3 keys 
 */
static stButton_t gButtonEventQueue[BUTTONS_QUEUE_SIZE];
/*
 * <@var 
 */
static stBufferStructDescriptor_t gstButtonByteBufferDescriptor;
/*
 * <@var gstButtonLongPrssTimeOut           : Check Long Press TimeOut Or Not          
 */
static stTimer_TimeOut_t gstButtonLongPrssTimeOut;
/*
 * const Pointer
 */
static const ButtonConstantCode_t *gpConstPointer;
/*
 * Current event 
 */
static volatile pFuncButtonsEvent_t gpButtonEvent;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < pinScan >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t pinScan                                                               |  
 | < @Description       : scan pinScan                                                       | 
 | < @return            : return 0 to 0xFF                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t pinScan();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextCode                                                             |
 | < @Description       : return Next OF The Current code                                               |    
 | < @Param Code      : pointer to constant code                                                        |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const ButtonConstantCode_t * getNextbuttonCode(const ButtonConstantCode_t *Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  getNextCode                                                             |
 | < @Description       : return code                                                                   |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const Code                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t getbuttonCode(const ButtonConstantCode_t *Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getIndex >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getIndex                                                            |
 | < @Description        : return Index of Callback                                                     |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return             : Const Index                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t getbuttonIndex(const ButtonConstantCode_t *Code);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ButtonPutIntoQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ButtonPutIntoQueue                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ButtonPutIntoQueue();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ButtonGetFromQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ButtonGetFromQueue                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ButtonGetFromQueue(void);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < pinScan >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t pinScan                                                               |  
 | < @Description       : scan pinScan                                                       | 
 | < @return            : return 0 to 0xFF                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t pinScan() {
    uint8_t code;
    code = 0;
#if BUTTON_MAX_EVENT == 8    
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
    bitWrite8Bit(code, 3, digitalPinRead(BUTTON_04_PIN));
    bitWrite8Bit(code, 4, digitalPinRead(BUTTON_05_PIN));
    bitWrite8Bit(code, 5, digitalPinRead(BUTTON_06_PIN));
    bitWrite8Bit(code, 6, digitalPinRead(BUTTON_07_PIN));
    bitWrite8Bit(code, 7, digitalPinRead(BUTTON_08_PIN));
#elif BUTTON_MAX_EVENT == 7
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
    bitWrite8Bit(code, 3, digitalPinRead(BUTTON_04_PIN));
    bitWrite8Bit(code, 4, digitalPinRead(BUTTON_05_PIN));
    bitWrite8Bit(code, 5, digitalPinRead(BUTTON_06_PIN));
    bitWrite8Bit(code, 6, digitalPinRead(BUTTON_07_PIN));
#elif BUTTON_MAX_EVENT == 6
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
    bitWrite8Bit(code, 3, digitalPinRead(BUTTON_04_PIN));
    bitWrite8Bit(code, 4, digitalPinRead(BUTTON_05_PIN));
    bitWrite8Bit(code, 5, digitalPinRead(BUTTON_06_PIN));
#elif BUTTON_MAX_EVENT == 5
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
    bitWrite8Bit(code, 3, digitalPinRead(BUTTON_04_PIN));
    bitWrite8Bit(code, 4, digitalPinRead(BUTTON_05_PIN));
#elif BUTTON_MAX_EVENT == 4
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
    bitWrite8Bit(code, 3, digitalPinRead(BUTTON_04_PIN));
#elif BUTTON_MAX_EVENT == 3
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
    bitWrite8Bit(code, 2, digitalPinRead(BUTTON_03_PIN));
#elif BUTTON_MAX_EVENT == 2
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
    bitWrite8Bit(code, 1, digitalPinRead(BUTTON_02_PIN));
#elif BUTTON_MAX_EVENT == 1
    bitWrite8Bit(code, 0, digitalPinRead(BUTTON_01_PIN));
#endif


    return code;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonScan >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonScan                                                               |  
 | < @Description       : scan buttonScan                                                       | 
 | < @return            : void                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonScan() {
    if (gu8buttonFlags.KeyState == 0) {
        gu8ButtonDounceCounter = KEYPAD_DE_COUNT;
        gu8ButtonState = pinScan();
        gu8buttonFlags.KeyState = 1;
        return;
    }

    if (gu8buttonFlags.KeyState == 1) {
        if (gu8ButtonState != pinScan()) {
            gu8buttonFlags.KeyState = 0;
        } else {
            if (gu8ButtonDounceCounter != 0) {
                gu8ButtonDounceCounter--;
            } else {
                gu8buttonFlags.KeyState = 2;
            }
        }
        return;
    }

    if (gu8buttonFlags.KeyState == 2) {
        gu8ButtonKeyCode = gu8ButtonState;
        gu8buttonFlags.KeyState = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < scanRows >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonScan                                                               |  
 | < @Description       : scan buttons                                                       | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonInit() {
#if BUTTON_MAX_EVENT == 8
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_04_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_05_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_06_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_07_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_08_PIN, MODE_INPUT_PULLUP);
#elif BUTTON_MAX_EVENT == 7
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_04_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_05_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_06_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_07_PIN, MODE_INPUT_PULLUP);
#elif BUTTON_MAX_EVENT == 6
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_04_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_05_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_06_PIN, MODE_INPUT_PULLUP);
#elif BUTTON_MAX_EVENT == 5
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_04_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_05_PIN, MODE_INPUT_PULLUP);
#elif  BUTTON_MAX_EVENT ==  4    
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_04_PIN, MODE_INPUT_PULLUP);
#elif  BUTTON_MAX_EVENT ==  3    
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_03_PIN, MODE_INPUT_PULLUP);
#elif  BUTTON_MAX_EVENT ==  2    
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(BUTTON_02_PIN, MODE_INPUT_PULLUP);
#elif  BUTTON_MAX_EVENT ==  1   
    digitalpinMode(BUTTON_01_PIN, MODE_INPUT_PULLUP);

#endif
    gu8buttonFlags.Flags = 0x00;
    gu8ButtonDounceCounter = KEYPAD_DE_COUNT;
    setBuff(gButtonEventQueue, MAX_VALUE_READ, BUTTONS_QUEUE_SIZE);
    structBufferInit(&gstButtonByteBufferDescriptor, gButtonEventQueue, BUTTONS_QUEUE_SIZE, 2);
    gu8ButtonState = MAX_VALUE_READ;
    gu8ButtonLastCode = MAX_VALUE_READ;
    gu8ButtonCurrentCode = MAX_VALUE_READ;
    gpConstPointer = &NO_BUTTONCODE;
    gpButtonEvent = NULL;
    for (uint8_t i = 0; i < BUTTON_MAX_EVENT; i++) {
        gpFunButtonKeyEvents[i] = NULL;
    }

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ButtonPutIntoQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ButtonPutIntoQueue                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ButtonPutIntoQueue() {
    stButton_t State;
    if (gu8ButtonCurrentCode == gu8ButtonKeyCode) {
        if ((gu8buttonFlags.LongTabFlag) && (!sysIsTimeoutMs(&gstButtonLongPrssTimeOut))) {
            /*Long Tab is Done */
            State.Keycode = gu8ButtonKeyCode;
            State.State = BUTTON_LONG_TAP;
            gu8buttonFlags.LongTabFlag = 0;
            putStruct(&gstButtonByteBufferDescriptor, &State); /*Put Key Into Queue*/
            return;
        }
        return;
    }

    gu8ButtonLastCode = gu8ButtonCurrentCode;
    gu8ButtonCurrentCode = gu8ButtonKeyCode;
    State.Keycode = gu8ButtonKeyCode;
    if (gu8ButtonCurrentCode == MAX_VALUE_READ) {
        /*release action*/
        State.State = BUTTON_KEY_RELEASE;
        gu8buttonFlags.LongTabFlag = 0;
    } else if (gu8ButtonLastCode == MAX_VALUE_READ && gu8ButtonCurrentCode != MAX_VALUE_READ) {
        sysSetPeriodMS(&gstButtonLongPrssTimeOut, BUTTON_LONG_TIME); /*active Long Press Time*/
        gu8buttonFlags.LongTabFlag = 1; /*long Press is OK*/
        State.State = BUTTON_KEY_PRESS;
    }
    putStruct(&gstButtonByteBufferDescriptor, &State);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ButtonGetFromQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ButtonGetFromQueue                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ButtonGetFromQueue(void) {
    if (!gu8buttonFlags.NewCallBackHandle) {
        if (getStruct(&gstButtonByteBufferDescriptor, &gu8ButtonStateFromQueue)) {
            const ButtonConstantCode_t *i = gpConstPointer;
            for (; i && i != &NO_BUTTONCODE; i = getNextbuttonCode(i)) {
                gpButtonEvent = gpFunButtonKeyEvents[getbuttonIndex(i)];
                if (gpButtonEvent != NULL && gu8ButtonStateFromQueue.Keycode == getbuttonCode(i)) {

#if defined TONE_MODULE
#if TONE_MODULE
                    Toneplay(0, 200, 1, 100);
#endif
#endif              
                    gu8buttonFlags.NewCallBackHandle = 1;
                    return;
                }
            }
            return;
        }
        return;
    }

    if (gpButtonEvent(&gu8ButtonStateFromQueue)) {
        gpButtonEvent = NULL;
        gu8buttonFlags.NewCallBackHandle = 0;
        return;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextCode                                                             |
 | < @Description       : return Next OF The Current code                                               |    
 | < @Param Code      : pointer to constant code                                                        |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const ButtonConstantCode_t * getNextbuttonCode(const ButtonConstantCode_t * Code) {
#if COMPILER_TYPE == GCC
    return (const ButtonConstantCode_t *) pgm_read_word(&Code->Next); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const ButtonConstantCode_t *) (Code->Next); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  getNextCode                                                             |
 | < @Description       : return code                                                                   |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const Code                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t getbuttonCode(const ButtonConstantCode_t * Code) {
#if COMPILER_TYPE == GCC
    return (uint8_t) pgm_read_byte(&Code->Code); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const uint8_t) (Code->Code); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getIndex >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getIndex                                                            |
 | < @Description        : return Index of Callback                                                     |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return             : Const Index                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t getbuttonIndex(const ButtonConstantCode_t * Code) {
#if COMPILER_TYPE == GCC
    return (uint8_t) pgm_read_byte(&Code->Index); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const uint8_t) (Code->Index); /*xc-compiler*/
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonAssignCosntEvents >                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonAssignCosntEvents                                                   |  
 | < @Description       : run Callbacks of The Const Events                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonAssignCosntEvents(const ButtonConstantCode_t * keyEventsFixed) {
    if (keyEventsFixed && keyEventsFixed != &NO_BUTTONCODE)
        gpConstPointer = keyEventsFixed;
}

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
void buttonRegisterEvent(pFuncButtonsEvent_t callback, uint8_t Index) {
    gpFunButtonKeyEvents[Index] = callback;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonDriver >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonDriver                                                               |  
 | < @Description       :  button driver  run in background                                                     | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonDriver() {
    ButtonPutIntoQueue();
    ButtonGetFromQueue();
}
#endif
#endif