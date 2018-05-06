#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "stm32f3xx.h"                  // Device header
#include "timers.h"

void onTimerEvent(void){
    led_toggle();
}

int main(){
    led_init();
    timer6_init(500, 0);
    timer6_enableIRQ(onTimerEvent);
    timer6_start();
    while(1){
    }
}
