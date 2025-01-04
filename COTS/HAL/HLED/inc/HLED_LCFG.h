#ifndef HLED_LCFG_H
#define HLED_LCFG_H

typedef struct 
{
    uint8_t portNum;
    uint8_t pinNum;
    HLED_enuLEDConnection_t connection;
} HLED_structLEDConfig_t;

#define NUM_OF_LEDS     3
#define FIRST_LED       HLED_START

#endif
