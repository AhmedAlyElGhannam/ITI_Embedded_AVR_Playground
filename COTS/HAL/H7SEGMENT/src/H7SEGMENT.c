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
#include "MDIO_PBCFG.h"
#include "MPORT_LCFG.h"
#include "MDIO.h"
#include "MPORT.h"
#include "H7SEGMENT.h"
#include "H7SEGMENT_LCFG.h"


/* macros for checking function arguments */
#define IS_INVALID_7SEGMENT_NAME(X)			((((HLED_enuLEDName_t)X) > (NUM_OF_LEDS - 1)) || (((HLED_enuLEDName_t)X) < (FIRST_LED)))
#define IS_INVALID_7SEGMENT_DIGIT(X)		((((HLED_enuLEDValue_t)X) != HLED_ON) && (((HLED_enuLEDValue_t)X) != HLED_OFF))
#define IS_CONNECTED_7SEG_COUNT_LESS_THAN_NUM_OF_DIGITS(X)	(((uint8_t)X) > NUM_OF_7SEG)

/* macros for checking 7 segment mode of operation */
#define IS_7SEGMENT_COMMON_ANODE(X)		(((H7SEGMENT_enu7SegmentConnection_t)X) == H7SEGMENT_COMMON_ANODE)
#define IS_7SEGMENT_COMMON_CATHODE(X)	(((H7SEGMENT_enu7SegmentConnection_t)X) == H7SEGMENT_COMMON_CATHODE)

/* macro to count the number of digits in a number */
#define COUNT_NUM_OF_DIGITS_IN_VAL(X, COUNT)		\
					do {					\
  						  (X) /= 10;			\
  						  ++(COUNT);			\
  					   } while ((X) != 0)		

/* macro to define the number of displayable values */
#define H7SEGMENT_NUM_OF_DISPLAYABLE_VALS	10

/* accessing led configuration array defined in LCFG.c file */
extern H7SEGMENT_struct7SegmentConfig_t Global_H7SEGMENT_struct7SegmentConfigArr[NUM_OF_7SEG];

/* defining array for translating actual numbers to values written to 7 segment */
static uint8_t H7SEGMENT_uint8ArrNumberToVal[H7SEGMENT_NUM_OF_DISPLAYABLE_VALS] = 
{
	H7SEGMENT_ZERO,
	H7SEGMENT_ONE,
	H7SEGMENT_TWO,
	H7SEGMENT_THREE,
	H7SEGMENT_FOUR,
	H7SEGMENT_FIVE,
	H7SEGMENT_SIX,
	H7SEGMENT_SEVEN,
	H7SEGMENT_EIGHT,
	H7SEGMENT_NINE
};

/*
 * @brief	Initializes all 7 segments as per the configuration defined in the array located in LCFG.c
 *                   
 * @param	None
 *				
 * @return  None   
 */
void H7SEGMENT_voidInit(void)
{
	/* defining variables for port pin && iterator */
	uint8_t Local_uint8CurrPortPin = 0x00;
	uint8_t Local_uint8Iter1;
	uint8_t Local_uint8Iter2;

	for (Local_uint8Iter = 0; Local_uint8Iter < NUM_OF_LEDS; Local_uint8Iter++)
	{
		/* looping over all 7 segment pins to initialize them */
		for (Local_uint8Iter2 = H7SEGMENT_PIN_a; Local_uint8Iter2 <= H7SEGMENT_PIN_dot; Local_uint8Iter2++)
		{
			/* extract and combine port && pin numbers into a single value to pass to MPORT function */
			Local_uint8CurrPortPin = SET_HIGH_NIB_TO_VAL(Local_uint8CurrPortPin, Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].portNum) + SET_LOW_NIB_TO_VAL(Local_uint8CurrPortPin, Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].pinsConnection[Local_uint8Iter2]);

			/* configure this 7 segment pin as output */
			MPORT_enuSetPinDirection(Local_uint8CurrPortPin, MPORT_PORT_PIN_OUTPUT);
		}

		/* depending on 7 segment connection initialize all 7 segment LEDs to OFF */
		if (IS_7SEGMENT_COMMON_ANODE(Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].connection))
		{
			/* initialize pins to low */
			MDIO_enuSetPortValue(Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].portNum, MDIO_PORT_HIGH);
		}
		else if (IS_7SEGMENT_COMMON_CATHODE(Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].connection))
		{
			/* initialize pins to high */
			MDIO_enuSetPortValue(Global_H7SEGMENT_struct7SegmentConfigArr[Local_uint8Iter].portNum, MDIO_PORT_LOW);
		}
		else {}
	}
}


/*
 * @brief	Writes a digit from 0 to 9 on 7 segment display
 *                   
 * @param (in) Copy_uint8_7SegmentName -> 7 segment name as defined by the user in H7SEGMENT_enu7SegNames_t enum
 * 
 * @param (in) Copy_uint8Digit -> number that will be displayed on 7 segment [0, 9].
 *				
 * @return H7SEGMENT_OK || H7SEGMENT_INVALID_7SEG_NAME || H7SEGMENT_INVALID_DIGIT || H7SEGMENT_NOK
 */
H7SEGMENT_enuErrorStatus_t H7SEGMENT_enuWriteDigit(uint8_t Copy_uint8_7SegmentName, HLED_enuLEDValue_t Copy_uint8Digit)
{
    /* defining a variable to store return address */
	H7SEGMENT_enuErrorStatus_t ret_enuStatus = H7SEGMENT_OK;

	/* defining variable to store the actual state of LED according to connection */
	uint8_t Local_uint8_7SegmentPinsValue;

	/* defining iterator for the loop ahead */
	uint8_t Local_uint8Iter;

	/* defining a temp variable to store what state is going to be written in pin */
	uint8_t Local_uint8TempPinState;

	if (IS_INVALID_7SEGMENT_NAME(Copy_uint8_7SegmentName))
	{
		/* do not continue if passed 7 seg name is not valid */
		ret_enuStatus = H7SEGMENT_INVALID_7SEG_NAME;
	}
	else if (IS_INVALID_7SEGMENT_DIGIT(Copy_uint8Digit))
	{
		/* do not continue if passed digit is out of the bounds [0, 9] */
		ret_enuStatus = H7SEGMENT_INVALID_DIGIT;
	}
	else /* all arguments are valid */
	{
		/* converting the digit to what is going to actually be displayed */
		Local_uint8_7SegmentPinsValue = H7SEGMENT_uint8ArrNumberToVal[Copy_uint8Digit];
		
		for (Local_uint8Iter = PIN0; Local_uint8Iter <= PIN7; Local_uint8Iter++)
		{
 			/* determine if pin is going to be set to HIGH or LOW depending on 7 segment connection */
			if (IS_7SEGMENT_COMMON_ANODE(Global_H7SEGMENT_struct7SegmentConfigArr[Copy_uint8_7SegmentName].connection))
			{
				/* ON is LOW && OFF is HIGH */
				Local_uint8TempPinState = !GET_BIT(Local_uint8_7SegmentPinsValue, Local_uint8Iter);
			}
			else if (IS_7SEGMENT_COMMON_CATHODE(Global_H7SEGMENT_struct7SegmentConfigArr[Copy_uint8_7SegmentName].connection))
			{
				/* ON is HIGH && OFF is LOW */
				Local_uint8TempPinState = GET_BIT(Local_uint8_7SegmentPinsValue, Local_uint8Iter);
			}
			else {}

			/* loop over all 7 segment pins and set their values accordingly via MDIO API */
			ret_enuStatus = MDIO_enuSetPinValue(
				Global_HLED_structLEDConfigArr[Copy_uint8LEDName].portNum,
				Local_uint8Iter,
				Local_uint8TempPinState
			);

			/* checking error status of MDIO_enuSetPinValue */
			if (ret_enuStatus != MDIO_OK)
			{
				/* if MDIO API's return is not OK, break the loop */
				ret_enuStatus = H7SEGMENT_NOK;
				break;
			}
			else 
			{
				/* error status is restored to OK */
				ret_enuStatus = H7SEGMENT_OK;
			}
		}
	}

	return ret_enuStatus;
}


/*
 * @brief	Writes a multip-digit number on multiple 7 segment displays
 *                   
 * @param (in) Copy_uint16MultiDigitValue -> 7 segment name as defined by the user in H7SEGMENT_enu7SegNames_t enum
 *				
 * @return H7SEGMENT_OK || H7SEGMENT_LIMIT_ERROR || H7SEGMENT_NOK
 */
H7SEGMENT_enuErrorStatus_t H7SEGMENT_enuWriteMultiDigitValue(uint16_t Copy_uint16MultiDigitValue)
{
	/* defining a variable to store return address */
	H7SEGMENT_enuErrorStatus_t ret_enuStatus = H7SEGMENT_OK;

	/* defining iterator for upcoming loop */
	uint8_t Local_uint8Iter;

	/* defining a temporary variable to hold the passed value */
	uint16_t Local_uint16TempMultiDigitValue = Copy_uint16MultiDigitValue;

	/* defining variable to store digit count of passed value */
	uint8_t Local_uint8ValueDigitCount = 0;

	/* counting the number of digits in the passed value */
	COUNT_NUM_OF_DIGITS_IN_VAL(Local_uint16TempMultiDigitValue, Local_uint8ValueDigitCount);

	/* defining an array to store the separate digits (max 5 for uint16) */
	uint8_t Local_uint8ArrSeparateValueDigits[5] = {0};

	/* digit count must not exceed the number of connected 7 segments */
	if (IS_CONNECTED_7SEG_COUNT_LESS_THAN_NUM_OF_DIGITS(Local_uint8ValueDigitCount))
	{
		/* cannot display this number with the number of connected 7 segment displays */
		ret_enuStatus = H7SEGMENT_LIMIT_ERROR;
	}
	else /* argument is valid */
	{
		/* counting the number of digits in the passed value && extracting each digit */
		while (Copy_uint16MultiDigitValue != 0)
		{
			/* extracting the first digit of passed value and storing it in arr */
			Local_uint8ArrSeparateValueDigits[Local_uint8ValueDigitCount] = Copy_uint16MultiDigitValue % 10;

			/* deleting the extracted digit from the value */
			Copy_uint16MultiDigitValue /= 10;
		}

		/* displaying passed value's digits on appropriate count of 7 segments */
		for (Local_uint8Iter = 0; Local_uint8Iter < NUM_OF_7SEG; Local_uint8Iter++)
		{
			/* call H7SEGMENT_enuWriteDigit and pass the digit + the 7 segment display name that will display it */
			ret_enuStatus = H7SEGMENT_enuWriteDigit(
				Local_uint8Iter,
				Local_uint8ArrSeparateValueDigits[Local_uint8Iter]
			);
		}
	}

	return ret_enuStatus;
}