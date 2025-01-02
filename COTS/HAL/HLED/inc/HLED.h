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
	HLED_OK = 0x00,
} HLED_enuLEDStatus_t;

#endif