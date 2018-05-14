#ifndef BME280_H
#define BME280_H

#include <stdint.h>
#include "hld_api.h"

void BME280_init(hld_i2c_t* i2c);
void BME280_setTempCal(float tcal);
void BME280_readSensor(void);                      // read the sensor for data
float BME280_getTemperature_C(void);
float BME280_getTemperature_F(void);
float BME280_getHumidity(void);
float BME280_getPressure_HP(void);                 // pressure in hectapascals
float BME280_getPressure_MB(void);                 // pressure in millibars

#endif
