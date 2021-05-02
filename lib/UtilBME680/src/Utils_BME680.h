#ifndef UTILS_BME_680_H
#define UTILS_BME680_H
//#define BME680_DEBUG
#ifdef BME680_DEBUG
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

#include<Arduino.h>
#include<Wire.h>
#include<SPI.h>
#include<bsec.h>

void initIaqSensor(Bsec& t_iaqSensor, uint8_t t_addr, TwoWire &t_i2c_bus);
void checkIaqSensorStatus(Bsec& t_iaqSensor);
void printData(Bsec& t_iaqSensor, Stream &t_stream);

#endif