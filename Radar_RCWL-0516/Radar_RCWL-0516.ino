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

#include "src/SensorData.h"

#ifdef ARDUINO_SAMD_FEATHER_M0 // pin defines for Adafruit Feather M0
const int LED_RED = 0;
const int LED_GREEN = 1;
const int LED_BLUE = 5;
const int SENSOR_INT_PIN = 13; // sensor interrupt pin
const int SENSOR_EN_PIN = 12;
#endif

// pin defines for other boards can be added here.

typedef enum {
  SENSOR_STATE_ON,
  SENSOR_STATE_OFF
} sensor_state_t;

volatile sensor_state_t sensorState = SENSOR_STATE_OFF;

SensorData data;
int numBins = 3;
unsigned int binBorders[] = {2, 8}; // size is numBins-1


volatile unsigned int movementOnTime, movementDuration;

void setup() {
  configurePins();
  data.setBinBorders(binBorders, numBins-1);
  // set default pin levels
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(SENSOR_EN_PIN, HIGH);
  Serial.begin(9600);
  delay(10000);
  digitalWrite(LED_GREEN, HIGH);
  
  // clear data and start data acquisition
  data.clear();
  attachInterrupt(digitalPinToInterrupt(SENSOR_INT_PIN), sensorIRQ, CHANGE);

}

void loop() {
  Serial.println("Data dump");
  data.printBins();
  data.printData();
  data.clear();
  delay(10000);
}

void configurePins() {
  // configure LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // configure interrupt pin
  pinMode(SENSOR_INT_PIN, INPUT_PULLDOWN);
  // configure sensor enable pin
  pinMode(SENSOR_EN_PIN, OUTPUT);
}

void sensorIRQ() {
  if (digitalRead(SENSOR_INT_PIN) == HIGH) {
    // start of movement detected
    sensorState = SENSOR_STATE_ON;
    movementOnTime = millis();  
  }
  else {
    // end of movement detected
    if (sensorState == SENSOR_STATE_ON) { // check for correct toggling sequence
      sensorState = SENSOR_STATE_OFF;
      movementDuration = millis() - movementOnTime;
      data.add(movementDuration);
    }
  }
}