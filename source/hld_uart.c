#include "hld_uart.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_usart.h"

#define UART2_PINS  LL_GPIO_PIN_2 |  LL_GPIO_PIN_3
#define UART2_PORT  GPIOA


void uart2_configure_pins(void){
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_GPIO_InitTypeDef gpio;
  LL_GPIO_StructInit(&gpio);
  gpio.Mode = LL_GPIO_MODE_ALTERNATE;
  gpio.Pin = UART2_PINS;
  gpio.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(UART2_PORT, &gpio);
}

void uart2_init(uint32_t baudrate){
  uart2_configure_pins();
  
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_USART_InitTypeDef uart;
  LL_USART_StructInit(&uart);
  
  uart.BaudRate = 9600;
  uart.StopBits = LL_USART_STOPBITS_1;
  uart.DataWidth = LL_USART_DATAWIDTH_8B;
  uart.OverSampling = LL_USART_OVERSAMPLING_8;
  uart.Parity = LL_USART_PARITY_NONE;
  uart.TransferDirection = LL_USART_DIRECTION_TX_RX;
  
  LL_USART_Init(USART2, &uart);
  LL_USART_Enable(USART2);
}

void uart2_puts(const char* string){
  char c; 
  while((c = *string++)){
    uart2_putc(c);
  }
}

void uart2_putc(char c){
  LL_USART_TransmitData8(USART2,c);
  while(!LL_USART_IsActiveFlag_TXE(USART2));
}
