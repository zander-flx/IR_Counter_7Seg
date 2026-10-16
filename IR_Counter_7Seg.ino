/*======================================================
    INFRARED SENSOR COUNTER WITH 7 SEGMENT DISPLAY
========================================================
Description:
  This program takes an Infrared Sensor analog signal
  and converts it to digital input. It then detects
  every 500 miliseconds whether there is an obstacle
  ahead and counts it until it reached 99 counts and
  stops. The counts will be displayed on a 7-segment
  Common-Anode display.

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
int adc_val = 0;
uint8_t count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_IN, INPUT);
  for (int i = 0; i < NUM0; i++) {
    pinMode(LED_1[i], OUTPUT);
  }

  for (int i = 0; i < NUM1; i++) {
    pinMode(LED_2[i], OUTPUT);
  }
  analogReadResolution(8);
}
#include "Decoder.h"

void loop() {
  // put your main code here, to run repeatedly:
  adc_val = analogRead(IR_IN);
  decoder(count);

  if(adc_val != 255 && count <= 99){
    count++;
    
    // Serial.printf("count: %d\n", count);
    delay(500);
  } else if(count == 100){
    count = 0;
  }
}
