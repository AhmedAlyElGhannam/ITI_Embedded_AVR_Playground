#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "MDIO.h"
#include "MPORT.h"


int main(void)
{
	
	/* testing MPORT functions */

	// setting direction
	MPORT_voidInit();

	// defining variables to store buttons' states
	uint8_t Local_uint8Button1State;
	uint8_t Local_uint8Button2State;
	uint8_t Local_uint8Button3State;
	while (true)
	{
		// reading button 1 state (PA0)
		MDIO_enuGetPinValue(MDIO_PORTA, MDIO_PIN0, &Local_uint8Button1State);
		if (Local_uint8Button1State == MDIO_PIN_HIGH)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, MDIO_PIN_HIGH); // led 1 (PB0)
		else if (Local_uint8Button1State == MDIO_PIN_LOW)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, MDIO_PIN_LOW); // led 1 (PB0)

		_delay_ms(50);

		// reading button 2 state (PA1)
		MDIO_enuGetPinValue(MDIO_PORTA, MDIO_PIN1, &Local_uint8Button2State);
		if (Local_uint8Button2State == MDIO_PIN_HIGH)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN1, MDIO_PIN_HIGH); // led 2 (PB1)
		else if (Local_uint8Button2State == MDIO_PIN_LOW)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN1, MDIO_PIN_LOW); // led 2 (PB1)

		_delay_ms(50);	

		// reading button 3 state (PA2)
		MDIO_enuGetPinValue(MDIO_PORTA, MDIO_PIN2, &Local_uint8Button3State);
		if (Local_uint8Button3State == MDIO_PIN_HIGH)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN2, MDIO_PIN_HIGH); // led 3 (PB2)
		if (Local_uint8Button3State == MDIO_PIN_LOW)
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN2, MDIO_PIN_LOW); // led 3 (PB2)

		_delay_ms(50);
	}

	return 0;
}

