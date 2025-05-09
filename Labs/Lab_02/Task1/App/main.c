#define F_CPU 	8000000UL
#include <util/delay.h>
#include "MDIO.h"

#define TRUE 	1
#define HIGH 	1
#define LOW 	0



void main(void)
{
	MDIO_enuSetPinConfigration(MDIO_PORTB, MDIO_PIN0, OUTPUT);
	MDIO_enuSetPinConfigration(MDIO_PORTB, MDIO_PIN1, INPUT);
	u8 button_state;
	while (TRUE)
	{
		MDIO_enuGetPinValue(MDIO_PORTB, MDIO_PIN1, &button_state);
		if (button_state == HIGH)
		{
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, HIGH);
		}
		else if (button_state == LOW)
		{
			MDIO_enuSetPinValue(MDIO_PORTB, MDIO_PIN0, LOW);
		}
		//_delay_ms(1000);
		
	}
}


