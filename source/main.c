#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "stm32f3xx.h"                  // Device header
#include "timers.h"
#include "button.h"
#include "tof_analyzer.h"

void onTimerEvent(void){
}

void signal_start(void);
void signal_config(void);

#define SAMPLES 1500
#define CHANNELS 4
#define TOTAL_SAMPLED_DATA SAMPLES * CHANNELS
#define TRESHOLD 621

int counter = 0;
uint16_t buffer[TOTAL_SAMPLED_DATA];
int capture_complete = 1;
int generating_signal = 0;

void onADCComplete(void){
    
}

void onTransferComplete(void){
    capture_complete = 1;
    counter++;
}

void onButtonChange(int state){

    if ((state) && (!generating_signal) && (capture_complete)){
        signal_start();
        adc_regular_capture();
        generating_signal = 1;
        capture_complete = 0;
    }       
}

void configure_adc_with_timer_trigger(void){
    timer6_init(10, 1);
    timer6_enableIRQ(onTimerEvent);
    timer6_start();
    adc_regular_init();
    adc_regular_enableIRQ(onADCComplete);
    adc_dma_config(buffer, TOTAL_SAMPLED_DATA, onTransferComplete);
}



void signal_generator_callback(void){
    static int count = 0;
    if(count < 20){
        led_toggle();
        count++;        
    }else if(count < 2000){
        count++;
    }else{
        count = 0;
        generating_signal = 0;
        timer15_stop();
    }
}

void signal_start(void){
    timer15_start();
}

void signal_config(void){
    timer15_init(25, 1);
    timer15_enableIRQ(signal_generator_callback);
}

int main(){
    uart2_init(9600);
    //configure adc capture
    delay_ms(20);
    signal_config();
    led_init();
    button_init();
    button_onChange(onButtonChange);
    configure_adc_with_timer_trigger();
    while(1){
        onButtonChange(1);
        while(!capture_complete);
        trigger_index_t trigger_position;
        find_object_distance(buffer, TOTAL_SAMPLED_DATA, TRESHOLD, &trigger_position);
        char position = estimate_direction(&trigger_position);        
        serial_printf(uart2_puts, "tr: %4d\t", trigger_position.tr);
        serial_printf(uart2_puts, "tl: %4d\t", trigger_position.tl);
        serial_printf(uart2_puts, "br: %4d\t", trigger_position.br);
        serial_printf(uart2_puts, "bl: %4d\t", trigger_position.bl);
        serial_printf(uart2_puts, "pos: %c\n", position);
        delay_ms(50);
    }
}
