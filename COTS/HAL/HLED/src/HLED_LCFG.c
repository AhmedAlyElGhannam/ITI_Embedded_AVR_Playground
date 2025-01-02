#include "bit_math.h"
/* to include right reg .h file during testing */
#ifdef UNIT_TESTING_MODE	
	/* header files that are included only when in testing mode */
	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
#else
	#include "std_types.h"
#endif
#include "HLED_LCFG.h"
#include "HLED.h"

HLED_structLEDConfig_t Global_HLED_structLEDConfigArr[NUM_OF_LEDS] =
{
    [LED_START] = 
    {
        .portNum = PORTA,
        .pinNum = PIN0,
        .connection = HLED_FORWARD
    },
    [LED_STOP] = 
    {
        .portNum = PORTB,
        .pinNum = PIN0,
        .connection = HLED_FORWARD
    },
    [LED_ALERT] = 
    {
        .portNum = PORTC,
        .pinNum = PIN0,
        .connection = HLED_FORWARD
    }
};

