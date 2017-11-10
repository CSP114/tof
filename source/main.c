#include "led.h"
#include "cmsis_os2.h"

void SystemCoreClockUpdate(void);

void app_main(void *argument){
  while(1){
    led_toggle();
    osDelay(500);
  }
}

int main(){
  //hardware config
  led_init();
  
  //os config
  SystemCoreClockUpdate();
  osKernelInitialize();
  osThreadNew(app_main, NULL, NULL);
  osKernelStart();
  
  while(1){
  }
}
