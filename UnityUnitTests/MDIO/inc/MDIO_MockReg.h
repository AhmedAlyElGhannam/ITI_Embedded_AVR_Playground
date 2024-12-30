#ifndef MDIO_MOCK_REG_H
#define MDIO_MOCK_REG_H

// struct to represent each DIO port registers (in the same order as their addresses)
typedef struct 
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} MDIO_strPortRegElement_t;

// macro to find port address (returns mock reg base address)
#define MDIO_GET_PORT_ADD(PORT_NUM)                             \
        ((PORT_NUM) == MDIO_PORTA ? &MOCK_PORTA :               \
         (PORT_NUM) == MDIO_PORTB ? &MOCK_PORTB :               \
         (PORT_NUM) == MDIO_PORTC ? &MOCK_PORTC :               \
         (PORT_NUM) == MDIO_PORTD ? &MOCK_PORTD : NULL)         \

#endif
