#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "stm32f3xx.h"                  // Device header
#include "timers.h"
#include "button.h"

void onTimerEvent(void){
}

#define SAMPLES 100
#define CHANNELS 4
#define TOTAL_SAMPLED_DATA SAMPLES * CHANNELS

int data0;
int counter = 0;
uint16_t buffer[TOTAL_SAMPLED_DATA];
int complete = 0;

void onADCComplete(void){
    led_toggle();
    counter++;
}

void onTransferComplete(void){
    complete = 1;
}

void onButtonChange(int state){
    adc_regular_capture();
    complete = 0;
}

int main(){
    led_init();
    button_init();
    timer6_init(100, 1);
    timer6_enableIRQ(onTimerEvent);
    timer6_start();
    adc_regular_init();
    adc_regular_enableIRQ(onADCComplete);
    adc_dma_config(buffer, TOTAL_SAMPLED_DATA, onTransferComplete);
    button_onChange(onButtonChange);
    while(1){
    }
}
