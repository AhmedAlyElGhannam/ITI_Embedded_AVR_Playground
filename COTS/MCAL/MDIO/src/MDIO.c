#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MDIO_PBCFG.h"
#include "MDIO_LCFG.h"
#include "MDIO.h"

// macros for checking function arguments
#define IS_INVALID_PORT_NUM(X)			((((MDIO_enuPortNum_t)X) > MDIO_PORTD) || (((MDIO_enuPortNum_t)X) < MDIO_PORTA))
#define IS_INVALID_PIN_NUM(X)			((((MDIO_enuPinNum_t)X) > MDIO_PIN7) || (((MDIO_enuPinNum_t)X) < MDIO_PIN0))
#define IS_INVALID_PIN_CONFIG(X)		((((MDIO_enuPinConfig_t)X) != MDIO_PIN_OUTPUT) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT_PULLUP) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT))
#define IS_INVALID_PORT_CONFIG(X)		(((((MDIO_enuPortConfig_t)X)) != MDIO_PORT_OUTPUT) && (((MDIO_enuPortConfig_t)X) != MDIO_PORT_INPUT))
#define IS_INVALID_PIN_STATE(X)			((((MDIO_enuPinState_t)X) != MDIO_PIN_HIGH) && (((MDIO_enuPinState_t)X) != MDIO_PIN_LOW))
#define IS_INVALID_PORT_STATE(X)		((((MDIO_enuPortState_t)X) != MDIO_PORT_HIGH) && (((MDIO_enuPortState_t)X) != MDIO_PORT_LOW))
#define IS_INVALID_PTR(X)				((X) == NULL)


MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuPinConfigration)
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

	if (IS_INVALID_PIN_CONFIG(Copy_enuPinConfigration))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	if (Copy_enuPinConfigration == MDIO_PIN_OUTPUT)
	{
		SET_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
	}
	else if (Copy_enuPinConfigration == MDIO_PIN_INPUT_PULLUP)
	{
		CLR_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
		SET_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}
	else if (Copy_enuPinConfigration == MDIO_PIN_INPUT)
	{
		CLR_BIT(Local_strPtrCurrPort->DDR, Copy_enuPinNum);
		CLR_BIT(Local_strPtrCurrPort->PORT, Copy_enuPinNum);
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuPortConfigration)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if (IS_INVALID_PORT_NUM(Copy_enuPortNum))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (IS_INVALID_PORT_CONFIG(Copy_enuPortConfigration))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	MDIO_strPortRegElement_t* Local_strPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

	(Local_strPtrCurrPort->DDR) = Copy_enuPortConfigration;

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