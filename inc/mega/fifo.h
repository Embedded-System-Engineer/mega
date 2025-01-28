/* 
 * File:   fifo.h
 * Author: hassa
 *
 * Created on July 25, 2023, 5:18 PM
 */

#ifndef FIFO_H
#define	FIFO_H

#include <stdint.h>
#include "../mega.h"
typedef enum etFIFO_Status_e {
    /* success Operation*/
    FIFO_OK = 0,
    /* no space to write data. */
    FIFO_NO_SPA = 1,
    /* no data to read or peek. */
    FIFO_ERR_NO_DAT = 2,
    /* invalid offset. */
    FIFO_ERR_BAD_OFFS = 3,
} etFIFO_Status_t;

typedef struct {
     uint16_t u16WriteIndex;
     uint16_t u16ReadIndex;
     uint16_t u16FreeSize;
     uint16_t u16Capacity;
     uint8_t *pByteBuffer;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Fifo Buffer
 ---------------------------------------------------------------------------------------------------
 * @member : Pointer to Byte Buffer
 * 
 * @member : Read Index
 * 
 * @member : Write Index
 * 
 * @member : Free Size Index
 * 
 * @member : Capacity of FIFO Byte Buffer
 */
stByteFIFO_t;

typedef struct stStructFIFO_S {
    uint16_t structSize;
    stByteFIFO_t stByteFIFO;

}
/*
 ---------------------------------------------------------------------------------------------------
| @brief :  Fifo Buffer
 ---------------------------------------------------------------------------------------------------
 * @member : Byter Buffer FIFO
 *
 * @member : Max Cap
 *  
 */
stStructFIFO_t;


/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Init The Byte Buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to store buffer
 * 
 * @param : max length of the store buffer
 */
void fifo_bytes_init( stByteFIFO_t *pstByteFIFO,  uint8_t *pbyteBuffer,  uint16_t cap);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  check buffer is full Or Not
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @return: 1 is full , 0 else
 */
uint8_t fifo_bytes_Is_Full( stByteFIFO_t *pstByteFIFO);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  check buffer is Empty Or Not
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @return: 1 is empty , 0 else
 */
uint8_t fifo_bytes_Is_Empty( stByteFIFO_t *pstByteFIFO);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write buffer Data From Buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to source buffer
 * 
 * @param : required size to be write
 * 
 * @return: fifo status 
 */
etFIFO_Status_t fifo_bytes_write( stByteFIFO_t *pstByteFIFO, void *pbuf, uint16_t size);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief   read buffer Data From Buffer
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to Byte Fifo Buffer
 * 
 * @param  Pointer to destination buffer
 * 
 * @param  required size to be Read
 * 
 * @rerutn fifo statusn
 */
etFIFO_Status_t fifo_bytes_read( stByteFIFO_t *pstByteFIFO,  void *pbuf,  uint16_t size);

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  peek buffer Data From Buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to destination buffer
 * 
 * @param : required size to be Read
 * 
 * @param : start read Index
 * 
 * @rerutn : fifo status
 */
etFIFO_Status_t fifo_bytes_peek( stByteFIFO_t *pstByteFIFO,  void *pbuf,  uint16_t offset,  uint16_t size);

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  Init The struct Buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to struct Fifo Buffer
 * 
 * @param : Pointer to struct store buffer
 * 
 * @param : max length of the store buffer
 * 
 * @param  :struct size
 * 
 * @return: none
 */
void fifo_struct_init( stStructFIFO_t *pststrucFIFO,  void *pstructBuffer,  uint16_t cap,  uint16_t structSize);

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  write struct Data
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to struct Fifo Buffer
 * 
 * @param : Pointer to source struct
 * 
 * 
 * @return: none
 */
etFIFO_Status_t fifo_struct_write( stStructFIFO_t *pststrucFIFO,  void *pstructBuffer);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  read The struct Buffer
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @param  Pointer to destination struct
 * 
 * 
 * @return: FIFO status
 */
etFIFO_Status_t fifo_struct_Read( stStructFIFO_t *pststrucFIFO,  void *pstructBuffer);

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_FreeSpace( stByteFIFO_t *pstByteFIFO);
/*
 ---------------------------------------------------------------------------------------------------
| @brief :  Get used  Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Used Space In Queu
 */
uint16_t fifo_UsedSpace( stByteFIFO_t *pstByteFIFO);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write buffer just one byte to buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to source Byte
 * 
 */
etFIFO_Status_t fifo_byte_write( stByteFIFO_t *pstByteFIFO,  uint8_t byte);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Just On Byte
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte FIFO Buffer
 * 
 * @Param : Pointer to des
 * 
 * @return: FIFO Status
 */
etFIFO_Status_t fifo_byte_Read( stByteFIFO_t *pstByteFIFO,  uint8_t *byte);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Peek D buffer just one byte to buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to des Byte
 * 
 * @param : Current Read Offset
 * 
 * @return: FIFO States
 */
etFIFO_Status_t fifo_byte_Peek( stByteFIFO_t *pstByteFIFO,  uint8_t *Byte,  uint16_t Offset);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  remove current data from buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to 
 *  
 * @param : length data to remove
 * 
 * @return: FIFO States
 */
etFIFO_Status_t fifo_bytes_remove( stByteFIFO_t *pstByteFIFO,  uint16_t size);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Just On Byte
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte FIFO Buffer
 * 
 * @Param : Pointer to des
 * 
 * @return: FIFO Status
 */
etFIFO_Status_t fifo_byte_remove( stByteFIFO_t *pstByteFIFO);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  read The struct Buffer
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @param  Pointer to destination struct
 * 
 * 
 * @return: FIFO status
 */
etFIFO_Status_t fifo_struct_peek( stStructFIFO_t *pststrucFIFO,  uint16_t offset,  void *pstructBuffer);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  read The struct Buffer
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * 
 * 
 * @return: 1 is empty , 0 is not empty
 */
uint8_t fifo_struct_IsEmpty( stStructFIFO_t *pststrucFIFO);
/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_N_struct_free(stStructFIFO_t *pststrucFIFO) ;
/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_N_struct_used(stStructFIFO_t *pststrucFIFO);
#endif	/* FIFO_H */

