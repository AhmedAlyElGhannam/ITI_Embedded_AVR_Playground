#ifndef HSWITCH_LCFG_H
#define HSWITCH_LCFG_H

typedef struct 
{
    uint8_t portNum;
    uint8_t pinNum;
    HSWITCH_enuSwitchConnection_t connection;
} HSWITCH_structSwitchConfig_t;

#define NUM_OF_SWITCHES     2
#define FIRST_SWITCH        HSWITCH_RESET

#endif
