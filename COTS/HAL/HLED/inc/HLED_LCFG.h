#ifndef HLED_LCFG_H
#define HLED_LCFG_H

typedef enum 
{
    HLED_FORWARD = 0x01,
    HLED_REVERSE = 0x00,
} HLED_enuLEDConnection_t;

typedef struct 
{
    uint8_t portNum;
    uint8_t pinNum;
    HLED_enuLEDConnection_t connection;
} HLED_structLEDConfig_t;

#define NUM_OF_LEDS     3

#define LED_START       0
#define LED_STOP        1
#define LED_ALERT       2

#endif
