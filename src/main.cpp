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
const int howmany = 10;

void helloWorld(int t_howmany);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  helloWorld(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

/**
 * @brief Prints "Hello Chat" a few Times
 * 
 * @param t_howmany "How often print "Hello Chat"
 */
void helloWorld(int t_howmany){
  for (int i=0; i<t_howmany;i++){
    Serial.println("Hello Chat");
  }
}