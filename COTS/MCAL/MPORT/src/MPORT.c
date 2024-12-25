#include "std_types.h"
#include "bit_math.h"
#include "MDIO_Registers.h"
#include "MPORT_PBCFG.h"
#include "MPORT.h"


// defining number of pins per port
#define MPORT_NUM_OF_PINS   8

// macros for checking function arguments
#define IS_INVALID_PORT_NUM(X)			((((uint8_t)X) > 0x03) || (((uint8_t)X) < 0x00))
#define IS_INVALID_PIN_NUM(X)			((((uint8_t)X) > 0x07) || (((uint8_t)X) < 0x00))
#define IS_INVALID_PORT_PIN_DIR(X)		((((MPORT_enuPortPinDir_t)X) != MPORT_PORT_PIN_INPUT) && (((MPORT_enuPortPinDir_t)X) != MPORT_PORT_PIN_INPUT))
#define IS_INVALID_PORT_PIN_MODE(X)		((((MPORT_enuPortPinMode_t)X) != MPORT_PIN_MODE_INPUT_PULLUP) && (((MPORT_enuPortPinMode_t)X) != MPORT_PIN_MODE_INPUT_PULLDOWN) && (((MPORT_enuPortPinMode_t)X) != MPORT_PIN_MODE_UART))

// macros to extract port && pin numbers from iterator in MDIO_voidInit function
#define EXTRACT_PORT_NUM(PINXN)      ((PINXN) & (0xF0) >> 4)
#define EXTRACT_PIN_NUM(PINXN)       ((PINXN) & (0x0F))


MPORT_enuErrorStatus_t MPORT_enuSetPinDirection(MPORT_enuPortPin_t Copy_enuPortPinNum,  MPORT_enuPortPinDir_t  Copy_enuPortPinDir)
{
    // return var stores status
    MPORT_enuErrorStatus_t Ret_enuStatus = MPORT_OK;

    // extracting port and pin numbers
    uint8_t Local_uint8PortNum = EXTRACT_PORT_NUM(Copy_enuPortPinNum);
    uint8_t Local_uint8PinNum = EXTRACT_PIN_NUM(Copy_enuPortPinNum);
    
    // checking passed pin dir
    if (IS_INVALID_PORT_PIN_DIR(Copy_enuPortPinDir))
    {
        Ret_enuStatus = MPORT_ERROR_INVALID_DIRECTION;
        goto out;
    }

    // checking extracted pin && port nums
    if (IS_INVALID_PIN_NUM(Local_uint8PinNum) || IS_INVALID_PORT_NUM(Local_uint8PortNum))
    {
        Ret_enuStatus = MPORT_ERROR_INVALID_PIN;
        goto out;
    }

    // find port base address
    MDIO_strPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Local_uint8PortNum);

    // set specified direction
    switch (Copy_enuPortPinDir)
    {
        case MPORT_PORT_PIN_OUTPUT:
            SET_BIT(Local_structPtrCurrPort->DDR, Local_uint8PinNum);
        break;

        case MPORT_PORT_PIN_INPUT:
            CLR_BIT(Local_structPtrCurrPort->DDR, Local_uint8PinNum);
        break;
    }

out:
    return Ret_enuStatus;
}

MPORT_enuErrorStatus_t MPORT_enuSetPinMode(MPORT_enuPortPin_t Copy_enuPortPinNum, MPORT_enuPortPinMode_t Copy_enuPortPinMode)
{
    // return var stores status
    MPORT_enuErrorStatus_t Ret_enuStatus = MPORT_OK;

    // extracting port and pin numbers
    uint8_t Local_uint8PortNum = EXTRACT_PORT_NUM(Copy_enuPortPinNum);
    uint8_t Local_uint8PinNum = EXTRACT_PIN_NUM(Copy_enuPortPinNum);

    // checking extracted pin && port nums
    if (IS_INVALID_PIN_NUM(Local_uint8PinNum) || IS_INVALID_PORT_NUM(Local_uint8PortNum))
    {
        Ret_enuStatus = MPORT_ERROR_INVALID_PIN;
        goto out;
    }

    // checking pin mode
    if (IS_INVALID_PORT_PIN_MODE(Copy_enuPortPinMode))
    {
        Ret_enuStatus = MPORT_ERROR_INVALID_MODE;
        goto out;
    }

    // find port base address
    MDIO_strPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Local_uint8PortNum);

    // set specified direction
    switch (Copy_enuPortPinMode)
    {
        case MPORT_PIN_MODE_INPUT_PULLUP:
            SET_BIT(Local_structPtrCurrPort->PORT, Local_uint8PinNum);
        break;

        case MPORT_PIN_MODE_INPUT_PULLDOWN:
            CLR_BIT(Local_structPtrCurrPort->PORT, Local_uint8PinNum);
        break;

        case MPORT_PIN_MODE_UART:
            // Nothing for now
        break;
    }

out:
    return Ret_enuStatus;
}