#include "std_types.h"
#include "HKEYPAD_PBCFG.h"
#include "HKEYPAD_LCFG.h"
#include "HKEYPAD.h"

/* write your keypad key layout here */

const uint8_t HKEYPAD_uint8CharArr[HKEYPAD_NO_OF_ROWS][HKEYPAD_NO_OF_COLS] = 
{
	{'7', '8', '9', '/'},   
	{'4', '5', '6', '*'},   
	{'1', '2', '3', '-'},   
	{'C', '0', '=', '+'}    
};

const uint8_t HKEYPAD_uint8CharCodeArr[HKEYPAD_NO_OF_ROWS][HKEYPAD_NO_OF_COLS] = 
{ 							
	{KPD_SEVEN, KPD_EIGHT, KPD_NINE, KPD_DIV},   
	{KPD_FOUR, KPD_FIVE, KPD_SIX, KPD_MUL},   
	{KPD_ONE, KPD_TWO, KPD_THREE, KPD_SUB},   
	{KPD_CLR, KPD_ZERO, KPD_EQUAL, KPD_ADD}    
};
		