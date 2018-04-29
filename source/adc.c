#include "adc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_adc.h"
#include "delay.h"

//Init PA0-PA1
void adc_config_pins(void){
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_GPIO_InitTypeDef gpio;
    LL_GPIO_StructInit(&gpio);
    gpio.Mode = LL_GPIO_MODE_ANALOG;
    gpio.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    LL_GPIO_Init(GPIOC, &gpio);
}

void adc_init(void){
    adc_config_pins();
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC1);
    LL_RCC_SetADCClockSource(LL_RCC_ADC1_CLKSRC_HCLK);

    
    //Common configuration
    LL_ADC_CommonInitTypeDef common;
    LL_ADC_CommonStructInit(&common);
    common.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV1;
    LL_ADC_CommonInit(ADC1_COMMON, &common);
    
        
    LL_ADC_EnableInternalRegulator(ADC1);
    delay_ms(1);  
    
    LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
    while(LL_ADC_IsCalibrationOnGoing(ADC1));
    
    LL_ADC_InitTypeDef myADC;
    LL_ADC_StructInit(&myADC);
    myADC.Resolution = LL_ADC_RESOLUTION_12B;
    myADC.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    LL_ADC_Init(ADC1, &myADC);  
    
    LL_ADC_INJ_SetSequencerDiscont(ADC1, LL_ADC_INJ_SEQ_DISCONT_DISABLE);
     
           //Injected sequencer configuration
    LL_ADC_ClearFlag_JQOVF(ADC1);
    ADC1->JSQR = (0x1 << 0) | (0x6 << 8) |  (0x7 << 14);
    LL_ADC_INJ_SetSequencerRanks(ADC1, LL_ADC_INJ_RANK_1, LL_ADC_CHANNEL_3);
    LL_ADC_ClearFlag_JQOVF(ADC1);
  
    LL_ADC_Enable(ADC1);
    while(!LL_ADC_IsActiveFlag_ADRDY(ADC1)){};
}

void adc_capture(void){
    LL_ADC_ClearFlag_JEOS(ADC1);
    LL_ADC_INJ_StartConversion(ADC1);
    while(!LL_ADC_IsActiveFlag_JEOS(ADC1)){};
    LL_ADC_ClearFlag_JEOS(ADC1);
}

uint16_t adc_read_rank(int rank){
    int ranks[4] = { LL_ADC_INJ_RANK_1, LL_ADC_INJ_RANK_2, LL_ADC_INJ_RANK_3, LL_ADC_INJ_RANK_4 };
    return LL_ADC_INJ_ReadConversionData12(ADC1,ranks[rank]);
}
