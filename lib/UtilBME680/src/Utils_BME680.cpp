#include<Arduino.h>
#include<Wire.h>
#include<SPI.h>
#include<bsec.h>
#include"Utils_BME680.h"

void initIaqSensor(Bsec& t_iaqSensor, uint8_t t_addr, TwoWire &t_i2c_bus){
    DEBUG_PRINTLN("INIT-Started");
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

    t_iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus(t_iaqSensor);
}

void checkIaqSensorStatus(Bsec& t_iaqSensor){
  DEBUG_PRINTLN("Check IAQ Status");
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
      DEBUG_PRINTLN(t_iaqSensor.bme680Status);
      } 
      else {
      //output = "BME680 warning code : " + String(t_iaqSensor.bme680Status);
      //Serial.println(output);
      DEBUG_PRINT("BME680 warning: ");
      DEBUG_PRINTLN(t_iaqSensor.bme680Status);
    }
  }
}

void printData(Bsec& t_iaqSensor, Stream &t_stream){
    String output = "";
    if (t_iaqSensor.run()) { // If new data is available
    output = "T: " + String(t_iaqSensor.rawTemperature);
    output += " °C , P: " + String(t_iaqSensor.pressure);
    output += " Pa , rF: " + String(t_iaqSensor.rawHumidity);
    output += " % , gR: " + String(t_iaqSensor.gasResistance);
    /**
     * @brief Der IAQ–Wert wird durch einen intelligenten Algorithmus berechnet 
     * und beinhaltet unterschiedlichste Gaskonzentrationen die zur Luftqualität 
     * im Innenbereich beitragen. Der IAQ-Wert lässt keine direkten Rückschlüsse 
     * auf einzelne auftretende Konzentrationen zu, stellt diese aber im 
     * Zusammenhang als Gesamtqualität bereit.
     * 
     */
    output += " mOhm , IAQ: " + String(t_iaqSensor.iaq);
    /**
     * @brief 
     * UNRELIABLE 0 Sensor data is unreliable, the sensor must be calibrated
     * LOW_ACCURACY 1 Low accuracy, sensor should be calibrated
     * MEDIUM_ACCURACY 2 Medium accuracy, sensor calibration may improve performance
     * HIGH_ACCURACY 3 High accuracy
     * Will it be calibrated automaticly?
     */
    output += ", IAQ-ACC: " + String(t_iaqSensor.iaqAccuracy);
    output += ", T: " + String(t_iaqSensor.temperature);
    output += " °C , rF: " + String(t_iaqSensor.humidity);
    output += " % , stIAQ: " + String(t_iaqSensor.staticIaq);
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
    output += ", CO2e: " + String(t_iaqSensor.co2Equivalent);
    output += ", bVocE: " + String(t_iaqSensor.breathVocEquivalent);
    t_stream.println(output);
  } else {
    checkIaqSensorStatus(t_iaqSensor);
  }
}