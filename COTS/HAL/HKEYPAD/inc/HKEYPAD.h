#ifndef HKEYPAD_H
#define HKEYPAD_H


/* enum for port and pin numbers --- common for all HAL so they must be defined once */
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
    HKEYPAD_OK,
    HKEYPAD_NOK,
    HKEYPAD_NULL_PTR,
    HKEYPAD_INVALID_PARAM,
} HKEYPAD_enuErrorStatus_t;

typedef enum 
{
    BUTTON_PRESSED = 0U,
    BUTTON_RELEASED = 1U,
} HKEYPAD_enuKeypadButtonState_;

typedef struct 
{
    HAL_enuPortName_t RowPinsPort;
    HAL_enuPortName_t ColPinsPort;
    HAL_enuPinName_t  RowPinsArr[HKEYPAD_NO_OF_ROWS]; /* configured as input pullup*/
    HAL_enuPinName_t  ColPinsArr[HKEYPAD_NO_OF_COLS]; /* configured as output */
} HKEYPAD_structKeypadObject_t;

extern HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(HKEYPAD_structKeypadObject_t* Ptr_structKeypadObj);
extern HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(HKEYPAD_structKeypadObject_t* Ptr_structKeypadObj, uint8_t* Ptr_uint8PressedKey);


#endif