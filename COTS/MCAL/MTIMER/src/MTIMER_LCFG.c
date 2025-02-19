#include "bit_math.h"
#include "std_types.h"
#include "MTIMER_Registers.h"
#include "MTIMER.h"

MTIMER_structTimerConfig_t global_structTimers[NUM_OF_TIMERS] = 
{
    [TIMER0] = {
        .timerClkSel = TIMER_CLK_SEL_DIV_BY_64,
        .timerMode = TIMER_CTC_MODE,
        .timerIntState = TIMER_INT_ENABLE
    }
};