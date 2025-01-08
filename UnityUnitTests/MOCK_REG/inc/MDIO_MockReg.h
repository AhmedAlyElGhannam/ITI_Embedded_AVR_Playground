#ifndef MDIO_MOCK_REG_H
#define MDIO_MOCK_REG_H

// struct to represent each DIO port registers (in the same order as their addresses)
typedef struct 
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} MDIO_strPortRegElement_t;

#define PORTA_NUM      0
#define PORTB_NUM      1
#define PORTC_NUM      2
#define PORTD_NUM      3

// macro to find port address (returns mock reg base address)
#define MDIO_GET_PORT_ADD(PORT_NUM)                             \
        ((PORT_NUM) == PORTA_NUM ? &MOCK_PORTA :               \
         (PORT_NUM) == PORTB_NUM ? &MOCK_PORTB :               \
         (PORT_NUM) == PORTC_NUM ? &MOCK_PORTC :               \
         (PORT_NUM) == PORTD_NUM ? &MOCK_PORTD : NULL)         \

#endif
