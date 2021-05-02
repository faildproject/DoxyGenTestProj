/**
 * @file main.cpp
 * @author Philipp Heise (philipp.heise.2012@gmail.com)
 * @brief Simple test the Doxygen-Power
 *
 * Static IAQ:
 *  The main difference between IAQ and static IAQ (sIAQ) relies in 
 *  the scaling factor calculated based on the recent sensor history. 
 *  The sIAQ output has been optimized for stationary applications 
 *  (e.g. fixed indoor devices) whereas the IAQ output is ideal for 
 *  mobile application (e.g. carry-on devices).
 * bVOCeq estimate:
 *  The breath VOC equivalent output (bVOCeq) estimates the total VOC 
 *  concentration [ppm] in the environment. It is calculated based on 
 *  the sIAQ output and derived from lab tests.
 * CO2eq estimate:
 *  Estimates a CO2-equivalent (CO2eq) concentration [ppm] in the environment. 
 *  It is also calculated based on the sIAQ output and derived from VOC 
 *  measurements and correlation from field studies.

Since bVOCeq and CO2eq are based on the sIAQ output, they are expected to perform optimally in stationnary applications where the main source of VOCs in the environment comes from human activity (e.g. in a bedroom)
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <Utils.h>
#include <SPI.h>
#include <bsec.h>
//#define BME680_DEBUG
#include <Utils_BME680.h>

// Create an object of the class Bsec
Bsec iaqSensor;

String output;

// Entry point for the example
void setup(void)
{
  Serial.begin(115200);
  Wire.begin();
  initIaqSensor(iaqSensor,BME680_I2C_ADDR_SECONDARY,Wire);
}

// Function that is looped forever
void loop(void)
{
  unsigned long time_trigger = millis();
  printData(iaqSensor, Serial);
  delay(2000);
}

