#ifndef HSWITCH_H
#define HSWITCH_H

#ifndef HAL_PORT_AND_PIN_NAMES
#define HAL_PORT_AND_PIN_NAMES
typedef enum
{
    PORTA = 0x00,
    PORTB,
    PORTC,
    PORTD = 0x03,
} HAL_enuPortName_t;

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
} HAL_enuPinName_t;
#endif

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


void HSWITCH_voidInit(void);
HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchValue(uint8_t Copy_uint8SwitchName, uint8_t* Add_uint8PtrSwitchState);

#endif