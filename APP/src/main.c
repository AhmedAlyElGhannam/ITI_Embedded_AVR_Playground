#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "MDIO.h"

#define TRUE 	1
#define HIGH 	1
#define LOW 	0



int main(void)
{
	MDIO_enuSetPinConfigration(MDIO_PORTB, MDIO_PIN7, MDIO_PIN_OUTPUT);
	while (TRUE)
	{
		MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN7, MDIO_PIN_HIGH);
		_delay_ms(500);
		MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN7, MDIO_PIN_LOW);
		_delay_ms(500);
		
	}

	return 0;
}


