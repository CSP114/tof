#ifndef HLD_UART_H_
#define HLD_UART_H_

#include <stdint.h>

void uart2_init(uint32_t baudrate);

void uart2_puts(const char* string);

void uart2_putc(char c);

#endif
