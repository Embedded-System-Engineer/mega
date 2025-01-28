/* 
 * File:   memory.h
 * Author: hassa
 *
 * Created on April 19, 2023, 12:07 PM
 */

#ifndef MEMORY_H
#define	MEMORY_H
#include "appRes.h"

typedef struct callPoint_s {
    uint8_t State;
    uint16_t userSwID;
    uint16_t userRID;
} callPoint_t;



/*
 * <@marco system cancel state
 */
#define SYSTEM_DEFALUT_EVENT               0x00
/*
 * <@marco system cancel state
 */
#define SYSTEM_START_ADDRESS_EVENT         0x01
/*
 * <@marco system cancel state
 */
#define SYSTEM_CANCEL_EVENT                0x02
/*
 * <@marco system call state
 */
#define  SYSTEM_ACCEPT_EVENT               0x03
/*
 * <@marco system call state
 */
#define SYSTEM_ASSISSET_EVENT              0x04
/*
 * <@marco system call state
 */
#define SYSTEM_CALL_EVENT                  0x05
/*
 * <@marco system call state
 */
#define SYSTEM_EMG_EVENT                   0x06

#endif	/* MEMORY_H */

