/* 
 * File:   fifo.c
 * Author: hassa
 *
 * Created on July 25, 2023, 5:19 PM
 */

#include <stdlib.h>
#include <string.h>
#include "../../../inc/mega.h"




#include <stdint-gcc.h>

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
void fifo_bytes_init(stByteFIFO_t *pstByteFIFO, uint8_t *pbyteBuffer, uint16_t cap) {
    pstByteFIFO->pByteBuffer = pbyteBuffer;
    pstByteFIFO->u16Capacity = cap;
    pstByteFIFO->u16ReadIndex = 0;
    pstByteFIFO->u16WriteIndex = 0;
    pstByteFIFO->u16FreeSize = cap;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  check buffer is full Or Not
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @return: 1 is full , 0 else
 */
uint8_t fifo_bytes_Is_Full(stByteFIFO_t *pstByteFIFO) {
    if (pstByteFIFO->u16FreeSize == 0) {
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  check buffer is Empty Or Not
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @return: 1 is empty , 0 else
 */
uint8_t fifo_bytes_Is_Empty(stByteFIFO_t *pstByteFIFO) {

    if (pstByteFIFO->u16FreeSize == pstByteFIFO->u16Capacity) {
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write buffer just one byte to buffer
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to Byte Fifo Buffer
 * 
 * @param : Pointer to source Byte
 * 
 */
etFIFO_Status_t fifo_byte_write(stByteFIFO_t *pstByteFIFO, uint8_t byte) {
    return (fifo_bytes_write(pstByteFIFO, &byte, 1));
}

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
etFIFO_Status_t fifo_byte_Read(stByteFIFO_t *pstByteFIFO, uint8_t *byte) {
    return fifo_bytes_read(pstByteFIFO, byte, 1);

}

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
etFIFO_Status_t fifo_byte_remove(stByteFIFO_t *pstByteFIFO) {
    return fifo_bytes_remove(pstByteFIFO, 1);
}

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
etFIFO_Status_t fifo_byte_Peek(stByteFIFO_t *pstByteFIFO, uint8_t *Byte, uint16_t Offset) {
    return fifo_bytes_peek(pstByteFIFO, Byte, Offset, 1);
}

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
etFIFO_Status_t fifo_bytes_write(stByteFIFO_t *pstByteFIFO, void *pbuf, uint16_t size) {
    uint8_t *pu8currentWritePointer;
    uint16_t u16FirstSize = 0;
    uint16_t u16SecondSize = 0;




    if (pstByteFIFO->u16FreeSize < size) {
        return FIFO_NO_SPA;
    }
    pu8currentWritePointer = &pstByteFIFO->pByteBuffer[pstByteFIFO->u16WriteIndex]; /*start Index of write Data*/
    if (pstByteFIFO->u16WriteIndex + size < pstByteFIFO->u16Capacity) {
        copyBuff(pu8currentWritePointer, pbuf, size);
        pstByteFIFO->u16WriteIndex += size;
    } else {
        u16FirstSize = pstByteFIFO->u16Capacity - pstByteFIFO->u16WriteIndex;
        copyBuff(pu8currentWritePointer, pbuf, u16FirstSize); /*copy */
        u16SecondSize = size - u16FirstSize;
        copyBuff(pstByteFIFO->pByteBuffer, pbuf + u16FirstSize, u16SecondSize); /*copy */
        pstByteFIFO->u16WriteIndex = u16SecondSize;
    }
    /*update Free Size*/
    pstByteFIFO->u16FreeSize -= size;

    return (FIFO_OK);
}

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
etFIFO_Status_t fifo_bytes_read(stByteFIFO_t *pstByteFIFO, void *pbuf, uint16_t size) {

    uint8_t *pu8CurrentReadPointer;
    uint16_t u8FirstSize = 0;
    uint16_t u8SecondSize = 0;
    if (size == 0) {
        return (FIFO_OK);
    }
    if ((pstByteFIFO->u16Capacity - pstByteFIFO->u16FreeSize) < size) { /*read Data Error*/
        return (FIFO_ERR_NO_DAT);
    }
    pu8CurrentReadPointer = pstByteFIFO->pByteBuffer + pstByteFIFO->u16ReadIndex;
    if (pstByteFIFO->u16Capacity - pstByteFIFO->u16ReadIndex >= size) {
        if (pbuf != NULL) {
            copyBuff(pbuf, pu8CurrentReadPointer, size);
        }
        pstByteFIFO->u16ReadIndex = (pstByteFIFO->u16ReadIndex + size) % pstByteFIFO->u16Capacity;
    } else {
        u8FirstSize = pstByteFIFO->u16Capacity - pstByteFIFO->u16ReadIndex;
        u8SecondSize = size - u8FirstSize;
        if (pbuf != NULL) {
            copyBuff(pbuf, pu8CurrentReadPointer, u8FirstSize); /*copy */
            copyBuff(pbuf + u8FirstSize, pstByteFIFO->pByteBuffer, u8SecondSize); /*copy */
        }
        pstByteFIFO->u16ReadIndex = u8SecondSize;
    }
    pstByteFIFO->u16FreeSize += size;

    return (FIFO_OK);

}

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
etFIFO_Status_t fifo_bytes_peek(stByteFIFO_t *pstByteFIFO, void *pbuf, uint16_t offset, uint16_t size) {
    uint16_t u8UsedSize = 0;
    uint8_t *pu8CurrentReadPointer;
    uint16_t u8FirstSize = 0;
    uint16_t u8SecondSize = 0;
    uint16_t u8ReadIndex;


    if (size == 0) {
        return (FIFO_OK);
    }

    u8UsedSize = (pstByteFIFO->u16Capacity - pstByteFIFO->u16FreeSize);
    if (u8UsedSize == 0) {
        return (FIFO_ERR_NO_DAT);
    }

    if (offset >= u8UsedSize) {
        return (FIFO_ERR_BAD_OFFS);
    }


    if (u8UsedSize < offset + size) {
        return (FIFO_ERR_NO_DAT);
    }

    u8ReadIndex = (pstByteFIFO->u16ReadIndex + offset) % pstByteFIFO->u16Capacity;
    pu8CurrentReadPointer = pstByteFIFO->pByteBuffer + pstByteFIFO->u16ReadIndex;
    if (pstByteFIFO->u16Capacity - u8ReadIndex >= size) {
        if (pbuf != NULL) {
            copyBuff(pbuf, pu8CurrentReadPointer, size);
        }

    } else {
        u8FirstSize = pstByteFIFO->u16Capacity - u8ReadIndex;
        u8SecondSize = size - u8FirstSize;
        if (pbuf != NULL) {

            copyBuff(pbuf, pu8CurrentReadPointer, u8FirstSize); /*copy */
            copyBuff(pbuf + u8FirstSize, pstByteFIFO->pByteBuffer, u8SecondSize); /*copy */
        }
    }
    return (FIFO_OK);
}

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
void fifo_struct_init(stStructFIFO_t *pststrucFIFO, void *pstructBuffer, uint16_t cap, uint16_t structSize) {
    pststrucFIFO->structSize = structSize;
    fifo_bytes_init(&pststrucFIFO->stByteFIFO, pstructBuffer, structSize * cap);
}

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  write struct Data
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to struct Fifo Buffer
 * 
 * @param : Pointer to source struct
 * 
 * 
 * @return: FIFO
 */
etFIFO_Status_t fifo_struct_write(stStructFIFO_t *pststrucFIFO, void *pstructBuffer) {

    return fifo_bytes_write(&pststrucFIFO->stByteFIFO, pstructBuffer, (uint16_t) pststrucFIFO->structSize);
}

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
etFIFO_Status_t fifo_struct_Read(stStructFIFO_t *pststrucFIFO, void *pstructBuffer) {
    etFIFO_Status_t res;
    res = fifo_bytes_read(&pststrucFIFO->stByteFIFO, pstructBuffer, (uint16_t) pststrucFIFO->structSize);

    return (res);
}

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
etFIFO_Status_t fifo_struct_peek(stStructFIFO_t *pststrucFIFO, uint16_t offset, void *pstructBuffer) {
    etFIFO_Status_t res;
    res = fifo_bytes_peek(&pststrucFIFO->stByteFIFO, pstructBuffer, offset * sizeof (pststrucFIFO->structSize), (uint16_t) pststrucFIFO->structSize);

    return (res);
}

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_N_struct_free(stStructFIFO_t *pststrucFIFO) {
    return (pststrucFIFO->stByteFIFO.u16FreeSize) / (pststrucFIFO->structSize);
}

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_N_struct_used(stStructFIFO_t *pststrucFIFO) {
    return (pststrucFIFO->stByteFIFO.u16Capacity - pststrucFIFO->stByteFIFO.u16FreeSize) / (pststrucFIFO->structSize);
}

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  get Free Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Free Space Into Queue
 */
uint16_t fifo_FreeSpace(stByteFIFO_t *pstByteFIFO) {

    return pstByteFIFO->u16FreeSize;
}

/*
 ---------------------------------------------------------------------------------------------------
| @brief :  Get used  Space Into FIFO Queue
 ---------------------------------------------------------------------------------------------------
 * @param  Pointer to struct Fifo Buffer
 * 
 * @return: Used Space In Queue
 */
uint16_t fifo_UsedSpace(stByteFIFO_t *pstByteFIFO) {
    return (pstByteFIFO->u16Capacity - pstByteFIFO->u16FreeSize);
}

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
etFIFO_Status_t fifo_bytes_remove(stByteFIFO_t *pstByteFIFO, uint16_t size) {

    uint16_t u8FirstSize = 0;
    uint16_t u8SecondSize = 0;
    if (size == 0) {
        return (FIFO_OK);
    }

    if (pstByteFIFO->u16Capacity - pstByteFIFO->u16ReadIndex >= size) {
        pstByteFIFO->u16ReadIndex = (pstByteFIFO->u16ReadIndex + size) % pstByteFIFO->u16Capacity;
    } else {
        u8FirstSize = pstByteFIFO->u16Capacity - pstByteFIFO->u16ReadIndex;
        u8SecondSize = size - u8FirstSize;
        pstByteFIFO->u16ReadIndex = u8SecondSize;
    }
    pstByteFIFO->u16FreeSize += size;

    return (FIFO_OK);
}

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
uint8_t fifo_struct_IsEmpty(stStructFIFO_t *pststrucFIFO) {
    return (fifo_bytes_Is_Empty(&pststrucFIFO->stByteFIFO));
}