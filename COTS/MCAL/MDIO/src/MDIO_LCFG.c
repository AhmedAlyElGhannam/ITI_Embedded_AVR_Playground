#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MDIO_PBCFG.h"
#include "MDIO_LCFG.h"
#include "MDIO.h"

// macros to extract port && pin numbers from iterator
#define EXTRACT_PORT_NUM(ITER)      ((ITER) / MDIO_NUM_OF_PINS)
#define EXTRACT_PIN_NUM(ITER)       ((ITER) % MDIO_NUM_OF_PINS)

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

void MDIO_voidInit(void)
{
    uint8_t Local_uint8Iter;
    MDIO_enuPortNum_t Local_enuPortNum;
    MDIO_enuPinNum_t Local_enuPinNum;

    for (Local_uint8Iter = 0; Local_uint8Iter < (MDIO_NUM_OF_PORTS * MDIO_NUM_OF_PINS); Local_uint8Iter++)
    {
        Local_enuPortNum = EXTRACT_PORT_NUM(Local_uint8Iter);
        Local_enuPinNum = EXTRACT_PIN_NUM(Local_uint8Iter);
        MDIO_enuSetPinConfigration(Local_enuPortNum, Local_enuPinNum, MDIO_enuArrPinConfig[Local_uint8Iter]);
    }

    return;
}