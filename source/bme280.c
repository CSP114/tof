#include "bme280.h"

#define BME280_ADDRESS      0x76          // define the default I2C address

// Name of Registers used in the BME280

#define    BME280_DIG_T1_REG   0x88
#define    BME280_DIG_T2_REG   0x8A
#define    BME280_DIG_T3_REG   0x8C
#define    BME280_DIG_P1_REG   0x8E
#define    BME280_DIG_P2_REG   0x90
#define    BME280_DIG_P3_REG   0x92
#define    BME280_DIG_P4_REG   0x94
#define    BME280_DIG_P5_REG   0x96
#define    BME280_DIG_P6_REG   0x98
#define    BME280_DIG_P7_REG   0x9A
#define    BME280_DIG_P8_REG   0x9C
#define    BME280_DIG_P9_REG   0x9E

#define    BME280_DIG_H1_REG   0xA1
#define    BME280_DIG_H2_REG   0xE1
#define    BME280_DIG_H3_REG   0xE3
#define    BME280_DIG_H4_REG   0xE4
#define    BME280_DIG_H5_REG   0xE5
#define    BME280_DIG_H6_REG   0xE7

#define    BME280_REGISTER_CHIPID       0xD0
#define    BME280_REGISTER_VERSION      0xD1
#define    BME280_REGISTER_SOFTRESET    0xE0
#define    BME280_REGISTER_CAL26        0xE1
#define    BME280_REGISTER_CONTROLHUMID     0xF2
#define    BME280_REGISTER_CONTROL          0xF4
#define    BME280_REGISTER_CONFIG           0xF5
#define    BME280_REGISTER_PRESSUREDATA     0xF7
#define    BME280_REGISTER_TEMPDATA         0xFA
#define    BME280_REGISTER_HUMIDDATA        0xFD


typedef struct { 
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;
} BME280_Calibration_Data;


static float tempcal;// stores the temp offset calibration
static float temperature;// stores temperature value
static float humidity;// stores humidity value
static float pressure;// stores pressure value
static hld_i2c_t* _i2c;
uint8_t _i2caddr;
int32_t _sensorID;
int32_t t_fine;

uint8_t BME280_begin(void);
void      BME280_write8(uint8_t reg, uint8_t value);
uint8_t   BME280_read8(uint8_t reg);
uint16_t  BME280_read16(uint8_t reg);
uint32_t  BME280_read24(uint8_t reg);
int16_t   BME280_readS16(uint8_t reg);
uint16_t  BME280_read16_LE(uint8_t reg); // little endian
int16_t   BME280_readS16_LE(uint8_t reg); // little endian
uint32_t BME280_read24(uint8_t reg);

void BME280_readSensorCoefficients(void);
void BME280_readTemperature(void);
void BME280_readPressure(void);
void BME280_readHumidity(void);
void BME280_readSensorCoefficients(void);
void BME280_setTempCal(float);// we can set a calibration ofsset for the temperature. 

static BME280_Calibration_Data cal_data;

void BME280_init(hld_i2c_t* i2c){
    _i2c = i2c;
    _i2caddr = BME280_ADDRESS;
    tempcal = 0.0;
	tempcal = 0.0;
    temperature = 0.0;
    humidity = 0.0;
    BME280_begin();
}

uint8_t BME280_begin(void) {
    if (BME280_read8(BME280_REGISTER_CHIPID) != 0x60){   
        return 0;
    }
    BME280_readSensorCoefficients();
    
    // Set Humidity oversampling to 1
    BME280_write8(BME280_REGISTER_CONTROLHUMID, 0x01); // Set before CONTROL (DS 5.4.3)
    
    BME280_write8(BME280_REGISTER_CONTROL, 0x3F);
    
    return 1; 
}

void BME280_readTemperature(void)
{
    
    int32_t var1, var2;
    
    int32_t adc_T = BME280_read24(BME280_REGISTER_TEMPDATA);
        
    adc_T >>= 4;
    
    var1  = ((((adc_T>>3) - ((int32_t)cal_data.dig_T1 <<1))) *
             
             ((int32_t)cal_data.dig_T2)) >> 11;
    
    var2  = (((((adc_T>>4) - ((int32_t)cal_data.dig_T1)) *
               
               ((adc_T>>4) - ((int32_t)cal_data.dig_T1))) >> 12) *
             
             ((int32_t)cal_data.dig_T3)) >> 14;
    
    t_fine = var1 + var2;
    
    
    temperature  = (t_fine * 5 + 128) >> 8;
    
    temperature = temperature / 100;
    
}


void BME280_readPressure(void) {
    
    int64_t var1, var2, p;
    
    int32_t adc_P = BME280_read24(BME280_REGISTER_PRESSUREDATA);    
    adc_P >>= 4;
    
    var1 = ((int64_t)t_fine) - 128000;
    
    var2 = var1 * var1 * (int64_t)cal_data.dig_P6;
    
    var2 = var2 + ((var1*(int64_t)cal_data.dig_P5)<<17);
    
    var2 = var2 + (((int64_t)cal_data.dig_P4)<<35);
    
    var1 = ((var1 * var1 * (int64_t)cal_data.dig_P3)>>8) +
    
    ((var1 * (int64_t)cal_data.dig_P2)<<12);
    
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)cal_data.dig_P1)>>33;
    
    
    if (var1 == 0) {
        
        // return 0;  // avoid exception caused by division by zero
        pressure = 0.0;
    }
    
    p = 1048576 - adc_P;
    
    p = (((p<<31) - var2)*3125) / var1;
    
    var1 = (((int64_t)cal_data.dig_P9) * (p>>13) * (p>>13)) >> 25;
    
    var2 = (((int64_t)cal_data.dig_P8) * p) >> 19;
    
    
    p = ((p + var1 + var2) >> 8) + (((int64_t)cal_data.dig_P7)<<4);
    
    // return (float)p/256;
    pressure = (float)p/256;
}


void BME280_readHumidity(void) {
    
    int32_t adc_H = BME280_read16(BME280_REGISTER_HUMIDDATA);
    
    int32_t v_x1_u32r;
    
    v_x1_u32r = (t_fine - ((int32_t)76800));
    
    v_x1_u32r = (((((adc_H << 14) - (((int32_t)cal_data.dig_H4) << 20) -
                    
                    (((int32_t)cal_data.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
                 
                 (((((((v_x1_u32r * ((int32_t)cal_data.dig_H6)) >> 10) *
                      
                      (((v_x1_u32r * ((int32_t)cal_data.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
                    
                    ((int32_t)2097152)) * ((int32_t)cal_data.dig_H2) + 8192) >> 14));
    
    
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                               
                               ((int32_t)cal_data.dig_H1)) >> 4));
    
    
    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    
    float h = (v_x1_u32r>>12);
    
    // return  h / 1024.0;
    humidity = h / 1024.0;
}

/**************************************************************************

Read the values that are programmed into the sensor during amanufacture

**************************************************************************/

void BME280_readSensorCoefficients(void)
{
    
    cal_data.dig_T1 = BME280_read16_LE(BME280_DIG_T1_REG);
    
    cal_data.dig_T2 = BME280_readS16_LE(BME280_DIG_T2_REG);
    
    cal_data.dig_T3 = BME280_readS16_LE(BME280_DIG_T3_REG);
    
    cal_data.dig_P1 = BME280_read16_LE(BME280_DIG_P1_REG);
    
    cal_data.dig_P2 = BME280_readS16_LE(BME280_DIG_P2_REG);
    
    cal_data.dig_P3 = BME280_readS16_LE(BME280_DIG_P3_REG);
    
    cal_data.dig_P4 = BME280_readS16_LE(BME280_DIG_P4_REG);
    
    cal_data.dig_P5 = BME280_readS16_LE(BME280_DIG_P5_REG);
    
    cal_data.dig_P6 = BME280_readS16_LE(BME280_DIG_P6_REG);
    
    cal_data.dig_P7 = BME280_readS16_LE(BME280_DIG_P7_REG);
    
    cal_data.dig_P8 = BME280_readS16_LE(BME280_DIG_P8_REG);
    
    cal_data.dig_P9 = BME280_readS16_LE(BME280_DIG_P9_REG);
    
    cal_data.dig_H1 = BME280_read8(BME280_DIG_H1_REG);
    
    cal_data.dig_H2 = BME280_readS16_LE(BME280_DIG_H2_REG);
    
    cal_data.dig_H3 = BME280_read8(BME280_DIG_H3_REG);
    
    cal_data.dig_H4 = (BME280_read8(BME280_DIG_H4_REG) << 4) | (BME280_read8(BME280_DIG_H4_REG+1) & 0xF);
    
    cal_data.dig_H5 = (BME280_read8(BME280_DIG_H5_REG+1) << 4) | (BME280_read8(BME280_DIG_H5_REG) >> 4);
    
    cal_data.dig_H6 = (int8_t)BME280_read8(BME280_DIG_H6_REG);
    
}

void BME280_setTempCal(float tcal)
{
	tempcal = tcal;
}

void BME280_readSensor(void)
{
    BME280_readTemperature();
    BME280_readHumidity();
    BME280_readPressure();
}

float BME280_getTemperature_C(void)
{
     return (temperature + tempcal);
}

float BME280_getTemperature_F(void)
{
    return (temperature + tempcal) * 1.8f + 32.0f;
}

float BME280_getHumidity(void) {
    return humidity;
}

// Gets the pressure in millibars
float BME280_getPressure_MB(void) {
    
    return pressure / 100.0F;
}

// Gets the pressure in hectapascals
float BME280_getPressure_HP(void) {
    return pressure;
}


/**************************************************************************

Writes an 8 bit value over I2C

**************************************************************************/


void BME280_write8(uint8_t reg, uint8_t value)
{  
    _i2c->send_packetAtRegister(_i2caddr, reg, &value, 1);
}

/**************************************************************************
 
 Reads a signed 8 bit value over the I2C bus_REG
 
 **************************************************************************/

uint8_t BME280_read8(uint8_t reg)
{
    return _i2c->readData(_i2caddr, reg);   
}


/**************************************************************************

Reads a signed 16 bit value over the I2C bus_REG

**************************************************************************/

int16_t BME280_readS16_LE(uint8_t reg)
{
    return (int16_t)BME280_read16_LE(reg);
}

uint16_t BME280_read16_LE(uint8_t reg) {
    uint8_t data[2];
    _i2c->readPacket(_i2caddr, reg, data, 2);
    return (data[1] << 8)|(data[0]);
}

uint16_t  BME280_read16(uint8_t reg){
    uint8_t data[2];
    _i2c->readPacket(_i2caddr, reg, data, 2);
    return (data[0] << 8)|(data[1]);
}

uint32_t BME280_read24(uint8_t reg)
{
    uint8_t data[3];
    _i2c->readPacket(_i2caddr, reg, data, 3);
    return (data[0] << 16)|(data[1] << 8)|(data[2]);
}
