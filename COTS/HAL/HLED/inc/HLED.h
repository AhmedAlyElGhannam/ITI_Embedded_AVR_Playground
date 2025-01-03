#ifndef HLED_H
#define HLED_H

typedef enum
{
    PORTA = 0x00,
    PORTB,
    PORTC,
    PORTD = 0x03,
} HLED_enuPortName_t;

typedef enum
{
    PIN0 = 0x00,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7 = 0x07,
} HLED_enuPinName_t;

typedef enum 
{
	HLED_ON = 0x01,
	HLED_OFF = 0x00,
} HLED_enuLEDValue_t;

typedef enum 
{
    HLED_FORWARD = 0x01,
    HLED_REVERSE = 0x00,
} HLED_enuLEDConnection_t;

typedef enum
{
	HLED_OK = 0x00,
    HLED_INVALID_LED_NAME,
    HLED_INVALID_LED_VALUE,
} HLED_enuErrorStatus_t;

/* always start LED name from 0x00 */
typedef enum
{
    HLED_START = 0x00,
    HLED_ALERT,
    HLED_STOP = 0x02,
} HLED_enuLEDName_t;

void HLED_voidInit(void);
HLED_enuErrorStatus_t HLED_uint8SetLEDValue(uint8_t Copy_uint8LEDName, HLED_enuLEDValue_t Copy_uint8LEDValue);

#endif