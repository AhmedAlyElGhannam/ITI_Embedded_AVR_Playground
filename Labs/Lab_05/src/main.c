#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "HLED.h"
#include "HSWITCH.h"


int main(void)
{
	
	/* testing HLED && HSWITCH functions */

	/* setting direction */
	HLED_voidInit();
	HSWITCH_voidInit();

	/* defining variables to store buttons' states */
	uint8_t Local_uint8Button1State;
	uint8_t Local_uint8Button2State;
	
	while (true)
	{
		/* reading button 1 state (PA0) */
		HSWITCH_enuGetSwitchValue(HSWITCH_RESET, &Local_uint8Button1State);
		if (Local_uint8Button1State == HSWITCH_PRESSED)
			HLED_uint8SetLEDValue(HLED_START, HLED_ON);
		else if (Local_uint8Button1State == HSWITCH_RELEASED)
			HLED_uint8SetLEDValue(HLED_START, HLED_OFF);

		_delay_ms(50);

		/* reading button 1 state (PA0) */
		HSWITCH_enuGetSwitchValue(HSWITCH_LED_CONTROL, &Local_uint8Button2State);
		if (Local_uint8Button2State == HSWITCH_PRESSED)
			HLED_uint8SetLEDValue(HLED_STOP, HLED_ON);
		else if (Local_uint8Button2State == HSWITCH_RELEASED)
			HLED_uint8SetLEDValue(HLED_STOP, HLED_OFF);

		_delay_ms(50);

	}

	return 0;
}

