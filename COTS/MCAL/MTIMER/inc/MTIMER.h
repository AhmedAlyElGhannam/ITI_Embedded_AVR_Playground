#ifndef MTIMER_H
#define MTIMER_H

typedef enum 
{
    TIMER0,
    TIMER1,
    TIMER2,
    NUM_OF_TIMERS,
} MTIMER_enuTimers_t;

typedef enum
{
	MTIMER_OK = 0,
	MTIMER_INVALID_PARAM,
	MTIMER_INVALID_PIN,
	MTIMER_INVALID_PORT,
	MTIMER_NULL_PTR,
	MTIMER_NOK,
} MTIMER_enuErrorStatus_t;

typedef enum 
{
    TIMER_CTC_MODE = 0U,
    TIMER_OVF_MODE,
    TIMER_PWM_PHASE_CORRECT_MODE,
    TIMER_FAST_PWM_MODE,
} MTIMER_enuModeOfOperation_t;

typedef enum 
{
    TIMER_CLK_SEL_NO_CLK = 0U,
    TIMER_CLK_SEL_NO_PRES,
    TIMER_CLK_SEL_DIV_BY_8,
    TIMER_CLK_SEL_DIV_BY_64,
    TIMER_CLK_SEL_DIV_BY_256,
    TIMER_CLK_SEL_DIV_BY_1024,
    TIMER_CLK_SEL_EXT_CLK_FALLING_EDGE,
    TIMER_CLK_SEL_EXT_CLK_RISING_EDGE = 7U,
} MTIMER_enuClockSelection_t;

typedef enum 
{
    TIMER_INT_ENABLE = 1U,
    TIMER_INT_DISABLE = !TIMER_INT_ENABLE,
} MTIMER_enuInterruptOptions_t;

typedef struct 
{
    MTIMER_enuModeOfOperation_t timerMode;
    MTIMER_enuClockSelection_t timerClkSel;
    MTIMER_enuInterruptOptions_t timerIntState;
} MTIMER_structTimerConfig_t;



#endif