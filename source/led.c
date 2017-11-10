#include "led.h"

#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_tim.h"

void led_init(void){
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_InitTypeDef gpio;
  LL_GPIO_StructInit(&gpio);
  gpio.Mode = LL_GPIO_MODE_OUTPUT;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio.Pin = LL_GPIO_PIN_13;
  LL_GPIO_Init(GPIOB, &gpio);
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}

void led_toggle(void){
  LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_13);
}

void led_write(uint32_t state){
  if(state){
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
  }else{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
  }
}
