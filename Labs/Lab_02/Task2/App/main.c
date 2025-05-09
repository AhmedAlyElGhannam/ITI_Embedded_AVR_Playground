#define F_CPU 	8000000UL
#include <util/delay.h>
#include "MDIO.h"

#define TRUE 	1
#define FALSE	0



void main(void)
{
	MDIO_enuSetPortConfigration(MDIO_PORTA, PORT_OUTPUT);
	MDIO_enuSetPinConfigration(MDIO_PORTD, MDIO_PIN3, INPUT);
	u8 button_state;
	u8 flag = FALSE;
	MDIO_enuSetPortValue(MDIO_PORTA, ALL_LOW);
	while (TRUE)
	{
		MDIO_enuGetPinValue(MDIO_PORTD, MDIO_PIN3, &button_state);
		if (button_state == HIGH)
		{
			for (u16 counter = 0; counter <= 0xFF; counter++)
			{
				MDIO_enuSetPortValue(MDIO_PORTA, counter);
				_delay_ms(500);
			}
			MDIO_enuSetPortValue(MDIO_PORTA, ALL_LOW);
		}	
		_delay_ms(100);
	}
}


