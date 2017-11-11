#include "led.h"
#include "button.h"
#include "bracer.h"
#include "hld_uart.h"

static void onChangeCallback(int buttonState){
  led_write(buttonState);
  uart2_puts("Hello world\n");
}

void app_main(void *argument){
  button_onChange(onChangeCallback);
}

int main(){
  //hardware config
  led_init();
  button_init();
  uart2_init(9600);
  //bracer
  bracer_init(app_main);
  while(1){
  }
}
