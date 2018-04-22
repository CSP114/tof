#include "button.h"
#include "led.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "delay.h"

void buttonCallback(int state);

int main(){
    uart2_init(9600);
    led_init();
    button_init();
    button_onChange(buttonCallback);
    while(1){
        delay_ms(1000);
        serial_printf(uart2_puts, "hello, world\n");
    }
}

void buttonCallback(int state){
    led_write(!state);
}
