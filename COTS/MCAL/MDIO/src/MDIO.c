#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MDIO_PBCFG.h"
#include "MDIO.h"

// macros for checking function arguments
#define IS_INVALID_PORT_NUM(X)			((((MDIO_enuPortNum_t)X) > MDIO_PORTD) || (((MDIO_enuPortNum_t)X) < MDIO_PORTA))
#define IS_INVALID_PIN_NUM(X)			((((MDIO_enuPinNum_t)X) > MDIO_PIN7) || (((MDIO_enuPinNum_t)X) < MDIO_PIN0))
#define IS_INVALID_PIN_CONFIG(X)		((((MDIO_enuPinConfig_t)X) != MDIO_PIN_OUTPUT) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT_PULLUP) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT))
#define IS_INVALID_PORT_CONFIG(X)		(((((MDIO_enuPortConfig_t)X)) != MDIO_PORT_OUTPUT) && (((MDIO_enuPortConfig_t)X) != MDIO_PORT_INPUT))
#define IS_INVALID_PIN_STATE(X)			((((MDIO_enuPinState_t)X) != MDIO_PIN_HIGH) && (((MDIO_enuPinState_t)X) != MDIO_PIN_LOW))
#define IS_INVALID_PORT_STATE(X)		((((MDIO_enuPortState_t)X) != MDIO_PORT_HIGH) && (((MDIO_enuPortState_t)X) != MDIO_PORT_LOW))
#define IS_INVALID_PTR(X)				((X) == NULL)

// accessing pin configuration array defined in LCFG.c file
extern MDIO_enuPinConfig_t MDIO_enuArrPinConfig[MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS];

// macros to extract port && pin numbers from iterator in MDIO_voidInit function
#define EXTRACT_PORT_NUM(ITER)      ((ITER) / MDIO_NUM_OF_PINS)
#define EXTRACT_PIN_NUM(ITER)       ((ITER) % MDIO_NUM_OF_PINS)

void MPORT_voidInit(void)
{
    uint8_t Local_uint8Iter;
    MDIO_enuPortNum_t Local_enuPortNum;
    MDIO_enuPinNum_t Local_enuPinNum;

	// replace MDIO_NUM_OF_PORTS with MDIO_NUM_OF_ENABLED_PORTS 
    for (Local_uint8Iter = 0; Local_uint8Iter < (MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS); Local_uint8Iter++)
    {
        Local_enuPortNum = EXTRACT_PORT_NUM(Local_uint8Iter);
        Local_enuPinNum = EXTRACT_PIN_NUM(Local_uint8Iter);
        MDIO_enuSetPinConfigration(Local_enuPortNum, Local_enuPinNum, MDIO_enuArrPinConfig[Local_uint8Iter]);
    }

    return;
}

MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuPinConfig)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PIN_NUM(Copy_enuPinNum))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PIN_CONFIG(Copy_enuPinConfig))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	if (Copy_enuPinConfig == MDIO_PIN_OUTPUT)
	{
		SET_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
	}
	else if (Copy_enuPinConfig == MDIO_PIN_INPUT_PULLUP)
	{
		CLR_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
		SET_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}
	else if (Copy_enuPinConfig == MDIO_PIN_INPUT)
	{
		CLR_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
		CLR_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuPortConfig)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PORT_CONFIG(Copy_enuPortConfig))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	(Local_strPtrCurrPort->DDR) = Copy_enuPortConfig;

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuPinState)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PIN_NUM(Copy_enuPinNum))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PIN_STATE(Copy_enuPinState))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	if (Copy_enuPinState == MDIO_PIN_HIGH)
	{
		SET_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}
	else if (Copy_enuPinState == MDIO_PIN_LOW)
	{
		CLR_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PORT_STATE(Copy_enuPortState))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	(Local_strPtrCurrPort->PORT) = Copy_enuPortState;

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, uint8_t* Add_uint8PtrPinValue)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PIN_NUM(Copy_enuPinNum))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PTR(Add_uint8PtrPinValue))
	{
		ret_enumStatus = MDIO_NULL_PTR;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	(*Add_uint8PtrPinValue) = GET_BIT(Local_strPtrCurrPort->PIN, Copy_enuPinNum);

out:
	return ret_enumStatus;
}