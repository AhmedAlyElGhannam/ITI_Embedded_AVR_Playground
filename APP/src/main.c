#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "MDIO.h"
#include "MPORT.h"


int main(void)
{
	
	/* testing MPORT functions */

	// setting direction

	MPORT_enuSetPinDirection(MPORT_PIN_A1, MPORT_PORT_PIN_OUTPUT); // led




	// defining variable for button state


	while (true)
	{
		// reading button 1 state (PA0)


			MDIO_enuSetPinValue(MDIO_PORTA, MDIO_PIN1, MDIO_PIN_HIGH); 
		_delay_ms(500);
			MDIO_enuSetPinValue(MDIO_PORTA, MDIO_PIN1, MDIO_PIN_LOW); 

		_delay_ms(500);
	}

	return 0;
}


