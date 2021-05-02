#include<Arduino.h>
#include<Wire.h>
#include<SPI.h>
#include<bsec.h>
#include"Utils_BME680.h"

void initIaqSensor(Bsec& t_iaqSensor, uint8_t t_addr, TwoWire &t_i2c_bus){
    t_iaqSensor.begin(t_addr, t_i2c_bus);
    checkIaqSensorStatus(t_iaqSensor);

    bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };

    t_iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_CONTINUOUS);
    checkIaqSensorStatus(t_iaqSensor);
}

void checkIaqSensorStatus(Bsec& t_iaqSensor){
  if (t_iaqSensor.status != BSEC_OK) {
    if (t_iaqSensor.status < BSEC_OK) {
      //output = "BSEC error code : " + String(t_iaqSensor.status);
      DEBUG_PRINT("BSEC Error: ");
      DEBUG_PRINTLN(t_iaqSensor.status);
    }
    else {
      //output = "BSEC warning code : " + String(t_iaqSensor.status);
      //Serial.println(output);
      DEBUG_PRINT("BSEC warning: ");
      DEBUG_PRINTLN(t_iaqSensor.status);
    }
  }

  if (t_iaqSensor.bme680Status != BME680_OK) {
    if (t_iaqSensor.bme680Status < BME680_OK) {
      //output = "BME680 error code : " + String(t_iaqSensor.bme680Status);
      //Serial.println(output);
      DEBUG_PRINT("BME680 Error: ");
      DEBUG_PRINTLN(t_iaqSensor.bme680status);
      } 
      else {
      //output = "BME680 warning code : " + String(t_iaqSensor.bme680Status);
      //Serial.println(output);
      DEBUG_PRINT("BME680 warning: ");
      DEBUG_PRINTLN(t_iaqSensor.bme680status);
    }
  }
}