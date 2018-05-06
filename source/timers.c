#include "timers.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_tim.h"

void timer2_init(uint32_t period,int use_us){
    int prescaler = 0;
    SystemCoreClockUpdate();

    prescaler = use_us ? ((SystemCoreClock/1000000)-1) : ((SystemCoreClock/1000)-1); //CountFreq=(CoreClock/Prescaler+1)

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    LL_TIM_InitTypeDef myTimer;

    myTimer.CounterMode = LL_TIM_COUNTERMODE_DOWN;
    myTimer.Prescaler = prescaler;
    myTimer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    myTimer.Autoreload = period;
    LL_TIM_Init(TIM2, &myTimer);

    LL_TIM_DisableMasterSlaveMode(TIM2);
}

static timer_callback_t timer2_callback;

void timer2_enableIRQ(timer_callback_t callback){
    timer2_callback  = callback;
    LL_TIM_EnableIT_UPDATE(TIM2);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void timer2_start(void){
    LL_TIM_EnableCounter(TIM2);
}

void timer2_stop(void){
    LL_TIM_DisableCounter(TIM2);
}

void TIM2_IRQHandler(void){
    LL_TIM_ClearFlag_UPDATE(TIM2);
    timer2_callback();
}


void timer15_init(uint16_t period,int use_us){
    int prescaler = 0;
    SystemCoreClockUpdate();

    prescaler = use_us ? ((SystemCoreClock/1000000)-1) : ((SystemCoreClock/1000)-1); //CountFreq=(CoreClock/Prescaler+1)

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);

    LL_TIM_InitTypeDef myTimer;

    myTimer.CounterMode = LL_TIM_COUNTERDIRECTION_UP;// TIM15 can only be up timer
    myTimer.Prescaler = prescaler;
    myTimer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    myTimer.Autoreload = period;
    LL_TIM_Init(TIM15, &myTimer);

    LL_TIM_DisableMasterSlaveMode(TIM15);
}

static timer_callback_t timer15_callback;

void timer15_enableIRQ(timer_callback_t callback){
    timer15_callback  = callback;
    LL_TIM_EnableIT_UPDATE(TIM15);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
}

void timer15_start(void){
    LL_TIM_EnableCounter(TIM15);;
}

void timer15_stop(void){
    LL_TIM_DisableCounter(TIM15);
}

void TIM1_BRK_TIM15_IRQHandler(void){
    LL_TIM_ClearFlag_UPDATE(TIM15);
    timer15_callback();
}

void timer16_init(uint16_t period,int use_us){
    int prescaler = 0;
    SystemCoreClockUpdate();

    prescaler = use_us ? ((SystemCoreClock/1000000)-1) : ((SystemCoreClock/1000)-1); //CountFreq=(CoreClock/Prescaler+1)

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);

    LL_TIM_InitTypeDef myTimer;

    myTimer.CounterMode = LL_TIM_COUNTERDIRECTION_UP;// TIM16 can only be up timer
    myTimer.Prescaler = prescaler;
    myTimer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    myTimer.Autoreload = period;
    LL_TIM_Init(TIM16, &myTimer);

    LL_TIM_DisableMasterSlaveMode(TIM16);
}

static timer_callback_t timer16_callback;

void timer16_enableIRQ(timer_callback_t callback){
    timer16_callback  = callback;
    LL_TIM_EnableIT_UPDATE(TIM16);
    NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
}

void timer16_start(void){
    LL_TIM_EnableCounter(TIM16);;
}

void timer16_stop(void){
    LL_TIM_DisableCounter(TIM16);
}

void TIM1_UP_TIM16_IRQHandler(void){
    LL_TIM_ClearFlag_UPDATE(TIM16);
    timer16_callback();
}


void timer17_init(uint16_t period,int use_us){
    int prescaler = 0;
    SystemCoreClockUpdate();

    prescaler = use_us ? ((SystemCoreClock/1000000)-1) : ((SystemCoreClock/1000)-1); //CountFreq=(CoreClock/Prescaler+1)

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);

    LL_TIM_InitTypeDef myTimer;

    myTimer.CounterMode = LL_TIM_COUNTERDIRECTION_UP;// TIM17 can only be up timer
    myTimer.Prescaler = prescaler;
    myTimer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    myTimer.Autoreload = period;
    LL_TIM_Init(TIM17, &myTimer);

    LL_TIM_DisableMasterSlaveMode(TIM17);
}

static timer_callback_t timer17_callback;

void timer17_enableIRQ(timer_callback_t callback){
    timer17_callback  = callback;
    LL_TIM_EnableIT_UPDATE(TIM17);
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
}

void timer17_start(void){
    LL_TIM_EnableCounter(TIM17);;
}

void timer17_stop(void){
    LL_TIM_DisableCounter(TIM17);
}

void TIM1_TRG_COM_TIM17_IRQHandler(void){
    LL_TIM_ClearFlag_UPDATE(TIM17);
    timer17_callback();
}

// TIM6 Config

void timer6_init(uint16_t period,int use_us){
    int prescaler = 0;
    SystemCoreClockUpdate();

    prescaler = use_us ? ((SystemCoreClock/1000000)-1) : ((SystemCoreClock/1000)-1); //CountFreq=(CoreClock/Prescaler+1)

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

    LL_TIM_InitTypeDef myTimer;

    myTimer.CounterMode = LL_TIM_COUNTERDIRECTION_UP;// TIM6 can only be up timer
    myTimer.Prescaler = prescaler;
    myTimer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    myTimer.Autoreload = period;
    LL_TIM_Init(TIM6, &myTimer);

    LL_TIM_DisableMasterSlaveMode(TIM6);
}

static timer_callback_t timer6_callback;

void timer6_enableIRQ(timer_callback_t callback){
    timer6_callback  = callback;
    LL_TIM_EnableIT_UPDATE(TIM6);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void timer6_start(void){
    LL_TIM_EnableCounter(TIM6);;
}

void timer6_stop(void){
    LL_TIM_DisableCounter(TIM6);
}

void TIM6_DAC_IRQHandler(void){
    LL_TIM_ClearFlag_UPDATE(TIM6);
    timer6_callback();
}

