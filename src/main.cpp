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
const int HOWMANY = 10;
int g_cnt = 0;

const int LED_POUT = LED_BUILTIN; /**< Blue Onboard-LED */
const int BTN_PIN = 34; /**< Where the Button is connected*/

const int SDA_I2C = 22; /**< Dataline for I2C */
const int SCL_I2C = 23; /**< Clockline for I2C */

const int POTI_ADC = 27; /**< Readout the Poti-Voltage */
const int DRIVER_DAC = 28; /**< Control a Fan via MOSFET */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  helloWorldFkt(Serial, HOWMANY);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}