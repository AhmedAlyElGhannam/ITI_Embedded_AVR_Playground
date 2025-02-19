#include "bit_math.h"
#include "std_types.h"
#include "MTIMER_Registers.h"
#include "MGIE.h"
#include "MTIMER.h"


extern MGIE_CallBackFunction_t MGIE_CallBackFunctions[MGIE_NUM_OF_INTERRUPTS];
extern MTIMER_structTimerConfig_t global_structTimers[NUM_OF_TIMERS];

static void MTIMER_voidTimer0Init(void)
{
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;
    volatile uint8_t local_uint8RegTemp = 0x00;

    /* timer mode */
    switch (global_structTimers[TIMER0].timerMode)
    {
        case TIMER_OVF_MODE:
            /* no need to do a thing */
        break;

        case TIMER_PWM_PHASE_CORRECT_MODE:
            /* set bit 3 */
            SET_BIT(local_uint8RegTemp, 3);
        break;

        case TIMER_CTC_MODE:
            /* set bit 6 */
            SET_BIT(local_uint8RegTemp, 6);
        break;

        case TIMER_FAST_PWM_MODE:
            /* set bit 3 & 6 */
            SET_BIT(local_uint8RegTemp, 3);
            SET_BIT(local_uint8RegTemp, 6);
        break;
    }

    /* clock selection */
    local_uint8RegTemp |= global_structTimers[TIMER0].timerClkSel;

    /* set temp value into register */
    MTIMER->TCCR0 = local_uint8RegTemp;

    /* configure interrupt based on mode of operation */
    MTIMER->TIMSK = (MTIMER->TIMSK & (~11U)) |  (global_structTimers[TIMER0].timerIntState << global_structTimers[TIMER0].timerMode);
}

static void MTIMER_voidTimer1Init(void)
{

}

static void MTIMER_voidTimer2Init(void)
{
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;
    volatile uint8_t local_uint8RegTemp = 0x00;

    /* timer mode */
    switch (global_structTimers[TIMER2].timerMode)
    {
        case TIMER_OVF_MODE:
            /* no need to do a thing */
        break;

        case TIMER_PWM_PHASE_CORRECT_MODE:
            /* set bit 3 */
            SET_BIT(local_uint8RegTemp, 3);
        break;

        case TIMER_CTC_MODE:
            /* set bit 6 */
            SET_BIT(local_uint8RegTemp, 6);
        break;

        case TIMER_FAST_PWM_MODE:
            /* set bit 3 & 6 */
            SET_BIT(local_uint8RegTemp, 3);
            SET_BIT(local_uint8RegTemp, 6);
        break;
    }

    /* clock selection */
    local_uint8RegTemp |= global_structTimers[TIMER2].timerClkSel;

    /* set temp value into register */
    MTIMER->TCCR2 = local_uint8RegTemp;

    /* configure interrupt based on mode of operation (NEEDS TO BE EDITED TO MAKE SURE IT IS OK) */
    MTIMER->TIMSK = (MTIMER->TIMSK & (~11U)) |  (global_structTimers[TIMER2].timerIntState << global_structTimers[TIMER2].timerMode);
}

MTIMER_enuErrorStatus_t MTIMER_enuInit(MTIMER_enuTimers_t copy_enuTimer)
{
    MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;

    switch (copy_enuTimer)
    {
        case TIMER0:
            ret_enuErrorStatus = MTIMER_voidTimer0Init();
        break;

        case TIMER1:
            ret_enuErrorStatus = MTIMER_voidTimer1Init();
        break;

        case TIMER2:
            ret_enuErrorStatus = MTIMER_voidTimer2Init();
        break;

        default:
            ret_enuErrorStatus = MTIMER_INVALID_PARAM;
    }

    return ret_enuErrorStatus;
}

MTIMER_enuErrorStatus_t MTIMER_enuSetOverflowVal(MTIMER_enuTimers_t copy_enuTimer, uint16_t copy_uint16PreloadVal)
{
    MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;

    switch (copy_enuTimer)
    {
        case TIMER0:
            MTIMER->TCNT0 = (uint8_t)(0xFF & copy_uint16PreloadVal);
        break;

        case TIMER1:
            MTIMER->TCNT1H = (uint8_t)((0xFF00 & copy_uint16PreloadVal) >> 8);
            MTIMER->TCNT1L = (uint8_t)(0xFF & copy_uint16PreloadVal);
        break;

        case TIMER2:
            MTIMER->TCNT2 = (uint8_t)(0xFF & copy_uint16PreloadVal);
        break;

        default:
            ret_enuErrorStatus = MTIMER_INVALID_PARAM;
    }

    return ret_enuErrorStatus;
}

MTIMER_enuErrorStatus_t MTIMER_enuSetClkSelection(MTIMER_enuTimers_t copy_enuTimer, MTIMER_enuClockSelection_t copy_enuClkSel)
{
    MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;

    switch (copy_enuClkSel)
    {
        case TIMER0:
            MTIMER->TCCR0 |= global_structTimers[TIMER0].timerClkSel;
        break;

        case TIMER1:
            MTIMER->TCCR1B |= global_structTimers[TIMER1].timerClkSel;
        break;

        case TIMER2:
            MTIMER->TCCR2 |= global_structTimers[TIMER2].timerClkSel;
        break;

        default:
            ret_enuErrorStatus = MTIMER_INVALID_PARAM;
    }

    return ret_enuErrorStatus;
}

MTIMER_enuErrorStatus_t MTIMER_enuSetOutputCompareVal(MTIMER_enuTimers_t copy_enuTimer, uint8_t copy_u8PreloadVal)
{
	MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;

    switch (copy_enuTimer)
    {
        case TIMER0:
            MTIMER->OCR0 = (uint8_t)(0xFF & copy_uint16PreloadVal);
        break;

        case TIMER1:
            /* will be left on hold for now */
            /*MTIMER->OCR1H = (uint8_t)((0xFF00 & copy_uint16PreloadVal) >> 8);
            MTIMER->OCR1L = (uint8_t)(0xFF & copy_uint16PreloadVal);*/
        break;

        case TIMER2:
            MTIMER->OCR2 = (uint8_t)(0xFF & copy_uint16PreloadVal);
        break;

        default:
            ret_enuErrorStatus = MTIMER_INVALID_PARAM;
    }

    return ret_enuErrorStatus;
}



MTIMER_enuErrorStatus_t MTIMER_enuGetCounterVal(MTIMER_enuTimers_t copy_enuTimer, uint16_t* ptr_uint16CounterVal)
{
    MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;
    volatile MTIMER_strRegisters_t* MTIMER = (volatile MTIMER_strRegisters_t*)MTIMER_BASE_ADDRESS;

    if (ptr_uint16CounterVal == NULL)
    {
        ret_enuErrorStatus = MTIMER_NULL_PTR;
    }
    else 
    {
        switch (copy_enuTimer)
        {
            case TIMER0:
                (*ptr_uint16CounterVal) = MTIMER->TCNT0;
            break;

            case TIMER1:
                /* will be left on hold for now */
                /*MTIMER->OCR1H = (uint8_t)((0xFF00 & copy_uint16PreloadVal) >> 8);
                MTIMER->OCR1L = (uint8_t)(0xFF & copy_uint16PreloadVal);*/
                (*ptr_uint16CounterVal) = (MTIMER->TCNT1L | (MTIMER->TCNT1H << 8));
            break;

            case TIMER2:
            (*ptr_uint16CounterVal) = MTIMER->TCNT2;
            break;

            default:
                ret_enuErrorStatus = MTIMER_INVALID_PARAM;
        }
    }
    
    return ret_enuErrorStatus;
}


MTIMER_enuErrorStatus_t MTIMER_enuSetTimerCallBack(MGIE_CallBackFunction_t ptr_ISR, MGIE_enuVectorTable_t copy_enuISRNum)
{
    MTIMER_enuErrorStatus_t ret_enuErrorStatus = MTIMER_OK;

    if (ptr_uint16CounterVal == NULL)
    {
        ret_enuErrorStatus = MTIMER_NULL_PTR;
    }
	else
    {
		MGIE_CallBackFunctions[copy_enuISRNum] = ptr_ISR;
    }

    return ret_enuErrorStatus;
}


void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER0_OVERFLOW] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER0_OVERFLOW]();
    }
    else {}
}

void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER0_COMPARE_MATCH] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER0_COMPARE_MATCH]();
    }
    else {}
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER1_OVERFLOW] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER1_OVERFLOW]();
    }
    else {}
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER1_COMPARE_MATCH_B] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER1_COMPARE_MATCH_B]();
    }
    else {}
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER1_COMPARE_MATCH_A] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER1_COMPARE_MATCH_A]();
    }
    else {}
}

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER1_CAPTURE_EVENT] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER1_CAPTURE_EVENT]();
    }
    else {}
}

void __vector_5 (void) __attribute__((signal)) ;
void __vector_5 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER2_OVERFLOW] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER2_OVERFLOW]();
    }
    else {}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if (MGIE_CallBackFunctions[MGIE_TIMER2_COMPARE_MATCH] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_TIMER2_COMPARE_MATCH]();
    }
    else {}
}
