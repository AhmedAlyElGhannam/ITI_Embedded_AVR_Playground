#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "MDIO.h"
#include "MPORT.h"


int main(void)
{
	
	/* testing MPORT functions */

	// setting direction
	MPORT_enuSetPinDirection(MPORT_PIN_A0, MPORT_PORT_PIN_INPUT); // button
	MPORT_enuSetPinDirection(MPORT_PIN_B0, MPORT_PORT_PIN_OUTPUT); // led

	// setting mode for button pin
	MPORT_enuSetPinMode(MPORT_PIN_A0, MPORT_PIN_MODE_INPUT_PULLDOWN); // pull-down configuration for button

	// defining variable for button state
	uint8_t Local_uint8Button1State;

	while (true)
	{
		// reading button 1 state (PA0)
		MDIO_enuGetPinValue(MDIO_PORTA, MDIO_PIN0, &Local_uint8Button1State);
		if (Local_uint8Button1State == MDIO_PIN_HIGH)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, MDIO_PIN_HIGH); 
		else if (Local_uint8Button1State == MDIO_PIN_LOW)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, MDIO_PIN_LOW); 

		_delay_ms(500);
	}

	return 0;
}


