#include "bit_math.h"
#ifdef UNIT_TESTING_MODE
    /* header files that are included only when in testing mode */
	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
	#include "MDIO_MockReg.h"

	/* mock base addresses for ports using extern (only in testing mode) */
	extern MDIO_strPortRegElement_t MOCK_PORTA;
	extern MDIO_strPortRegElement_t MOCK_PORTB;
	extern MDIO_strPortRegElement_t MOCK_PORTC;
	extern MDIO_strPortRegElement_t MOCK_PORTD;
#else
    #include "std_types.h"
    #include "MDIO_Registers.h"
#endif
#include "MPORT_PBCFG.h"
#include "MPORT.h"
#include "MPORT_LCFG.h"


/* array that stores pin configuration and sets it at runtime */
MPORT_structPortPinDirAndMode_t MPORT_enuArrPinConfig[MPORT_NUM_OF_ALL_PINS] = 
{
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_INPUT, MPORT_PIN_MODE_INPUT_PULLDOWN},
    {MPORT_PORT_PIN_OUTPUT, MPORT_PIN_MODE_NONE}
};
