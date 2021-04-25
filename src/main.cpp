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
const int howmany = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  helloWorldFkt(Serial, howmany);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}