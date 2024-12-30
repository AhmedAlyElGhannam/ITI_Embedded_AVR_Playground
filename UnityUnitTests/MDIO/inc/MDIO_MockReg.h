#ifndef MDIO_MOCK_REG_H
#define MDIO_MOCK_REG_H

// struct to represent each DIO port registers (in the same order as their addresses)
typedef struct 
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} MDIO_strPortRegElement_t;

// defining 4 pointers to reg structs instead of using actual base addresses during tests
MDIO_strPortRegElement_t* MOCK_PORTA;
MDIO_strPortRegElement_t* MOCK_PORTB;
MDIO_strPortRegElement_t* MOCK_PORTC;
MDIO_strPortRegElement_t* MOCK_PORTD;

// macro to find port address (returns mock reg base address)
#define MDIO_GET_PORT_ADD(PORT_NUM)                          \
        ((PORT_NUM) == MDIO_PORTA ? MOCK_PORTA :             \
         (PORT_NUM) == MDIO_PORTB ? MOCK_PORTB :             \
         (PORT_NUM) == MDIO_PORTC ? MOCK_PORTC : MOCK_PORTD) 

#endif
