#include "std_types.h"
#include <util/delay.h>
#include "MPORT.h"
#include "HLCD.h"

int main(void)
{
	
	/* testing HLCD functions */
	HLCD_structLCDObject_t local_structLCDObject = 
	{
		.HLCD_DataPort = PORTA,
		.HLCD_ConfigPort = PORTB,
		.HLCD_RS = PIN0,
		.HLCD_RW = PIN1,
		.HLCD_E  = PIN2
	};

	MPORT_voidInit();

	/* calling init function */
	HLCD_enuInit(&local_structLCDObject);

	/* printing a string on first line */
	HLCD_enuWriteString(&local_structLCDObject, "Kotuwaru!");

	/* shifting to line 2 */
	HLCD_enuGoToXY(&local_structLCDObject, HLCD_COL_00, HLCD_LINE_02);

	/* printing an int */
	HLCD_enuWriteInteger(&local_structLCDObject, 86);

	/* keep it stuck in an infinite loop */
	while (true)
	{
		
	}

	return 0;
}

