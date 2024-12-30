#ifndef TEST_H
#define TEST_H

#include "std_types.h"
#include "bit_math.h"
#include "MDIO_MockReg.h"
#include "MDIO_PBCFG.h"
#include "MDIO.h"
#include "unity_internals.h"
#include "unity.h"

/* tests for MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuPinConfig) */
// invalid port num
void UTEST_MDIO_enuSetPinConfigration_InvalidPortNum(void);
// invalid pin num
void UTEST_MDIO_enuSetPinConfigration_InvalidPinNum(void);
// invalid pin config
void UTEST_MDIO_enuSetPinConfigration_InvalidPinConfig(void);
// using valid inputs
void UTEST_MDIO_enuSetPinConfigration_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuPortConfig) */
// // invalid port num
// void UTEST_MDIO_enuSetPortConfigration_InvalidPortNum(void);
// // invalid port config
// void UTEST_MDIO_enuSetPortConfigration_InvalidPortConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPortConfigration_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuPinState) */
// // invalid port num
// void UTEST_MDIO_enuSetPinValue_InvalidPortNum(void);
// // invalid pin num
// void UTEST_MDIO_enuSetPinValue_InvalidPinNum(void);
// // invalid pin config
// void UTEST_MDIO_enuSetPinValue_InvalidPinConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPinValue_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState) */
// // invalid port num
// void UTEST_MDIO_enuSetPortValue_InvalidPortNum(void);
// // invalid port config
// void UTEST_MDIO_enuSetPortValue_InvalidPortConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPortValue_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, uint8_t* Add_uint8PtrPinValue) */
// // invalid port num
// void UTEST_MDIO_enuGetPinValue_InvalidPortNum(void);
// // invalid pin num
// void UTEST_MDIO_enuGetPinValue_InvalidPinNum(void);
// // invalid pin config
// void UTEST_MDIO_enuGetPinValue_InvalidPinConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuGetPinValue_ValidInputs(void);

#endif