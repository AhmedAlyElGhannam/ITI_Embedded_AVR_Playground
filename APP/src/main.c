#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "HLED.h"
#include "HSWITCH.h"
#include "H7SEGMENT.h"
#include "MDIO.h"


int main(void)
{
	
	/* testing H7SEGMENT && HSWITCH functions */

	/* calling init functions */
	HSWITCH_voidInit();
	H7SEGMENT_voidInit(); 
	HLED_voidInit();

	/* defining variable to store button state */
	uint8_t Local_uint8Button1State;

	/* defining a variable to display its value on 7 segment */
	uint16_t Local_uint16Counter = 88;

	/* calling H7SEGMENT API to display 0 on both 7 segment displays */
	H7SEGMENT_enuWriteMultiDigitValue(Local_uint16Counter);
	/* MDIO_enuSetPortValue(MDIO_PORTA, MDIO_PORT_HIGH); */

	while (true)
	{
/*
		HLED_uint8SetLEDValue(HLED_START, HLED_ON);
		_delay_ms(500);
		HLED_uint8SetLEDValue(HLED_START, HLED_OFF);
		_delay_ms(500);*/
		/* reading button 1 state (PC0) */
		HSWITCH_enuGetSwitchValue(HSWITCH_RESET, &Local_uint8Button1State);
		if (Local_uint8Button1State == HSWITCH_PRESSED)
		{
			Local_uint16Counter++;
			H7SEGMENT_enuWriteMultiDigitValue(Local_uint16Counter);
		}

		_delay_ms(50);
	}

	return 0;
}

