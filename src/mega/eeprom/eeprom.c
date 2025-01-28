/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : eeprom.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : datasheet                                                                |  
| < SRAM USAGE               : 21  Byte (10 Byte Buffer + 7 Byte eeprom Descriptor , 4 Byte Time Out)   |
| < PROGRAM USAGE            : 722 Byte  (386 Instruction)                                              |                                    
| < Hardware Usage           : Internal EEPROM                                                          |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (EEPROM_MODULE)
#if EEPROM_MODULE
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Time Wait   >                                               |
 --------------------------------------------------------------------------------------------------------
 | <@macro EEPORM_READ_TIME_OUT  : read operation the cpu heated 4 clock cycle to ready next instruction|
 |                               : and reay data read                                                   |
 | <@macro EEPROM_WRITE_TIME_OUT : write operation the cpu heated 2 clock cycle to ready next           | 
 |                               : instruction and write operation task 1.8ms (2clock cycle*10byte)     |
 |                               : = 20 clock cycle + 1.8ms                                             |
 --------------------------------------------------------------------------------------------------------   
 */
#define     EEPORM_TIME_OUT            200 /*ms*/
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Read States   >                                             |
 --------------------------------------------------------------------------------------------------------
 */
#define    EEPROM_READ_PROGRESS            (0)             
#define    EEPROM_READ_SUCESS              (1)
#define    EEPROM_READ_ERROR               (2)
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom update States   >                                           |
 --------------------------------------------------------------------------------------------------------
 */
#define    EEPROM_UPDATE_PROGRESS            (0)             
#define    EEPROM_UPDATE_SUCESS              (1)
#define    EEPROM_UPDATE_ERROR               (2)
/* 
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Buffer   >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < Description  : any read operation used this buffer                                                 |                 
 | < Uasge        : 10 Byte                                                                             |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t gu8eeprom_read_buf[EEPROM_MAX_BUFFER_SIZE]; /*10Byte*/

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom struct >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < Description          : eeprom struct                                                               |
 | < Uasge                : 7 Byte                                                                      |
 | < param u8State        : state of the eeprom                                                         |                                                                    |                
 | < param size           : max number of the bytes read or write                                       |
 |                        : and this size <= max buffer length of eeprom                                |                          
 | < param u16address     : specefic address required to read or write                                  |
 | < Param u8DataIndex    : data index when read and write operation                                    |
 | < param data           : pointer of the write buffer from application                                |              
 --------------------------------------------------------------------------------------------------------
 */

/*
 * <@var systen have four state 
 */
volatile uint8_t gu8State;
/*
 * <@var Read Write Operation
 */
volatile uint8_t gu8RW;
/*
 * <@var number of byte Read or wite
 */
volatile uint8_t gu8size;
/*
 * <@var Address Request to write 
 */
volatile uint16_t gu16address;
/*
 * <@var current Read Or write Index
 */
volatile uint8_t gu8DataIndex;
/*
 * <@var write data buffer
 */
uint8_t *gpu8data;


/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Time out   >                                                |
 --------------------------------------------------------------------------------------------------------
 */
stTimer_TimeOut_t gstEepromTimeOut;


/*
 --------------------------------------------------------------------------------------------------------
 |                            < Basic Functions Defintions >                                            |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : this function just check the eeprom is Ready or not                           |     
 | < @return            : 1 the eeprom is Busy                                                          |
 |                      : 0 the eeprom is Ready                                                         |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromIsBusy();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromAssignData >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : assign data into Variables                                                    |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
static void __eepromAssignData(uint16_t Address, uint8_t *buf, uint8_t length, uint8_t RW);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < Basic Functions Impelmentions >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : this function just check the eeprom is Ready or not                           |     
 | < @return            : 1 the eeprom is Busy                                                          |
 |                      : 0 the eeprom is Ready                                                         |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromIsBusy() {
#if defined EEPE/*eeprom programing Enable*/
    return (EECR & _BV(EEPE));
#elif defined EEWE/*eeprom write Enable*/
    return (EECR & _BV(EEWE));
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromAssignData >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : assign data into Variables                                                    |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
static void __eepromAssignData(uint16_t Address, uint8_t *buf, uint8_t length, uint8_t RW) {
    if (Address + length >= E2END) return; /*error */
    if (length > EEPROM_MAX_BUFFER_SIZE) return;
    gu16address = Address;
    gpu8data = buf;
    gu8size = length;
    gu8RW = RW;
    gu8State = 1;
    sysSetPeriodMS(&gstEepromTimeOut, EEPORM_TIME_OUT);
}




/*
 --------------------------------------------------------------------------------------------------------
 |                            < user Functions Impelmentions >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromInit >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromInit                                                              |
 | < @Description       : Initialization all variables and Initialization eeorpm                        |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromInit() {
#if defined EEPM1
    /*eeprom programming with write only operation*/
    EECR &= ~(1 < EEPM0);
    EECR |= (1 < EEPM1);
#endif
    gu16address = 0;
    gu8State = 0;
    gu8DataIndex = 0;
    gu8RW = 0;
    gpu8data = NULL;
    setBuff(gu8eeprom_read_buf, 0xFF, EEPROM_MAX_BUFFER_SIZE);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromDriver >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromDriver                                                            |
 | < @Description       : read and update operaion active state run in background                       |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromDriver() {
    if (!gu8State)
        return;



    if (__eepromIsBusy()) {
        return;
    }

    if (sysIsTimeoutMs(&gstEepromTimeOut) == 0 ) {
        gu8State = 0;
        gu8DataIndex = 0;
        gu16address = 0;
        return;
    }

    if (gu8State == 1) { /*Read OPeration*/
        if (gu8DataIndex < gu8size) {
            ATOMIC_BEGIN
            EEAR = gu16address; /*assign start address of the data*/
            EECR |= (1 << EERE); /*enable read operation*/
            gu8eeprom_read_buf[gu8DataIndex] = EEDR; /*read data Into read buffer*/
            ATOMIC_END
            /*cpu stop   4 Clock Cycle*/
            gu8DataIndex++;
            gu16address++;
        } else {

            gu8DataIndex = 0; /*reset data Index*/
            if (gu8RW) {
                gu16address = 0;
                gu8State = 0;
                return;
            }
            gu16address -= gu8size; /*got to first address*/
            gu8State = 2;
        }
        return;
    }

    if (gu8State == 2) {/*match*/
        /*match byte by byte*/
        if (gu8DataIndex < gu8size) {
            if (gu8eeprom_read_buf[gu8DataIndex] == gpu8data[gu8DataIndex]) {
                gu8DataIndex++;
                gu16address++;
                return;
            }
            gu8State = 3;
        } else {
            gu8State = 0;
            gu8DataIndex = 0;
        }
        return;
    }

    if (gu8State == 3) { /*write OPeration*/
        ATOMIC_BEGIN
        EEAR = gu16address++; /*assignment address*/
        EEDR = gpu8data[gu8DataIndex++]; /*assignment data*/
        /*active write operation*/
#if defined EEPE
        EECR |= (1 << EEMPE); /*Enable In Master Mode Programming*/
        EECR |= (1 << EEPE); /*active Programming Operation*/
#elif defined EEWE
        EECR |= (1 << EEMWE); /*Enable In Master Mode Write*/
        EECR |= (1 << EEWE); /*active Write Operation*/
#endif
        ATOMIC_END
        gu8State = 2;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromWriteBuf >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromWriteBuf                                                          |
 | < @Description       : application write data into eeprom by this function to write muti row data    | 
 | < @Param address     : start address request to write data this address less than (EEPROM_END-10)    |
 | < @Param size        : number of byte write into eeprom and this size less than 10 byte in each time |
 | < @param data        : pointer to payload data into eeprom                                           |              
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromWriteBuf(uint16_t address, uint8_t size, uint8_t *data) {
    __eepromAssignData(address, data, size, 0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestSterm >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestSterm                                                      |
 | < @Description       : application read data from eeprom by this function to read muti row data      | 
 | < @Param address     : start address request to read data this address+size less than (EEPROM_END)   |
 | < @Param size        : number of byte read from eeprom and this size less than 10 byte in each time  |            
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestSterm(uint16_t address, uint8_t size) {
    __eepromAssignData(address, gu8eeprom_read_buf, size, 1);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestByte >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestByte                                                       |
 | < @Description       : application read data from eeprom by this function to read single byte data   | 
 | < @Param address     : start address request to read data this address less than (EEPROM_END)        |           
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestByte(uint16_t address) {
    __eepromAssignData(address, gu8eeprom_read_buf, 1, 1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromIsBusy >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromIsBusy                                                         |
 | < @Description       : chack state of Internal eeprom is ready to access new operation or not        |        
 | < @return            : 0 eeprom is ready to new operation                                            |
 |                      : 1 eeprom Internal Write Operaion in Progress                                  |
 |                      : 2 eeprom Internal Read Operaion in Progress                                   |              
 --------------------------------------------------------------------------------------------------------
 */
uint8_t eepromIsBusy() {
    if (!gu8State) {
        return (0);
    }
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRead >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromRead                                                           |
 | < @Description       : Read data From Internal Buffer with Last Operation size                       |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void eepromRead(uint8_t *buf) {
    if (gu8size == 0) return;
    copyBuff(buf, gu8eeprom_read_buf, gu8size);
}

#endif
#endif
