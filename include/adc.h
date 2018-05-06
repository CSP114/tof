#ifndef ADC_INCLUDED_
#define ADC_INCLUDED_

#include <stdint.h>

typedef void (*adc_callback_t)(void);

void adc_init(void);
void adc_capture(void);
uint16_t adc_read_rank(int rank);
void adc_enableIRQ(adc_callback_t callback);

#endif
