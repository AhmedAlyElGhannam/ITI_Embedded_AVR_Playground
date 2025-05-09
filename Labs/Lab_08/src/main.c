#include "std_types.h"
#include <util/delay.h>
#include "MPORT.h"
#include "HLCD.h"
#include "HKEYPAD.h"

int main(void)
{
	
	/* testing Keypad functions */
	HLCD_structLCDObject_t local_structLCDObject = 
	{
		.HLCD_DataPort = PORTA,
		.HLCD_ConfigPort = PORTB,
		.HLCD_RS = PIN0,
		.HLCD_RW = PIN1,
		.HLCD_E  = PIN2
	};

	HKEYPAD_structKeypadObject_t local_structKeypadObject = 
	{
		.RowPinsPort = PORTC,
		.ColPinsPort = PORTC,
		.RowPinsArr = {PIN0, PIN1, PIN2, PIN3},
		.ColPinsArr = {PIN4, PIN5, PIN6, PIN7}
	};

	uint8_t local_uint8PressedKey = '\0';


	MPORT_voidInit();

	/* calling init function for LCD */
	HLCD_enuInit(&local_structLCDObject);

	/* calling init function for keypad */
	HKEYPAD_enuInit(&local_structKeypadObject);

	/* printing a string on first line */
	HLCD_enuWriteString(&local_structLCDObject, "Kotuwaru!");

	/* shifting to line 2 */
	HLCD_enuGoToXY(&local_structLCDObject, HLCD_COL_00, HLCD_LINE_02);

	/* printing an int 
	HLCD_enuWriteInteger(&local_structLCDObject, 86); */

	/* keep it stuck in an infinite loop */
	while (true)
	{
		/* getting keypad press and printing the pressed char on LCD */
		HKEYPAD_enuGetPressedKey(&local_structKeypadObject, &local_uint8PressedKey);
		
		switch (local_uint8PressedKey)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
				HLCD_enuWriteCharacter(&local_structLCDObject, local_uint8PressedKey);				
			break;
		}

		local_uint8PressedKey = '\0';
	}

	return 0;
}

