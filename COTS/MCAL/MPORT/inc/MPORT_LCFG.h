#ifndef MPORT_LCFG_H
#define MPORT_LCFG_H
#include "MPORT.h"

typedef struct 
{
    MPORT_enuPortPinDir_t dir;
    MPORT_enuPortPinMode_t mode;
} MPORT_structPortPinDirAndMode_t;

#define MPORT_NUM_OF_ALL_PINS   32

#endif