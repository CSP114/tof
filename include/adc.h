#ifndef ADC_INCLUDED_
#define ADC_INCLUDED_

#include <stdint.h>

void adc_init(void);
void adc_capture(void);
uint16_t adc_read_rank(int rank);

#endif
