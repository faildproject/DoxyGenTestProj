/**
 * @file main.cpp
 * @author Philipp Heise (philipp.heise.2012@gmail.com)
 * @brief Simple test the Doxygen-Power
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <Utils.h>
#include <Zanshin_BME680.h>

const int HOWMANY = 1;
int g_cnt = 0;

const int LED_POUT = LED_BUILTIN; /**< Blue Onboard-LED */
const int BTN_PIN = 34; /**< Where the Button is connected*/

const int SDA_I2C = 22; /**< Dataline for I2C */
const int SCL_I2C = 23; /**< Clockline for I2C */

const int POTI_ADC = 27; /**< Readout the Poti-Voltage */
const int DRIVER_DAC = 28; /**< Control a Fan via MOSFET */

BME680_Class BME680;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  helloWorldFkt(Serial, HOWMANY);
  if(!BME680.begin(I2C_STANDARD_MODE)){
    Serial.println("Faild to connect to BME680");
  }
  BME680.setOversampling(TemperatureSensor, Oversample16);  // Use enumerated type values
  BME680.setOversampling(HumiditySensor, Oversample16);     // Use enumerated type values
  BME680.setOversampling(PressureSensor, Oversample16);     // Use enumerated type values
  BME680.setIIRFilter(IIR4);  // Use enumerated type values
  BME680.setGas(320, 150);  // 320�c for 150 milliseconds
}

void loop() {
  // put your main code here, to run repeatedly:
  static int32_t  temp, humidity, pressure, gas;  // BME readings
  float temp_f, humidity_f, pressure_f, gas_f;
  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings
  
  temp_f = (float)temp/100.;
  humidity_f = (float)humidity/1000.;
  pressure_f = (float)pressure/100.;
  gas_f = (float)gas/100.;
  Serial.printf("T: %.2f °C\trF: %.2f %\t P: %.2f Pa\t Gas: %.2f mOhm\r\n",temp_f,humidity_f,pressure_f,gas_f);
  delay(2000);
}