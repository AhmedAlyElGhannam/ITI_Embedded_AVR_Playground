#include "HSCHEDULER.h"
#include "HSCHEDULER_LCFG.h"


HSCHEDULER_structRunnable_t HSCHEDULER_structRunnableArr[NUM_OF_RUNNABLES] = 
{
    [RUNNABLE_LED] = 
    {
        .period = 1000U,
        .firstDelay = 0,
        .cbf = APP_voidToggleLED
    },
};
