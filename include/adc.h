#ifndef ADC_INCLUDED_
#define ADC_INCLUDED_

#include <stdint.h>

typedef void (*adc_callback_t)(void);

void adc_injected_init(int trigger);
void adc_injected_capture(void);
uint16_t adc_injected_read_rank(int rank);
void adc_injected_enableIRQ(adc_callback_t callback);

#endif
