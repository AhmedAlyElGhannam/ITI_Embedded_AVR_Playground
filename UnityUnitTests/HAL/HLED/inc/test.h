#ifndef TEST_H
#define TEST_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "bit_math.h"
#include "MDIO_MockReg.h"
#include "MPORT.h"
#include "MPORT_LCFG.h"
#include "unity_internals.h"
#include "unity.h"

/* only one test for void MPORT_voidInit(void) */
// void UTEST_MPORT_voidInit_ValidEntriesInArr(void);

/* tests for MPORT_enuErrorStatus_t MPORT_enuSetPinDirection(MPORT_enuPortPin_t Copy_enuPortPinNum,  MPORT_enuPortPinDir_t  Copy_enuPortPinDir) */
// wrong port pin format
void UTEST_MPORT_enuSetPinDirection_InvalidPortPinNum(void);
// wrong port pin direction
void UTEST_MPORT_enuSetPinDirection_InvalidPortPinDir(void);
// valid inputs
void UTEST_MPORT_enuSetPinDirection_ValidInputs(void);

/* tests for MPORT_enuErrorStatus_t MPORT_enuSetPinMode(MPORT_enuPortPin_t Copy_enuPortPinNum, MPORT_enuPortPinMode_t Copy_enuPortPinMode) */
// wrong port pin format
void UTEST_MPORT_enuSetPinMode_InvalidPortPinNum(void);
// wrong port pin direction
void UTEST_MPORT_enuSetPinMode_InvalidPortPinMode(void);
// valid inputs
void UTEST_MPORT_enuSetPinMode_ValidInputs(void);


#endif