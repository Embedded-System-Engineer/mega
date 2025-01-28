#include <stdint-gcc.h>
#include <stdint.h>

#include "../../../inc/mega.h"
#if defined __7SEG_MODULE
#if __7SEG_MODULE
/*
 * seven segment assii table
 */
static const uint8_t PROGMEM SevenSegmentASCII[] = {
    0b00000000, /* (space) */
    0b10000110, /* ! */
    0b00100010, /* " */
    0b01111110, /* # */
    0b01101101, /* $ */
    0b11010010, /* % */
    0b01000110, /* & */
    0b00100000, /* ' */
    0b00101001, /* ( */
    0b00001011, /* ) */
    0b00100001, /* * */
    0b01110000, /* + */
    0b00010000, /* , */
    0b01000000, /* - */
    0b10000000, /* . */
    0b01010010, /* / */
    0b00111111, /* 0 */
    0b00000110, /* 1 */
    0b01011011, /* 2 */
    0b01001111, /* 3 */
    0b01100110, /* 4 */
    0b01101101, /* 5 */
    0b01111101, /* 6 */
    0b00000111, /* 7 */
    0b01111111, /* 8 */
    0b01101111, /* 9 */
    0b00001001, /* : */
    0b00001101, /* ; */
    0b01100001, /* < */
    0b01001000, /* = */
    0b01000011, /* > */
    0b11010011, /* ? */
    0b01011111, /* @ */
    0b01110111, /* A */
    0b01111100, /* B */
    0b00111001, /* C */
    0b01011110, /* D */
    0b01111001, /* E */
    0b01110001, /* F */
    0b00111101, /* G */
    0b01110110, /* H */
    0b00110000, /* I */
    0b00011110, /* J */
    0b01110101, /* K */
    0b00111000, /* L */
    0b00010101, /* M */
    0b00110111, /* N */
    0b00111111, /* O */
    0b01110011, /* P */
    0b01101011, /* Q */
    0b00110011, /* R */
    0b01101101, /* S */
    0b01111000, /* T */
    0b00111110, /* U */
    0b00111110, /* V */
    0b00101010, /* W */
    0b01110110, /* X */
    0b01101110, /* Y */
    0b01011011, /* Z */
    0b00111001, /* [ */
    0b01100100, /* \ */
    0b00001111, /* ] */
    0b00100011, /* ^ */
    0b00001000, /* _ */
    0b00000010, /* ` */
    0b01011111, /* a */
    0b01111100, /* b */
    0b01011000, /* c */
    0b01011110, /* d */
    0b01111011, /* e */
    0b01110001, /* f */
    0b01101111, /* g */
    0b01110100, /* h */
    0b00010000, /* i */
    0b00001100, /* j */
    0b01110101, /* k */
    0b00110000, /* l */
    0b00010100, /* m */
    0b01010100, /* n */
    0b01011100, /* o */
    0b01110011, /* p */
    0b01100111, /* q */
    0b01010000, /* r */
    0b01101101, /* s */
    0b01111000, /* t */
    0b00011100, /* u */
    0b00011100, /* v */
    0b00010100, /* w */
    0b01110110, /* x */
    0b01101110, /* y */
    0b01011011, /* z */
    0b01000110, /* { */
    0b00110000, /* | */
    0b01110000, /* } */
    0b00000001, /* ~ */
    0b00000000, /* (del) */
};


#define _7SEG_READ_DATA(P)     (pgm_read_byte(SevenSegmentASCII + (P)))
/*
 * max display dispay number 
 */
static st_7seg_t dispay_array[MAX_DISPLAY_SUPPORT];
/*
 * display created Index
 */
static uint8_t gu8MaxDisplayCreated = 0;
/*
 * display created Index
 */
static uint8_t gu8DisplayCounter = 0;
static pst_7seg_t cuurent_display;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : crate display
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 */
void _7seg_init() {
    gu8MaxDisplayCreated = 0;
    cuurent_display = &dispay_array[0];
    digitalpinMode(_7SEG_DATA0_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA1_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA2_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA3_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA4_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA5_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA6_PIN, MODE_OUTPUT);
    digitalpinMode(_7SEG_DATA7_PIN, MODE_OUTPUT);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : create new display 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to digits pint array (read only) (this array store into flash)
 * 
 * @param : max digit in this display
 * 
 * @param : display type (true is common cathode , false is anode)
 * 
 * @return : pointer to created display if (NULL return the system can't create display)
 */
pst_7seg_t Create_7seg_Display(const gpio_t *digit_pins, const uint8_t max_digit, const uint8_t display_type) {
    //set all pin as a out
    if (gu8MaxDisplayCreated >= MAX_DISPLAY_SUPPORT) {
        return (NULL);
    }

    st_7seg_t *st7Seg = &dispay_array[gu8MaxDisplayCreated];
    st7Seg->Data = malloc(max_digit * sizeof (uint8_t));
    if (st7Seg->Data == NULL) {
        return (NULL);
    }
    ATOMIC_BEGIN
    setBuff(st7Seg->Data, 0x00, max_digit);
    st7Seg->pins_digits = (gpio_t *) digit_pins;
    st7Seg->_7seg_param.max_digit = max_digit;
    st7Seg->_7seg_param.disply_type = display_type;
    for (uint8_t i = 0; i < max_digit; i++) {
        digitalpinMode(digit_pins[i], MODE_OUTPUT);
        digitalPinWrite(digit_pins[i], display_type);
    }
    gu8MaxDisplayCreated++;
    ATOMIC_END


    return (st7Seg);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : remove display
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @return : none
 */
void Remove_7seg_Display(pst_7seg_t display) {

    ATOMIC_BEGIN
    for (uint8_t i = 0; i < display->_7seg_param.max_digit; i++) {
        digitalPinWrite(display->pins_digits[i], display->_7seg_param.disply_type);
    }
    if (display->Data) {
        free(display->Data);
    }
    display->_7seg_param.max_digit = 0;
    display->_7seg_param.disply_type = 0;
    if (gu8MaxDisplayCreated != 0) {

        gu8MaxDisplayCreated--;

    }
    ATOMIC_END
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write number 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @param : number
 * 
 * @param : flashing param
 * 
 * @param : justify (0-->left , 1 -->center , 2 -->right)
 * 
 * @return : none
 */
void _7seg_Display_write_Number(pst_7seg_t display, uint32_t value, uint8_t justify) {
    if (justify > 2) {
        justify = 0;
    }
    uint8_t buf[10];
    uint8_t desbuf[10];
    uint8_t start = 0;
    uint8_t startByte = 0;
    start = u32TOASII(buf, value);
    uint8_t max_digit_per_value = (10 - start);
    for (uint8_t i = 0; i < max_digit_per_value; i++) {
        desbuf[i] = _7SEG_READ_DATA(buf[start + i] - ' ');
    }
    /*scan time by current value*/
    uint8_t maxDigit = min(max_digit_per_value, display->_7seg_param.max_digit);
    //set data into buffer
    if (justify == 0x01) {
        startByte = (display->_7seg_param.max_digit - maxDigit) >> 1;
    } else if (justify == 0x02) {
        startByte = (display->_7seg_param.max_digit - maxDigit);
    } else {
        startByte = 0;
    }
    ATOMIC_BEGIN
    setBuff(display->Data, 0x00, display->_7seg_param.max_digit);
    copyBuff(display->Data + startByte, desbuf, maxDigit);
    ATOMIC_END



}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write string 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @param : pointer to string
 * 
 * @param : flashing param
 * 
 * @param : justify (0x00-->left , 0x01 -->center , x02 -->right)
 * 
 * @return : none
 */
void _7seg_Display_write_string(pst_7seg_t display, const char *string, uint8_t justify) {
    if (justify > 2) {
        justify = 0;
    }

    uint8_t startByte = 0;
    uint8_t max_digit_per_value = strlen(string);
    uint8_t *desbuf = malloc(max_digit_per_value);
    setBuff(desbuf, 0x00, max_digit_per_value);
    for (uint8_t i = 0; i < max_digit_per_value; i++) {
        desbuf[i] = _7SEG_READ_DATA(string[i] - ' ');
    }

    /*scan time by current value*/
    uint8_t max_scan_digit = min(max_digit_per_value, display->_7seg_param.max_digit);
    //set data into buffer
    if (justify == 0x01) {
        startByte = (display->_7seg_param.max_digit - max_scan_digit) >> 1;
    } else if (justify == 0x02) {
        startByte = (display->_7seg_param.max_digit - max_scan_digit);
    } else {
        startByte = 0;
    }
    ATOMIC_BEGIN
    setBuff(display->Data, 0x00, display->_7seg_param.max_digit);
    copyBuff(display->Data + startByte, desbuf, max_scan_digit);
    free(desbuf);
    ATOMIC_END

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  scan 7 segment display write digit
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 *
 * @param : digit number 0 to max digit -1
 * 
 * @param : byte write into digit
 * 
 * @param : start scan is 0 write pin to not active
 * 
 * @return : none
 */
__force_inline static void _7seg_write_Digit(pst_7seg_t display, uint8_t digit_number, uint8_t byte, uint8_t start_scan) {

    digitalPinWrite(display->pins_digits[digit_number], GPIO_LOW); //stop digit
    if (start_scan == 0) {
        return;
    }
    if (byte == 0x00) {
        return;
    }
    //write data into digit

    digitalPinWrite(_7SEG_DATA0_PIN, bitRead(byte, 0)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA1_PIN, bitRead(byte, 1)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA2_PIN, bitRead(byte, 2)^display->_7seg_param.disply_type); //---|>---
    digitalPinWrite(_7SEG_DATA3_PIN, bitRead(byte, 3)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA4_PIN, bitRead(byte, 4)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA5_PIN, bitRead(byte, 5)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA6_PIN, bitRead(byte, 6)^display->_7seg_param.disply_type);
    digitalPinWrite(_7SEG_DATA7_PIN, bitRead(byte, 7)^display->_7seg_param.disply_type);

    //start scan bit
    digitalPinWrite(display->pins_digits[digit_number], GPIO_HIGH);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  scan 7 segment display write data
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 *
 * @param : stop scan when value is one
 * 
 * @return : none
 */
__force_inline static void _7seg_write_pins() {
    //stop all digit 




    if (cuurent_display->_7seg_param.max_digit == 0) {
        return;
    }



    if (cuurent_display->currentDigit != 0) {
        _7seg_write_Digit(cuurent_display, cuurent_display->currentDigit - 1, cuurent_display->Data[cuurent_display->currentDigit - 1], 0);
    } else {
        _7seg_write_Digit(cuurent_display, cuurent_display->_7seg_param.max_digit - 1, cuurent_display->Data[cuurent_display->_7seg_param.max_digit - 1], 0);
        /*change display*/
        cuurent_display = &dispay_array[gu8DisplayCounter++];
        if (gu8DisplayCounter >= gu8MaxDisplayCreated) gu8DisplayCounter = 0;
    }
    _7seg_write_Digit(cuurent_display, cuurent_display->currentDigit, cuurent_display->Data[cuurent_display->currentDigit], 1);
    cuurent_display->currentDigit++;
    if (cuurent_display->currentDigit >= cuurent_display->_7seg_param.max_digit) {
        cuurent_display->currentDigit = 0;
    }





}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  scan 7 segment display every system tick
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 *
 * @return : none
 */
void _7seg_scan() {
    _7seg_write_pins();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  seven segment display count up
 ---------------------------------------------------------------------------------------------------
 * @param :  display count
 * 
 * @param : justifiy (0x00->left ,0x01 -->center ,0x02-->right
 * 
 * @param : count time 
 *
 * @return : none
 */
bool _7seg_display_count(pst_7seg_t display, uint8_t justify, uint32_t countTime, uint16_t maxcount) {
    //count up 0 to 9 form all digit
    //4 digit //10000
    static uint16_t counter = 0;
    static stTimer_TimeOut_t gsTime;
    static uint8_t state = 0;


    if (state == 0) {

        counter = 0;
        state = 1;
    }
    if (state == 1) {


        if (counter >= maxcount) {

            state = 0;
            return (true);
        }
        _7seg_Display_write_Number(display, counter++, justify);
        sysSetPeriodMS(&gsTime, countTime);
        state = 2;
    }

    if (state == 2) {
        if (sysIsTimeoutMs(&gsTime) == 0) {
            state = 1;
        }
        return (false);
    }

    return (false);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  seven segment display count up
 ---------------------------------------------------------------------------------------------------
 * @param :  display count
 * 
 * @param : time count between digit
 *
 * @param : state of the digit after count off or on
 * 
 * @return : none
 */
uint8_t ssd_test_digit_app(pst_7seg_t display, uint32_t time, bool digit_state) {
    static uint8_t max_digit_count = 0;
    static uint8_t currnt_digit_up = 0;
    static uint8_t state = 1;
    static stTimer_TimeOut_t gstdispaly_time;

    if (state == 0) {
        if (sysIsTimeoutMs(&gstdispaly_time) == 0) {
            state = 1;
        }
        return (false);
    }

    if (max_digit_count < display->_7seg_param.max_digit) {
        display->Data[max_digit_count] = _7SEG_READ_DATA(currnt_digit_up + 16);
        currnt_digit_up++;
        state = 0;
        sysSetPeriodMS(&gstdispaly_time, time);
        if (currnt_digit_up >= 10) {
            if (!digit_state) {
                display->Data[max_digit_count] = 0x00;
            }
            currnt_digit_up = 0;
            max_digit_count++;
        }
        return (false);
    }
    max_digit_count = 0;
    return (true);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write string 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @param : value to write all display
 * 
 * @return : none
 */
void _7seg_write_contanst_Char(pst_7seg_t display, uint8_t value) {
    uint8_t value_digit = _7SEG_READ_DATA(value - ' ');
    ATOMIC_BEGIN
    setBuff(display->Data, value_digit, display->_7seg_param.max_digit);
    ATOMIC_END
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write string 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @return : none
 */
void _7seg_clear_display(pst_7seg_t display) {
    ATOMIC_BEGIN
    setBuff(display->Data, 0x00, display->_7seg_param.max_digit);
    ATOMIC_END
}
#endif
#endif