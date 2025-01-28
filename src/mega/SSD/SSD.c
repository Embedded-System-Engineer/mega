/*
 * File:   SSD.c
 * Author: hassa
 *
 * Created on September 11, 2022, 10:31 AM
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"

#if defined SSD_MODULE
#if SSD_MODULE
static stTimer_TimeOut_t gsTimerTestSSD;
static gpio_t gu8ssdDigitPinsArray[SSD_MAX_DIGIT];
static uint8_t gu8ssdDataArray[SSD_MAX_DIGIT]; /*Number Of Byte To Read Data*/
static volatile uint8_t gu8startDigit;
static volatile uint8_t gu8EndDigit;
static volatile uint8_t gu8ssdCurrentDigit;
static volatile uint8_t gu8ssdDataIndex;
static volatile uint8_t gu8ssdState;
static volatile uint8_t gu8ssdDigitCounter;
static volatile uint8_t gu8ssdLedCounter;


static void ssdWriteDataPins(uint8_t u8Byte);

#define  SSD_TYPE_TEST         (7)
#define  SSD_TEST_OPEN         (6)
#define  SSD_DIGIT_STATE       (5)
#define  SSD_LED_STATE         (4)


static const uint8_t PROGMEM charTable[] = {
    0b01111110, /*0*/
    0b00110000, /*1*/
    0b01101101, /*2*/
    0b01111001, /*3*/
    0b00110011, /*4*/
    0b01011011, /*5*/
    0b01011111, /*6*/
    0b01110000, /*7*/
    0b01111111, /*8*/
    0b01111011, /*9*/
    0b01110111, /*A*/
    0b00011111, /*b*/
    0b01001110, /*c*/
    0b00111101, /*d*/
    0b01001111, /*E*/
    0b01000111, /*F*/
    0b01011110, /*G*/
    0b00010111, /*h*/
    0b00010000, /*i*/
    0b00111000, /*j*/
    0b00101111, /*k*/
    0b00001110, /*L*/
    0b01110110, /*M*/
    0b00010101, /*n*/
    0b00011101, /*O*/
    0b01100111, /*P*/
    0b01110011, /*q*/
    0b00000101, /*r*/
    0b00011011, /*S*/
    0b00001111, /*t*/
    0b00111110, /*U*/
    0b00011100, /*V*/
    0b00101011, /*w*/
    0b00110110, /*x*/
    0b00111011, /*y*/
    0b01001001, /*z*/
    0b00001000, /*_*/
};

static void ssdTestMODE();

#define SSD_TABLE_READ(P)     (pgm_read_byte(charTable + (P)))
#define  SSD_DP_FLAG 0b10000000 

static void ssdWriteDataPins(uint8_t u8Byte) {
#if SSD_TYPE_LED == SSD_COMMON_ANADOD

    digitalPinWrite(SSD_DATA7_PIN, bitRead(u8Byte, 7));
    digitalPinWrite(SSD_DATA0_PIN, bitRead(u8Byte, 6));
    digitalPinWrite(SSD_DATA1_PIN, bitRead(u8Byte, 5));
    digitalPinWrite(SSD_DATA2_PIN, bitRead(u8Byte, 4));
    digitalPinWrite(SSD_DATA3_PIN, bitRead(u8Byte, 3));
    digitalPinWrite(SSD_DATA4_PIN, bitRead(u8Byte, 2));
    digitalPinWrite(SSD_DATA5_PIN, bitRead(u8Byte, 1));
    digitalPinWrite(SSD_DATA6_PIN, bitRead(u8Byte, 0));
#else 
    digitalPinWrite(SSD_DATA7_PIN, !bitRead(u8Byte, 7));
    digitalPinWrite(SSD_DATA0_PIN, !bitRead(u8Byte, 6));
    digitalPinWrite(SSD_DATA1_PIN, !bitRead(u8Byte, 5));
    digitalPinWrite(SSD_DATA2_PIN, !bitRead(u8Byte, 4));
    digitalPinWrite(SSD_DATA3_PIN, !bitRead(u8Byte, 3));
    digitalPinWrite(SSD_DATA4_PIN, !bitRead(u8Byte, 2));
    digitalPinWrite(SSD_DATA5_PIN, !bitRead(u8Byte, 1));
    digitalPinWrite(SSD_DATA6_PIN, !bitRead(u8Byte, 0));
#endif
}

void ssdSync() {



    if (gu8ssdCurrentDigit == 0) {
        digitalPinWrite(gu8ssdDigitPinsArray[SSD_MAX_DIGIT - 1], !SSD_TYPE_LED);
    } else {
        digitalPinWrite(gu8ssdDigitPinsArray[gu8ssdCurrentDigit - 1], !SSD_TYPE_LED);
    }
    ssdWriteDataPins(gu8ssdDataArray[gu8ssdCurrentDigit]);
    digitalPinWrite(gu8ssdDigitPinsArray[gu8ssdCurrentDigit], SSD_TYPE_LED);
    gu8ssdCurrentDigit++;
    if (gu8ssdCurrentDigit >= SSD_MAX_DIGIT)
        gu8ssdCurrentDigit = 0;


}

void ssdInit() {
#if (SSD_MAX_DIGIT == 8)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[7] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[6] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[5] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT5_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT6_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT7_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[5] = SSD_DIGIT5_PIN;
    gu8ssdDigitPinsArray[6] = SSD_DIGIT6_PIN;
    gu8ssdDigitPinsArray[7] = SSD_DIGIT7_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT2_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT3_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT4_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT5_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT6_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT7_PIN, SSD_PIN_INIT);

#elif (SSD_MAX_DIGIT == 7)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[6] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[5] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT5_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT6_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[5] = SSD_DIGIT5_PIN;
    gu8ssdDigitPinsArray[6] = SSD_DIGIT6_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT1_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT2_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT3_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT4_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT5_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DIGIT6_PIN, MODE_OUTPUT);
#elif (SSD_MAX_DIGIT == 6)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[5] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT5_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT4_PIN;
    gu8ssdDigitPinsArray[5] = SSD_DIGIT5_PIN;
#endif

    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT2_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT3_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT4_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT5_PIN, SSD_PIN_INIT);

#elif (SSD_MAX_DIGIT == 5)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[4] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT4_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
    gu8ssdDigitPinsArray[4] = SSD_DIGIT4_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT2_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT3_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT4_PIN, SSD_PIN_INIT);

#elif (SSD_MAX_DIGIT == 4)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[3] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT3_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
    gu8ssdDigitPinsArray[3] = SSD_DIGIT3_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT2_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT3_PIN, SSD_PIN_INIT);
    ;
#elif (SSD_MAX_DIGIT == 3)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[3] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT2_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
    gu8ssdDigitPinsArray[2] = SSD_DIGIT2_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT2_PIN, SSD_PIN_INIT);

#elif (SSD_MAX_DIGIT == 2)
#if SSD_DIR == SSD_RIGHT

    gu8ssdDigitPinsArray[1] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[0] = SSD_DIGIT1_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
    gu8ssdDigitPinsArray[1] = SSD_DIGIT1_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
    digitalpinMode(SSD_DIGIT1_PIN, SSD_PIN_INIT);
#elif (SSD_MAX_DIGIT == 1)
#if SSD_DIR == SSD_RIGHT
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
#else
    gu8ssdDigitPinsArray[0] = SSD_DIGIT0_PIN;
#endif
    digitalpinMode(SSD_DIGIT0_PIN, SSD_PIN_INIT);
#elif (SSD_MAX_DIGIT == 0)
#error  "PLEASE DEFINDE MAX DIGIT"
#endif
    digitalpinMode(SSD_DATA0_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA1_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA2_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA3_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA4_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA5_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA6_PIN, MODE_OUTPUT);
    digitalpinMode(SSD_DATA7_PIN, MODE_OUTPUT);
    setBuff(gu8ssdDataArray, CHAR_OFF_INDEX, SSD_MAX_DIGIT);
    gu8ssdCurrentDigit = 0;
    gu8ssdDataIndex = 0;
    gu8ssdLedCounter = 0;
    gu8ssdDigitCounter = 0;
    gu8ssdState = 0;
    gu8EndDigit = SSD_MAX_DIGIT;
    gu8startDigit = 0;
    sysSetPeriodMS(&gsTimerTestSSD, 500);
}

static void ssdTestMODE() {
    uint8_t u8Max;
    /*update Led every one second digit by digit*/
    /*update digit One*/
    u8Max = 9;
    if (bitIsClear(gu8ssdState, SSD_LED_STATE)) {
        /*check the open TestLED*/
        if (bitIsClear(gu8ssdState, SSD_TEST_OPEN))
            return;
        if (bitIsSet(gu8ssdState, SSD_TYPE_TEST)) {
            u8Max = 7;
            gu8ssdDataArray[gu8ssdDigitCounter] = 0x80 >> gu8ssdLedCounter;
        } else {
            u8Max = 9;
            gu8ssdDataArray[gu8ssdDigitCounter] = SSD_TABLE_READ(gu8ssdLedCounter);
        }
        sysSetPeriodMS(&gsTimerTestSSD, 500);
        bitSet(gu8ssdState, SSD_LED_STATE);
    } else {
        if (sysIsTimeoutMs(&gsTimerTestSSD)) {
            /*Increment Counter digit with LED*/
            gu8ssdLedCounter++;
            if (gu8ssdLedCounter > u8Max) {
                if (bitIsSet(gu8ssdState, SSD_TYPE_TEST))
                    gu8ssdDataArray[gu8ssdDigitCounter] = 0x00;
                else
                    gu8ssdDataArray[gu8ssdDigitCounter] = CHAR_ZERO;
                gu8ssdLedCounter = 0;
                gu8ssdDigitCounter++;
                if (gu8ssdDigitCounter >= gu8EndDigit) {
                    gu8ssdDigitCounter = gu8startDigit;
                    ssdClearData(gu8ssdDataArray);
                }
            }
            bitClear(gu8ssdState, SSD_LED_STATE);
        }

        if (bitIsClear(gu8ssdState, SSD_TEST_OPEN)) {
            gu8ssdDigitCounter = 0;
            gu8ssdLedCounter = 0;
            bitClear(gu8ssdState, SSD_LED_STATE);
            ssdClearData(gu8ssdDataArray);
        }
    }
}

void ssdOpenTest(uint8_t startDigit, uint8_t EndDigit, uint8_t TypeTest) {
    gu8ssdDigitCounter = startDigit;
    gu8EndDigit = EndDigit;
    gu8startDigit = startDigit;
    bitSet(gu8ssdState, SSD_TEST_OPEN);
    if (TypeTest)
        bitSet(gu8ssdState, SSD_TYPE_TEST); /*Test LED MODE*/
}

void ssdCloseTest() {
    gu8ssdDigitCounter = 0;
    gu8ssdLedCounter = 0;
    gu8EndDigit = SSD_MAX_DIGIT; /*max digit*/
    gu8startDigit = 0; /*clear start*/
    bitClear(gu8ssdState, SSD_TEST_OPEN); /*close Test Mode*/
    bitClear(gu8ssdState, SSD_TYPE_TEST); /*Test Digit as a default */
}

void ssdClearData(uint8_t * Data) {
    setBuff(Data, CHAR_OFF_INDEX, SSD_MAX_DIGIT);
}

void ssdPrint(uint8_t *Data, uint8_t startData, uint8_t startDigit, uint8_t length) {
    uint8_t count;
    /*check option byte*/
    count = startData + length - 1; /*4+1-1 = 4 1to 5*/
    for (uint8_t i = startDigit; i < (startDigit + length); i++) {
        gu8ssdDataArray[i] = SSD_TABLE_READ(Data[count]);
        count--;
    }
}

void ssdClearWithDefault(uint8_t defaultChar, uint8_t startDigit, uint8_t length) {
    /*check option byte*/
    setBuff(gu8ssdDataArray + startDigit, defaultChar, length);
}

void ssdDriver() {
    ssdTestMODE();
}

void ssdclearALL() {
    ssdClearData(gu8ssdDataArray);
}

#endif
#endif