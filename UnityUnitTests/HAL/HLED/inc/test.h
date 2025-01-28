#ifndef TEST_H
#define TEST_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "bit_math.h"
#include "MDIO_MockReg.h"
#include "MPORT.h"
#include "MPORT_LCFG.h"
#include "HLED.h"
#include "HLED_LCFG.h"
#include "unity_internals.h"
#include "unity.h"

/* only one test for void MPORT_voidInit(void) 
void UTEST_HLED_voidInit_ValidEntriesInArr(void);*/

/* HLED_enuErrorStatus_t HLED_uint8SetLEDValue(uint8_t Copy_uint8LEDName, HLED_enuLEDValue_t Copy_uint8LEDValue) */
void UTEST_HLED_uint8SetLEDValue_InvalidLEDName(void);
void UTEST_HLED_uint8SetLEDValue_InvalidLEDValue(void);
void UTEST_HLED_uint8SetLEDValue_ValidInputsForwardConnection(void);
void UTEST_HLED_uint8SetLEDValue_ValidInputsReverseConnection(void);


#endif