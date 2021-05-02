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

// Helper functions declarations
void checkIaqSensorStatus(void);
void errLeds(void);

// Create an object of the class Bsec
Bsec iaqSensor;

String output;

// Entry point for the example
void setup(void)
{
  Serial.begin(115200);
  Wire.begin();

  iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
  Serial.println(output);
  checkIaqSensorStatus();

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

  iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_CONTINUOUS);
  checkIaqSensorStatus();

  // Print the header
  output = "Timestamp [ms], raw temperature [°C], pressure [hPa], raw relative humidity [%], gas [Ohm], IAQ, IAQ accuracy, temperature [°C], relative humidity [%], Static IAQ, CO2 equivalent, breath VOC equivalent";
  Serial.println(output);
}

// Function that is looped forever
void loop(void)
{
  unsigned long time_trigger = millis();
  if (iaqSensor.run()) { // If new data is available
    output = String(time_trigger);
    output += ", " + String(iaqSensor.rawTemperature);
    output += ", " + String(iaqSensor.pressure);
    output += ", " + String(iaqSensor.rawHumidity);
    output += ", " + String(iaqSensor.gasResistance);
    /**
     * @brief Der IAQ–Wert wird durch einen intelligenten Algorithmus berechnet 
     * und beinhaltet unterschiedlichste Gaskonzentrationen die zur Luftqualität 
     * im Innenbereich beitragen. Der IAQ-Wert lässt keine direkten Rückschlüsse 
     * auf einzelne auftretende Konzentrationen zu, stellt diese aber im 
     * Zusammenhang als Gesamtqualität bereit.
     * 
     */
    output += ", " + String(iaqSensor.iaq);
    /**
     * @brief 
     * UNRELIABLE 0 Sensor data is unreliable, the sensor must be calibrated
     * LOW_ACCURACY 1 Low accuracy, sensor should be calibrated
     * MEDIUM_ACCURACY 2 Medium accuracy, sensor calibration may improve performance
     * HIGH_ACCURACY 3 High accuracy
     * Will it be calibrated automaticly?
     */
    output += ", " + String(iaqSensor.iaqAccuracy);
    output += ", " + String(iaqSensor.temperature);
    output += ", " + String(iaqSensor.humidity);
    output += ", " + String(iaqSensor.staticIaq);
    /**
     * @brief Kohlenstoffdioxid (CO2) ist das Treibhausgas, das massemäßig am 
     * häufigsten vorkommt. Es hat ein CO2-Äquivalent von eins und bildet die 
     * Basis der Bewertung. Wie stark sich andere Gase auf unser Klima auswirken,
     * zeigt die folgende Tabelle.
     * Gas 	                          Vorkommen/ Verursacher(Beispiele) CO2e(20 Jahre)  CO2e(100 Jahre)
     * ------------------------------------------------------------------------------------------------
     * Kohlenstoffdioxid  (CO2) 	    Verbrennung	                      1               1
     * Methan  (CH4)	                Reisanbau, Kläranlagen 	          84 	            28
     * Lachgas (N2O)                  Dünger, Biomasseverbrennung	      264 	          265
     * FCKW 	                        Sprühdosen, Kältemittel	          10900 	        13900
     * Schwefelhexafluorid(SF6) 	    Gas zur Magnesiumherstellung	    17500 	        23500
     * 
     */
    output += ", " + String(iaqSensor.co2Equivalent);
    output += ", " + String(iaqSensor.breathVocEquivalent);
    Serial.println(output);
  } else {
    checkIaqSensorStatus();
  }
}

// Helper function definitions
void checkIaqSensorStatus(void)
{
  if (iaqSensor.status != BSEC_OK) {
    if (iaqSensor.status < BSEC_OK) {
      output = "BSEC error code : " + String(iaqSensor.status);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      output = "BSEC warning code : " + String(iaqSensor.status);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme680Status != BME680_OK) {
    if (iaqSensor.bme680Status < BME680_OK) {
      output = "BME680 error code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      output = "BME680 warning code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
    }
  }
}

void errLeds(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}