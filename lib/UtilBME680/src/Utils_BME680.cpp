#include<Arduino.h>
#include<Wire.h>
#include<SPI.h>
#include<bsec.h>
#include"Utils_BME680.h"

void initIaqSensor(Bsec& t_iaqSensor, uint8_t t_addr, TwoWire &t_i2c_bus){

}
void checkIaqSensorStatus(Bsec& t_iaqSensor);