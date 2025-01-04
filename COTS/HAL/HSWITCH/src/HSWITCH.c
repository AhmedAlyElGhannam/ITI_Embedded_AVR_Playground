#include "bit_math.h"
/* to include right reg .h file during testing */
#ifdef UNIT_TESTING_MODE	
	/* header files that are included only when in testing mode */
	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
#else
	#include "std_types.h"
#endif
#include "MDIO_PBCFG.h"
#include "MPORT_LCFG.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HSWITCH_LCFG.h"
#include "HSWITCH.h"


/* macros for checking function arguments */
#define IS_INVALID_SWITCH_NAME(X)					((((uint8_t)X) > NUM_OF_SWITCHES) || (((uint8_t)X) < FIRST_SWITCH))
#define IS_INVALID_SWITCH_STATE(X)					((((HLED_enuLEDValue_t)X) != HLED_ON) && (((HLED_enuLEDValue_t)X) != HLED_OFF))
#define IS_CONNECTION_HSWITCH_INTERNAL_PULLUP(X)	(((HSWITCH_enuSwitchConnection_t)X) == HSWITCH_INTERNAL_PULLUP)
#define IS_INVALID_PTR(X)							((X) == NULL)

/* accessing led configuration array defined in LCFG.c file */
extern HSWITCH_structSwitchConfig_t Global_HSWITCH_structSwitchConfigArr[NUM_OF_SWITCHES];

/*uses MPORT*/
void HLED_voidInit(void)
{
	uint8_t Local_uint8CurrPortPin;
	uint8_t Local_uint8Iter;

	for (Local_uint8Iter = 0; Local_uint8Iter < NUM_OF_SWITCHES; Local_uint8Iter++)
	{
		Local_uint8CurrPortPin = (Global_HSWITCH_structSwitchConfigArr[Local_uint8Iter].portNum << 4) + (Global_HSWITCH_structSwitchConfigArr[Local_uint8Iter].pinNum);
		MPORT_enuSetPinDirection(Local_uint8CurrPortPin, MPORT_PORT_PIN_INPUT);
		if (IS_CONNECTION_HSWITCH_INTERNAL_PULLUP(Global_HSWITCH_structSwitchConfigArr[Local_uint8Iter].connection))
		{
			MPORT_enuSetPinMode(Local_uint8CurrPortPin, MPORT_PIN_MODE_INPUT_PULLUP);
		}
		else {}
	}
}

/*uses MDIO*/
HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchValue(uint8_t Copy_uint8SwitchName, uint8_t* Add_uint8PtrSwitchState)
{
	HSWITCH_enuErrorStatus_t ret_enuStatus = HSWITCH_OK;

	if (IS_INVALID_SWITCH_NAME(Copy_uint8SwitchName))
	{
		ret_enuStatus = HSWITCH_INVALID_SWITCH_NAME;
	}
	else if (IS_INVALID_PTR(Add_uint8PtrSwitchState))
	{
		ret_enuStatus = HSWITCH_NULL_PTR;
	}
	else
	{
		uint8_t Local_uint8SwitchNormalState;
		/* @TODO: change expected value for pressed based on connection */
		// if (IS_FORWARD_CONNECTION(Copy_uint8LEDName))
		// {
		// 	Local_uint8LEDActualState = Copy_uint8LEDValue;
		// }
		// else if (IS_REVERSE_CONNECTION(Copy_uint8LEDName))
		// {
		// 	Local_uint8LEDActualState = !Copy_uint8LEDValue;
		// }
		// else {}
		ret_enuStatus = MDIO_enuGetPinValue(
			Global_HSWITCH_structSwitchConfigArr[Copy_uint8SwitchName].portNum,
			Global_HSWITCH_structSwitchConfigArr[Copy_uint8SwitchName].pinNum,
			Add_uint8PtrSwitchState
		);
	}

	return ret_enuStatus;
}