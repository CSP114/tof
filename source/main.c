#include "bracer.h"
#include "hld_uart.h"
#include "serial_stdio.h"
#include "cmsis_os2.h"
#include "math.h"

void app_main(void *argument){
  int i = 0;
  float signal;
  float pressure;
  float temperature;
  float humidity;
  while(1){
    signal = sin(i*(3.14f/10.0f));
    pressure = signal * 500.0f + 500.0f;
    temperature = signal * 80.0f;
    humidity = signal * 50.0f + 100.0f;
    serial_printf(uart2_puts, "$P,%4.2f,T,%4.2f,H,%4.2f,*%02x\n",pressure, temperature, humidity, 100);
    osDelay(200);
    i++;
  }
}

int main(){
  //hardware config
  uart2_init(9600);
  //bracer
  bracer_init(app_main);
  while(1){
  }
}
