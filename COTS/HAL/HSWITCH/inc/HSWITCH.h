#ifndef HSWITCH_H
#define HSWITCH_H

typedef enum
{
    PORTA = 0x00,
    PORTB,
    PORTC,
    PORTD = 0x03,
} HSWITCH_enuPortName_t;

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
} HSWITCH_enuPinName_t;

typedef enum 
{
	HSWITCH_PRESSED = 0x01,
	HSWITCH_RELEASED = 0x00,
} HSWITCH_enuSwitchAction_t;

typedef enum
{
	HSWITCH_OK = 0x00,
    HSWITCH_INVALID_SWITCH_NAME,
    HSWITCH_NULL_PTR,
    HSWITCH_INVALID_SWITCH_STATE,
} HSWITCH_enuErrorStatus_t;

typedef enum 
{
    HSWITCH_INTERNAL_PULLUP,
    HSWITCH_EXTERNAL_PULLUP,
    HSWITCH_EXTERNAL_PULLDOWN,
} HSWITCH_enuSwitchConnection_t;

typedef enum
{
    HSWITCH_RESET = 0x00,
    HSWITCH_LED_CONTROL = 0x01
} HSWITCH_enuSwitchName_t;

#endif