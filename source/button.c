#include "button.h"
#include "bracer.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_system.h"

#define BUTTON_PIN LL_GPIO_PIN_13
#define BUTTON_PORT GPIOC

void button_init(void){
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_InitTypeDef gpio;
  LL_GPIO_StructInit(&gpio);
  gpio.Mode = LL_GPIO_MODE_INPUT;
  gpio.Pin = BUTTON_PIN;
  gpio.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(BUTTON_PORT, &gpio);
}

void (*onChangeCallback)(int buttonState);

void button_event_handler(void* err, void* context){
  if(onChangeCallback){
    onChangeCallback((uint32_t) context);
  }
}

void button_onChange(void(*callback)(int buttonState)){
  onChangeCallback = callback;

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_EXTI_InitTypeDef exti;
  LL_EXTI_StructInit(&exti);
  exti.Mode = LL_EXTI_MODE_IT;
  exti.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
  exti.LineCommand = ENABLE;
  exti.Line_0_31 = LL_EXTI_LINE_13;
  LL_EXTI_Init(&exti);
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13); 
  
  NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void EXTI15_10_IRQHandler(void){
  uint32_t button_state = LL_GPIO_IsInputPinSet(BUTTON_PORT, BUTTON_PIN);
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
  bracer_postEvent(button_event_handler, NULL, (void*)button_state, 0);
}
