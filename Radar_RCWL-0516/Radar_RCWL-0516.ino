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
#include "src/SensorData.h"
#include "src/RadarSensor_RCWL0516.h"

#ifdef ARDUINO_SAMD_FEATHER_M0 // pin defines for Adafruit Feather M0
const int LED_RED = 0;
const int LED_GREEN = 1;
const int LED_BLUE = 5;
const int SENSOR_INT_PIN = 13; // sensor interrupt pin
const int SENSOR_EN_PIN = 12;
#else // pin defines for TheThings Uno (Arduino Leonardo)
const int LED_RED = 0;
const int LED_GREEN = 1;
const int LED_BLUE = 2;
const int SENSOR_INT_PIN = 3; // sensor interrupt pin
const int SENSOR_EN_PIN = 4;
#endif

SensorData data;
int numBins = 3;
unsigned int binBorders[] = {6000, 10000}; // size is numBins-1

RadarSensor_RCWL0516 radarSensor;

void setup() {
  Serial.begin(9600);
  
  configureLedPins();
  
  data.setBinBorders(binBorders, numBins-1); 
  radarSensor.setInterruptPin(SENSOR_INT_PIN);
  radarSensor.setEnablePin(SENSOR_EN_PIN);
  
  radarSensor.configure();
  
  delay(10000);
  
  digitalWrite(LED_GREEN, HIGH);
  
  // clear data and start data acquisition
  data.clear();
  attachInterrupt(digitalPinToInterrupt(SENSOR_INT_PIN), radarSensorIRQ, CHANGE); // enable interrupt
  radarSensor.enable();

  
}

void loop() {
  Serial.println("Data dump");
  data.printBins();
  data.printData();
  data.clear();
  delay(10000);
}

void configureLedPins() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}


// interrupt stuff

typedef enum {
  SENSOR_STATE_ON,
  SENSOR_STATE_OFF
} sensor_state_t;

void radarSensorIRQ() {
  static sensor_state_t sensorState = SENSOR_STATE_ON;
  static unsigned int movementOnTime = 0;

  if (digitalRead(SENSOR_INT_PIN) == HIGH) {
    // start of movement detected
    sensorState = SENSOR_STATE_ON;
    movementOnTime = millis();  
  }
  else {
    // end of movement detected
    if (sensorState == SENSOR_STATE_ON) { // check for correct toggling sequence
      sensorState = SENSOR_STATE_OFF;
      unsigned int movementDuration = millis() - movementOnTime;
      data.add(movementDuration);
    }
  }
}
