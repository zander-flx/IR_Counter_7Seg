/*======================================================
    INFRARED SENSOR COUNTER WITH 7 SEGMENT DISPLAY
========================================================
Description:
  This program takes an Infrared Sensor digital signal.
  It then detects every 500 miliseconds whether there
  is an obstacle ahead and counts it until it reached
  100 counts and resets to 0. The counts will be 
  displayed on a 7-segment Common-Cathode display.

Programmer: 
  Felixander B. Doloso

Date: 
  16 October 2026
------------------------------------------------------*/

//GPIO Pins
const byte IR_IN = 36;
const uint8_t LED_1[] = {32, 33, 25, 26, 27, 14, 12};
const uint8_t NUM0 = sizeof(LED_1) / sizeof(LED_1[0]);

const uint8_t LED_2[] = {19, 18, 5, 17, 16, 4, 0};
const uint8_t NUM1 = sizeof(LED_2) / sizeof(LED_2[0]);

//Variables
int lastSensorState = 0; //0 if there's no obstacle, 1 if there's obstacle
int currentSensorState = 0;
uint8_t count = 0;

#include "Decoder.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_IN, INPUT);
  for (int i = 0; i < NUM0; i++) {
    pinMode(LED_1[i], OUTPUT);
  }

  for (int i = 0; i < NUM1; i++) {
    pinMode(LED_2[i], OUTPUT);
  }

  //Initialize Display to 0
  decoder(count);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentSensorState = digitalRead(IR_IN);
  
  //Only trigger when the currentSensorState changes from 1 to 0
  if(currentSensorState == 0 && lastSensorState == 1){
    count = (count + 1) % 100;
    /*
    0 + 1 = 1  -> 1 % 100 = 1
    98 + 1 = 99 -> 99 % 100 = 99
    99 + 1 = 100 -> 100 % 100 = 0
    */ 
    decoder(count);
  }

  lastSensorState = currentSensorState; 
  /*
  Assigns the currentSensorState reading to lastSensorState.
  Acts as ENABLE to the previous if statement
  */

  delay(50);
}
