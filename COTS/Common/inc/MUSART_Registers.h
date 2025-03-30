#ifndef MUSART_REGISTERS_H
#define MUSART_REGISTERS_H

typedef struct 
{
    volatile uint8_t UBRRL; 
    volatile uint8_t UCSRB;
    volatile uint8_t UCSRA;
    volatile uint8_t UDR; /*0x2C*/
    const uint8_t reserved[18]; /*0x2D --> 0x3F*/
    volatile uint8_t UBRRH_UCSRC; /*0x40*/
} MUSART_Registers_t;

#define MUSART_BASE_ADDRESS ((volatile void*)(0x29))

#endif