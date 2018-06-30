// Evaluation of Microwave Radar Sensors
//
// Andre Meyer, mail@andmeyer.ch
//
// DESCRIPTION
// Simple sketch to detect moving objects (people) in range of an Microwave Radar Sensor
//
// COMPONENTS
// - Adafruit Feather M0 Wifi (1x)
// - RCWL-0516 Microwave Radar Sensor (1x)
// - Green LED (1x)
// - Red LED (1x)
// - 220R resistor (2x)

#include "Arduino.h"
#include "src/RadarSensor.h"


void setup() {
  Serial.begin(9600);
  
  setupRadarSensor();
  
  delay(10000);
  
  enableRadarSensor();
  
}

void loop() {
  printRadarSensor();
  delay(10000);
}



// interrupt stuff

