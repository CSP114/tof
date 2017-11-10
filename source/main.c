#include "led.h"
#include "button.h"
#include "bracer.h"

static void onChangeCallback(int buttonState){
  led_write(buttonState);
}

void app_main(void *argument){
  button_onChange(onChangeCallback);
}

int main(){
  //hardware config
  led_init();
  button_init();
  //bracer
  bracer_init(app_main);
  while(1){
  }
}
