#include "std_types.h"
#include "MDIO_PBCFG.h"
#include "MDIO.h"
#include "HKEYPAD_PBCFG.h"
#include "HKEYPAD_LCFG.h"
#include "HKEYPAD.h"
#include <util/delay.h>


#define IS_NULL_PTR(PTR)                ((PTR) == NULL)
#define IS_INVALID_PORT(PORT)           ((PORT) > PORTD)
#define IS_KEYPAD_BUTTON_PRESSED(BTN)   ((BTN) == BUTTON_PRESSED) /* pressed is pulled down to 0 */

extern const uint8_t HKEYPAD_uint8CharLayout1Arr[HKEYPAD_NO_OF_ROWS][HKEYPAD_NO_OF_COLS];

HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(HKEYPAD_structKeypadObject_t* Ptr_structKeypadObj)
{
    HKEYPAD_enuErrorStatus_t Local_enuErrorStatus = HKEYPAD_OK;
    uint8_t Local_uint8RowIter;
    uint8_t Local_uint8ColIter;

    if(IS_NULL_PTR(Ptr_structKeypadObj))
    {
        Local_enuErrorStatus = HKEYPAD_NULL_PTR;
    }
    else if (IS_INVALID_PORT(Ptr_structKeypadObj->RowPinsPort) || IS_INVALID_PORT(Ptr_structKeypadObj->ColPinsPort))
    {
        Local_enuErrorStatus = HKEYPAD_INVALID_PARAM;
    }
    else 
    {
        /* set all output pins to logic 1 by default */
        for (Local_uint8ColIter = 0; Local_uint8ColIter < HKEYPAD_NO_OF_COLS; Local_uint8ColIter++)
        {
            MDIO_enuSetPinValue(Ptr_structKeypadObj->ColPinsPort, Ptr_structKeypadObj->ColPinsArr[Local_uint8ColIter], MDIO_PIN_HIGH);
        }
    }

    return Local_enuErrorStatus;
}

HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(HKEYPAD_structKeypadObject_t* Ptr_structKeypadObj, uint8_t* Ptr_uint8PressedKey)
{
    HKEYPAD_enuErrorStatus_t Local_enuErrorStatus = HKEYPAD_OK;
    uint8_t Local_uint8RowIter;
    uint8_t Local_uint8ColIter;
    uint8_t Local_uint8ButtonState = '\0';
    bool Local_boolIsKeyPressRead = false;

    if(IS_NULL_PTR(Ptr_structKeypadObj) || IS_NULL_PTR(Ptr_uint8PressedKey))
    {
        Local_enuErrorStatus = HKEYPAD_NULL_PTR;
    }
    else if (IS_INVALID_PORT(Ptr_structKeypadObj->RowPinsPort) || IS_INVALID_PORT(Ptr_structKeypadObj->ColPinsPort))
    {
        Local_enuErrorStatus = HKEYPAD_INVALID_PARAM;
    }
    else 
    {
        for (Local_uint8ColIter = 0; Local_uint8ColIter < HKEYPAD_NO_OF_COLS; Local_uint8ColIter++)
	    {
            /* set output pin to logic 0 */
	    	MDIO_enuSetPinValue(Ptr_structKeypadObj->ColPinsPort, Ptr_structKeypadObj->ColPinsArr[Local_uint8ColIter], MDIO_PIN_LOW);
	    	for (Local_uint8RowIter = 0; Local_uint8RowIter < HKEYPAD_NO_OF_ROWS; Local_uint8RowIter++)
	    	{
	    		MDIO_enuGetPinValue(Ptr_structKeypadObj->RowPinsPort, Ptr_structKeypadObj->RowPinsArr[Local_uint8RowIter], &Local_uint8ButtonState);
	    		/* read pin */
	    		if (IS_KEYPAD_BUTTON_PRESSED(Local_uint8ButtonState))
	    		{
	    			_delay_ms(25); /* debouncing protecc */
	    			MDIO_enuGetPinValue(Ptr_structKeypadObj->RowPinsPort, Ptr_structKeypadObj->RowPinsArr[Local_uint8RowIter], &Local_uint8ButtonState);
	    			if (IS_KEYPAD_BUTTON_PRESSED(Local_uint8ButtonState))
	    			{
	    				/* handling long pressing */
	    				while (IS_KEYPAD_BUTTON_PRESSED(Local_uint8ButtonState))
	    					MDIO_enuGetPinValue(Ptr_structKeypadObj->RowPinsPort, Ptr_structKeypadObj->RowPinsArr[Local_uint8RowIter], &Local_uint8ButtonState);
	    				
                        (*Ptr_uint8PressedKey) = HKEYPAD_uint8CharLayout1Arr[Local_uint8RowIter][Local_uint8ColIter];
                        Local_boolIsKeyPressRead = true;
                        break;
	    			}
                    else {}
	    		}
                else {}
	    	}
	    	/* set output pin to logic 1 again */
	    	MDIO_enuSetPinValue(Ptr_structKeypadObj->ColPinsPort, Ptr_structKeypadObj->ColPinsArr[Local_uint8ColIter], MDIO_PIN_HIGH);

            /* break if press is read successfully */
            if (Local_boolIsKeyPressRead == true)
            {
                break;
            }
            else {}
	    }
    }

    return Local_enuErrorStatus;
}
