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
#include "HSWITCH.h"
#include "HSWITCH_LCFG.h"


HSWITCH_structSwitchConfig_t Global_HSWITCH_structSwitchConfigArr[NUM_OF_SWITCHES] =
{
    [HSWITCH_RESET] = 
    {
        .portNum = PORTA,
        .pinNum = PIN1,
        .connection = HSWITCH_EXTERNAL_PULLUP
    },
    [HSWITCH_LED_CONTROL] = 
    {
        .portNum = PORTB,
        .pinNum = PIN1,
        .connection = HSWITCH_INTERNAL_PULLUP
    }
};

