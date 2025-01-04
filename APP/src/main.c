#define F_CPU 	8000000UL
#include <util/delay.h>
#include "std_types.h"
#include "HLED.h"


int main(void)
{
	
	/* testing HLED functions */

	// setting direction
	HLED_voidInit();
	
	while (true)
	{
		HLED_uint8SetLEDValue(HLED_STOP, HLED_ON);
		_delay_ms(500);
		HLED_uint8SetLEDValue(HLED_STOP, HLED_OFF);
		_delay_ms(500);
	}

	return 0;
}

