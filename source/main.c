#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"
#include "adc.h"
#include "stm32f3xx.h"                  // Device header


void buttonCallback(int state);

int main(){
    uart2_init(9600);
    serial_printf(uart2_puts, "Usart init complete\n");
    adc_init();
    serial_printf(uart2_puts, "ADC init complete\n");
    while(1){
        delay_ms(100);
        adc_capture();
        serial_printf(uart2_puts, "channel[0]=%04d\t", ADC1->JDR1);
        serial_printf(uart2_puts, "channel[1]=%04d\n", ADC1->JDR2);
        
    }
}

void buttonCallback(int state){
    led_write(!state);
}
