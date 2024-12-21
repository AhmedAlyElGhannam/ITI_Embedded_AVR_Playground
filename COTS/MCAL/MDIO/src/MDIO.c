#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MDIO_PBCFG.h"
#include "MDIO_LCFG.h"
#include "MDIO.h"

MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuConfigration)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if ((Copy_enuPortNum > MDIO_PIN7) || (Copy_enuPortNum < MDIO_PIN0))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if ((Copy_enuPinNum > MDIO_PORTD) || (Copy_enuPinNum < MDIO_PORTA))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if ((Copy_enuConfigration != OUTPUT) && (Copy_enuConfigration != INPUT_PULLUP) && (Copy_enuConfigration != INPUT_PULLDOWN))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	switch (Copy_enuPortNum)
	{
		case MDIO_PORTA:
			if (Copy_enuConfigration == OUTPUT)
			{
				SET_BIT(DDRA, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLUP)
			{
				CLR_BIT(DDRA, Copy_enuPinNum);
				SET_BIT(PORTA, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLDOWN)
			{
				CLR_BIT(DDRA, Copy_enuPinNum);
				CLR_BIT(PORTA, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTB:
			if (Copy_enuConfigration == OUTPUT)
			{
				SET_BIT(DDRB, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLUP)
			{
				CLR_BIT(DDRB, Copy_enuPinNum);
				SET_BIT(PORTB, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLDOWN)
			{
				CLR_BIT(DDRB, Copy_enuPinNum);
				CLR_BIT(PORTB, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTC:
			if (Copy_enuConfigration == OUTPUT)
			{
				SET_BIT(DDRC, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLUP)
			{
				CLR_BIT(DDRC, Copy_enuPinNum);
				SET_BIT(PORTC, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLDOWN)
			{
				CLR_BIT(DDRC, Copy_enuPinNum);
				CLR_BIT(PORTC, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTD:
			if (Copy_enuConfigration == OUTPUT)
			{
				SET_BIT(DDRD, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLUP)
			{
				CLR_BIT(DDRD, Copy_enuPinNum);
				SET_BIT(PORTD, Copy_enuPinNum);
			}
			else if (Copy_enuConfigration == INPUT_PULLDOWN)
			{
				CLR_BIT(DDRD, Copy_enuPinNum);
				CLR_BIT(PORTD, Copy_enuPinNum);
			}
		break;
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuConfigration)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if ((Copy_enuPortNum > MDIO_PORTD) || (Copy_enuPortNum < MDIO_PORTA))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if ((Copy_enuConfigration != PORT_OUTPUT) && (Copy_enuConfigration != PORT_INPUT))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	switch (Copy_enuPortNum)
	{
		case MDIO_PORTA:
			DDRA = Copy_enuConfigration;
		break;

		case MDIO_PORTB:
			DDRB = Copy_enuConfigration;
		break;

		case MDIO_PORTC:
			DDRC = Copy_enuConfigration;
		break;

		case MDIO_PORTD:
			DDRD = Copy_enuConfigration;
		break;
	}

out:
	return ret_enumStatus;
}


MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuState)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if ((Copy_enuPortNum > MDIO_PIN7) || (Copy_enuPortNum < MDIO_PIN0))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if ((Copy_enuPinNum > MDIO_PORTD) || (Copy_enuPinNum < MDIO_PORTA))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if ((Copy_enuState != HIGH) && (Copy_enuState != LOW))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	switch (Copy_enuPortNum)
	{
		case MDIO_PORTA:
			if (Copy_enuState == HIGH)
			{
				SET_BIT(PORTA, Copy_enuPinNum);
			}
			else if (Copy_enuState == LOW)
			{
				CLR_BIT(PORTA, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTB:
			if (Copy_enuState == HIGH)
			{
				SET_BIT(PORTB, Copy_enuPinNum);
			}
			else if (Copy_enuState == LOW)
			{
				CLR_BIT(PORTB, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTC:
			if (Copy_enuState == HIGH)
			{
				SET_BIT(PORTC, Copy_enuPinNum);
			}
			else if (Copy_enuState == LOW)
			{
				CLR_BIT(PORTC, Copy_enuPinNum);
			}
		break;

		case MDIO_PORTD:
			if (Copy_enuState == HIGH)
			{
				SET_BIT(PORTD, Copy_enuPinNum);
			}
			else if (Copy_enuState == LOW)
			{
				CLR_BIT(PORTD, Copy_enuPinNum);
			}
		break;
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if ((Copy_enuPortNum > MDIO_PORTD) || (Copy_enuPortNum < MDIO_PORTA))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if ((Copy_enuPortState > ALL_HIGH) || (Copy_enuPortState < ALL_LOW))
	{
		ret_enumStatus = MDIO_INVALID_PARAM;
		goto out;
	}

	switch (Copy_enuPortNum)
	{
		case MDIO_PORTA:
			PORTA = Copy_enuPortState;
		break;

		case MDIO_PORTB:
			PORTB = Copy_enuPortState;
		break;

		case MDIO_PORTC:
			PORTC = Copy_enuPortState;
		break;

		case MDIO_PORTD:
			PORTD = Copy_enuPortState;
		break;
	}

out:
	return ret_enumStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_pu8PinValue)
{
	MDIO_enuErrorStatus_t ret_enumStatus = MDIO_OK;

	if ((Copy_enuPortNum > MDIO_PIN7) || (Copy_enuPortNum < MDIO_PIN0))
	{
		ret_enumStatus = MDIO_INVALID_PIN;
		goto out;
	}

	if ((Copy_enuPinNum > MDIO_PORTD) || (Copy_enuPinNum < MDIO_PORTA))
	{
		ret_enumStatus = MDIO_INVALID_PORT;
		goto out;
	}

	if (Add_pu8PinValue == NULL)
	{
		ret_enumStatus = MDIO_NULL_PTR;
		goto out;
	}

	switch (Copy_enuPortNum)
	{
		case MDIO_PORTA:
			(*Add_pu8PinValue) = GET_BIT(PINA, Copy_enuPinNum);
		break;

		case MDIO_PORTB:
			(*Add_pu8PinValue) = GET_BIT(PINB, Copy_enuPinNum);
		break;

		case MDIO_PORTC:
			(*Add_pu8PinValue) = GET_BIT(PINC, Copy_enuPinNum);
		break;

		case MDIO_PORTD:
			(*Add_pu8PinValue) = GET_BIT(PIND, Copy_enuPinNum);
		break;
	}

out:
	return ret_enumStatus;
}
