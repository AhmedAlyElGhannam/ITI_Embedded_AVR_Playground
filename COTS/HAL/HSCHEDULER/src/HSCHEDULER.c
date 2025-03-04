#include "std_types.h"
#include "MGIE.h"
#include "MTIMER.h"

/* scheduler init */
// init timer0 and choose ovf mode
// set callback that loops over them
// set time
// start timer

void HSCHEDULER_voidInit(void)
{
    cli();
    MTIMER_enuInit(TIMER0);
    MTIMER_enuSetTimerCallBack(HSCHEDULER_voidStartRunnable, MGIE_TIMER0_OVERFLOW);
    MTIMER_enuSetTimeMs(1); 
    sei();
    while(true);
}


void HSCHEDULER_voidStartRunnable(void)
{

}
/* scheduler cbf */
// loop over cbfs
// if passed ms_counter % their periodic_time == 0 && first_delay happened -> execute 