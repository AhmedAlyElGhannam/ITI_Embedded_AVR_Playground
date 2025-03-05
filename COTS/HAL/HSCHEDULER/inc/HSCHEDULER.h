#ifndef HSCHEDULER_H
#define HSCHEDULER_H


typedef enum 
{
    RUNNABLE_LED,
    RUNNABLE_LCD,
    RUNNABLE_PWM,
    RUNNABLE_SWITCH,
    NUM_OF_RUNNABLES
} HSCHEDULER_enuRunnableName_t;

typedef void (*HSCHEDULER_CallBackFunction_t) (void)

typedef struct 
{
    HSCHEDULER_CallBackFunction_t cbf;
    uint16_t period;
    uint16_t firstDelay;
} HSCHEDULER_structRunnable_t;


#endif