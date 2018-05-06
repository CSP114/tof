#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "stm32f3xx.h"                  // Device header
#include "timers.h"

void onTimerEvent(void){
}

int data0;
int counter = 0;

void onADCComplete(void){
    led_toggle();
    data0 = adc_regular_read();
    counter++;
}

int main(){
    led_init();
    timer6_init(500, 0);
    timer6_enableIRQ(onTimerEvent);
    timer6_start();
    adc_regular_init(14);
    adc_regular_enableIRQ(onADCComplete);
    adc_regular_capture();
    while(1){
    }
}
