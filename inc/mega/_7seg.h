/* 
 * File:   _7seg.h
 * Author: hassa
 *
 * Created on February 24, 2024, 3:04 PM
 */

#ifndef _7SEG_H
#define	_7SEG_H
#include "../mega.h"

#if defined __7SEG_MODULE
#if __7SEG_MODULE
#define _7SEG_DISPALY_COMMON_ANODE               (GPIO_LOW)
#define _7SEG_DISPALY_COMMON_CATHOD              (GPIO_HIGH)

typedef union {
    uint8_t param;

    struct {
        unsigned max_digit : 5; //support 32 digtit per display

        unsigned disply_type : 1; //dispay common one or 0
    };
} ut_7seg_param_t;

typedef struct _7seg_s {
    gpio_t *pins_digits;
    uint8_t *Data;
    uint8_t currentDigit;
    ut_7seg_param_t _7seg_param;
} st_7seg_t;



typedef st_7seg_t* pst_7seg_t;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : create new display 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to digits pint array (read only)
 * 
 * @param : max digit in this display
 * 
 * @param : display type (true is common cathode , false is anode)
 * 
 * @return : pointer to created display if (NULL return the system can't create display)
 */
pst_7seg_t Create_7seg_Display(const gpio_t * digit_pins, const uint8_t max_digit, const uint8_t display_type);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : remove display
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @return : none
 */
void Remove_7seg_Display(pst_7seg_t display);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : crate display
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 */
void _7seg_init();
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
 * @param : justify (0-->left , 1 -->center , 2 -->right)
 * 
 * @return : none
 */
void _7seg_Display_write_string(pst_7seg_t display, const char *string, uint8_t justify);
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
void _7seg_Display_write_Number(pst_7seg_t display, uint32_t value, uint8_t justify);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  scan 7 segment display every system tick
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 *
 * @return : none
 */
void _7seg_scan();

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
 * @param : max count used
 * 
 * @return : none
 */
bool _7seg_display_count(pst_7seg_t display, uint8_t justify, uint32_t countTime, uint16_t maxcount);
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
uint8_t ssd_test_digit_app(pst_7seg_t display, uint32_t time, bool digit_state);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write string 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @return : none
 */
void _7seg_clear_display(pst_7seg_t display);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  display write constant value 
 ---------------------------------------------------------------------------------------------------
 * @param :  pointer to display
 * 
 * @param : value to write all display
 * 
 * @return : none
 */
void _7seg_write_contanst_Char(pst_7seg_t display, uint8_t value);
#endif 
#endif

#endif	/* _7SEG_H */

