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
#include <NeoPixelBus.h>

const uint16_t PIXELCOUNT = 12; /**< Use 12 pixels*/
const uint8_t PIXEL_OW = 23;  /**< Pin for the Bus */
const uint32_t PIXEL_DELAY = 100;
#define COLORSATURATION 128
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripObj(PIXELCOUNT, PIXEL_OW);
RgbColor red(COLORSATURATION, 0, 0);
RgbColor green(0, COLORSATURATION, 0);
RgbColor blue(0, 0, COLORSATURATION);
RgbColor white(COLORSATURATION);
RgbColor black(0);

HslColor hsl_red(red);
HslColor hsl_green(green);
HslColor hsl_blue(blue);
HslColor hsl_white(white);
HslColor hsl_black(black);

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
  stripObj.Begin();
  stripObj.Show();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint8_t i=0;i<PIXELCOUNT;i++){
    stripObj.SetPixelColor(i, hsl_red);
    delay(40);
    stripObj.Show();
  }
  
  delay(PIXEL_DELAY);
  
  for (uint8_t i=0;i<PIXELCOUNT;i++){
    stripObj.SetPixelColor(i, hsl_white);
    delay(40);
    stripObj.Show();
  }
    
  delay(PIXEL_DELAY);
  
  for (uint8_t i=0;i<PIXELCOUNT;i++){
    stripObj.SetPixelColor(i, hsl_green);
    delay(40);
    stripObj.Show();
  }
      
  delay(PIXEL_DELAY);
  
  for (uint8_t i=0;i<PIXELCOUNT;i++){
    stripObj.SetPixelColor(i, hsl_blue);
    delay(40);
    stripObj.Show();
  }

  delay(PIXEL_DELAY);
  
}