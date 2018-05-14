#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "timers.h"
#include "button.h"
#include "mpu6050.h"
#include "hld_i2c.h"

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
    //led_init();
    //button_init();
    //timer6_init(100, 1);
    //timer6_enableIRQ(onTimerEvent);
    //timer6_start();
    //adc_regular_init();
    //adc_regular_enableIRQ(onADCComplete);
    //adc_dma_config(buffer, TOTAL_SAMPLED_DATA, onTransferComplete);
    //button_onChange(onButtonChange);
    uart2_init(9600);
    hld_i2c_t* i2c = i2c1_init();
    mpu6050_init(i2c);
    int16_t datax, datay, dataz;
    while(1){
        datax = mpu6050_read_axis(i2c, 'x');
        datay = mpu6050_read_axis(i2c, 'y');
        dataz = mpu6050_read_axis(i2c, 'z');
        serial_printf(uart2_puts, "x=%f, y=%f, z=%f\n", datax*(16.0/65536), datay*(16.0/65536), dataz*(16.0/65536));
        delay_ms(250);
    }
}
