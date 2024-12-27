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

	while (true)
	{
		// reading button 1 state (PA0)


			MDIO_enuSetPinValue(MDIO_PORTA, MDIO_PIN0, MDIO_PIN_HIGH); 
		_delay_ms(500);
			MDIO_enuSetPinValue(MDIO_PORTA, MDIO_PIN0, MDIO_PIN_LOW); 

		_delay_ms(500);
	}

	return 0;
}


