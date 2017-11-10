#include "led.h"
#include "bracer.h"

void app_main(void *argument){
  while(1){
    led_toggle();
    osDelay(500);
  }
}

int main(){
  //hardware config
  led_init();
  //bracer
  bracer_init(app_main);
  while(1){
  }
}
