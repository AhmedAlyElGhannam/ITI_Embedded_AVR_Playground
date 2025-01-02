#include "bit_math.h"
/* to include right reg .h file during testing */
#ifdef UNIT_TESTING_MODE	
	/* header files that are included only when in testing mode */
	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
	#include "MDIO_MockReg.h"

	/* mock base addresses for ports using extern (only in testing mode) */
	extern MDIO_strPortRegElement_t MOCK_PORTA;
	extern MDIO_strPortRegElement_t MOCK_PORTB;
	extern MDIO_strPortRegElement_t MOCK_PORTC;
	extern MDIO_strPortRegElement_t MOCK_PORTD;
#else
	#include "std_types.h"
	#include "MDIO_Registers.h"
#endif
#include "MDIO_PBCFG.h"
#include "MPORT_LCFG.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HLED_LCFG.h"
#include "HLED.h"


/* macros for checking function arguments */
#define IS_INVALID_PORT_NUM(X)			((((MDIO_enuPortNum_t)X) > MDIO_PORTD) || (((MDIO_enuPortNum_t)X) < MDIO_PORTA))
#define IS_INVALID_PIN_NUM(X)			((((MDIO_enuPinNum_t)X) > MDIO_PIN7) || (((MDIO_enuPinNum_t)X) < MDIO_PIN0))
#define IS_INVALID_PIN_CONFIG(X)		((((MDIO_enuPinConfig_t)X) != MDIO_PIN_OUTPUT) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT_PULLUP) && (((MDIO_enuPinConfig_t)X) != MDIO_PIN_INPUT))
#define IS_INVALID_PORT_CONFIG(X)		(((((MDIO_enuPortConfig_t)X)) != MDIO_PORT_OUTPUT) && (((MDIO_enuPortConfig_t)X) != MDIO_PORT_INPUT))
#define IS_INVALID_PIN_STATE(X)			((((MDIO_enuPinState_t)X) != MDIO_PIN_HIGH) && (((MDIO_enuPinState_t)X) != MDIO_PIN_LOW))
#define IS_INVALID_PORT_STATE(X)		((((MDIO_enuPortState_t)X) != MDIO_PORT_HIGH) && (((MDIO_enuPortState_t)X) != MDIO_PORT_LOW))
#define IS_INVALID_PTR(X)				((X) == NULL)

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
uint8_t HLED_uint8SetLEDValue(uint8_t Copy_uint8LEDName, HLED_enuLEDValue_t Copy_uint8LEDValue)
{
	uint8_t ret_uint8Status = HLED_OK;



out:
	return ret_uint8Status;
}