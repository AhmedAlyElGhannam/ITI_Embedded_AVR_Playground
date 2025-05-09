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
	uint16_t Local_uint16Counter = 0;

	/* calling H7SEGMENT API to display 0 on both 7 segment displays */
	H7SEGMENT_enuWriteDigit(H7SEGMENT_COUNTER_UNITS, Local_uint16Counter);

	while (true)
	{
		HSWITCH_enuGetSwitchValue(HSWITCH_RESET, &Local_uint8Button1State);
		if (Local_uint8Button1State == HSWITCH_PRESSED)
		{
			Local_uint16Counter++;
			H7SEGMENT_enuWriteMultiDigitValue(Local_uint16Counter);
		}

		_delay_ms(150);
	}

	return 0;
}

