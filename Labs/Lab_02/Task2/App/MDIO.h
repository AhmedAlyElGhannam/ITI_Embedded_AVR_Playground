#ifndef DIO_H
#define DIO_H

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

typedef float f32;
typedef double f64;

#define NULL ((void*)0)

#define SET_BIT(X, POS) (X |= (0x01 << POS))
#define CLR_BIT(X, POS) (X &= ~(0x01 << POS))
#define TOG_BIT(X, POS) (X ^= (0x01 << POS))
#define GET_BIT(X, POS) ((X >> POS) & 0x01)

#define PINA (*(volatile u8*)(0x39))
#define DDRA (*(volatile u8*)(0x3A))
#define PORTA (*(volatile u8*)(0x3B))

#define PINB (*(volatile u8*)(0x36))
#define DDRB (*(volatile u8*)(0x37))
#define PORTB (*(volatile u8*)(0x38))

#define PINC (*(volatile u8*)(0x33))
#define DDRC (*(volatile u8*)(0x34))
#define PORTC (*(volatile u8*)(0x35))

#define PIND (*(volatile u8*)(0x30))
#define DDRD (*(volatile u8*)(0x31))
#define PORTD (*(volatile u8*)(0x32))

#define SFIOR (*(volatile u8*)(0x50))

// enum for error status
typedef enum
{
	MDIO_OK,
	MDIO_INVALID_PARAM,
	MDIO_INVALID_PIN,
	MDIO_INVALID_PORT,
	MDIO_NULL_PTR,
	MDIO_NOK,
} MDIO_enuErrorStatus_t;

// enum for pin numbers
typedef enum
{
	MDIO_PIN0 = 0x00,
	MDIO_PIN1,
	MDIO_PIN2,
	MDIO_PIN3,
	MDIO_PIN4,
	MDIO_PIN5,
	MDIO_PIN6,
	MDIO_PIN7,
} MDIO_enuPinNum_t;

// enum for port numbers
typedef enum
{
	MDIO_PORTA = 0x00,
	MDIO_PORTB,
	MDIO_PORTC,
	MDIO_PORTD,
	MDIO_PORTE,
	MDIO_PORTF,
} MDIO_enuPortNum_t;

// enum for pin configuration
typedef enum
{
	OUTPUT = 0x00,
	INPUT_PULLUP,
	INPUT_PULLDOWN,
	INPUT,
} MDIO_enuPinConfig_t;

// enum for port configuration
typedef enum
{
	PORT_OUTPUT = 0xFF,
	PORT_INPUT = 0x00,
} MDIO_enuPortConfig_t;

// enum for logic levels (pins)
typedef enum
{
	HIGH = 1,
	LOW = 0
} MDIO_enuPinState_t;

// enum for logic levels (ports)
typedef enum
{
	ALL_LOW = 0x00,
	ALL_HIGH = 0xFF
} MDIO_enuPortState_t;


MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuConfigration);
MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuConfigration);
MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuState);
MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState);
MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, u8* Add_pu8PinValue);

#endif