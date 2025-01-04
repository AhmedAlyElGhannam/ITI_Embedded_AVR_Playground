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
#include "HLED.h"
#include "HLED_LCFG.h"


/* macros for checking function arguments */
#define IS_INVALID_LED_NAME(X)			((((HLED_enuLEDName_t)X) > (NUM_OF_LEDS - 1)) || (((HLED_enuLEDName_t)X) < (FIRST_LED)))
#define IS_INVALID_LED_VALUE(X)			((((HLED_enuLEDValue_t)X) != HLED_ON) && (((HLED_enuLEDValue_t)X) != HLED_OFF))

/* accessing led configuration array defined in LCFG.c file */
extern HLED_structLEDConfig_t Global_HLED_structLEDConfigArr[NUM_OF_LEDS];

/*uses MPORT*/
void HLED_voidInit(void)
{
	uint8_t Local_uint8CurrPortPin;
	uint8_t Local_uint8Iter;

	for (Local_uint8Iter = 0; Local_uint8Iter < NUM_OF_LEDS; Local_uint8Iter++)
	{
		Local_uint8CurrPortPin = (Global_HLED_structLEDConfigArr[Local_uint8Iter].portNum << 4) + (Global_HLED_structLEDConfigArr[Local_uint8Iter].pinNum);
		MPORT_enuSetPinDirection(Local_uint8CurrPortPin, MPORT_PORT_PIN_OUTPUT);
	}
}

/*uses MDIO*/
HLED_enuErrorStatus_t HLED_uint8SetLEDValue(uint8_t Copy_uint8LEDName, HLED_enuLEDValue_t Copy_uint8LEDValue)
{
	HLED_enuErrorStatus_t ret_enuStatus = HLED_OK;

	if (IS_INVALID_LED_NAME(Copy_uint8LEDName))
	{
		ret_enuStatus = HLED_INVALID_LED_NAME;
	}
	else if (IS_INVALID_LED_VALUE(Copy_uint8LEDValue))
	{
		ret_enuStatus = HLED_INVALID_LED_VALUE;
	}
	else
	{
		uint8_t Local_uint8LEDActualState = Copy_uint8LEDValue;
		if ((Global_HLED_structLEDConfigArr[Copy_uint8LEDName].connection) == HLED_FORWARD)
		{
			Local_uint8LEDActualState = Copy_uint8LEDValue;
		}
		else if ((Global_HLED_structLEDConfigArr[Copy_uint8LEDName].connection) == HLED_REVERSE)
		{
			Local_uint8LEDActualState = !Copy_uint8LEDValue;
		}
		else {}

		ret_enuStatus = MDIO_enuSetPinValue(
			Global_HLED_structLEDConfigArr[Copy_uint8LEDName].portNum,
			Global_HLED_structLEDConfigArr[Copy_uint8LEDName].pinNum,
			Local_uint8LEDActualState
		);
	}

	return ret_enuStatus;
}