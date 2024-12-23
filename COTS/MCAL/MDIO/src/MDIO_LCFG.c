#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MDIO_PBCFG.h"
#include "MDIO_LCFG.h"
#include "MDIO.h"

// array that stores pin configuration and sets it at runtime
MDIO_enuPinConfig_t MDIO_enuArrPinConfig[MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS] = 
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
