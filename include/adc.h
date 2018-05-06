#ifndef ADC_INCLUDED_
#define ADC_INCLUDED_

#include <stdint.h>

typedef void (*adc_callback_t)(void);

void adc_injected_init(int trigger);
void adc_injected_capture(void);
uint16_t adc_injected_read_rank(int rank);
void adc_injected_enableIRQ(adc_callback_t callback);

void adc_regular_init(void);
void adc_regular_enableIRQ(adc_callback_t callback);
void adc_regular_capture(void);
uint16_t adc_regular_read(void);

void adc_dma_config(uint16_t* dest_address, uint16_t nData, adc_callback_t callback);

#endif
