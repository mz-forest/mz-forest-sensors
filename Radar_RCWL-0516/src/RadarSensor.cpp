

#include "RadarSensor.h"
#include "SensorData.h"

#ifdef ARDUINO_SAMD_FEATHER_M0 // pin defines for Adafruit Feather M0
cconst int SENSOR_INT_PIN = 13; // sensor interrupt pin
const int SENSOR_EN_PIN = 12;
const int DEBUG_PIN = -1; // TBD
#else // pin defines for TheThings Uno (Arduino Leonardo)
const int SENSOR_INT_PIN = 3; // sensor interrupt pin
const int SENSOR_EN_PIN = 4;
const int DEBUG_PIN = 13;
#endif

RadarSensor_RCWL0516 radarSensor;

SensorData data;
int numBins = 3;
unsigned int binBorders[] = {6000, 10000}; // size is numBins-1

void setupRadarSensor() {
    
    data.setBinBorders(binBorders, numBins-1); 
  
    configureStatusPins();

    radarSensor.setInterruptPin(SENSOR_INT_PIN);
    radarSensor.setEnablePin(SENSOR_EN_PIN);
    radarSensor.configure();
  
}

void enableRadarSensor() {
    data.clear();
    attachInterrupt(digitalPinToInterrupt(SENSOR_INT_PIN), radarSensorCallback, CHANGE); // enable interrupt
    radarSensor.enable();
}

void configureStatusPins(){
    pinMode(DEBUG_PIN, OUTPUT);
    digitalWrite(DEBUG_PIN, LOW);
}


void readRadarSensor(uint16_t* ptr, int len) {
    memset(ptr,0xE, len*sizeof(uint16_t));
    if (data.getNumBins() == len) {
        data.getBins(ptr);
    }
}


void printRadarSensor(){
    Serial.println("--- Data for Radar Sensor ---");
    data.printBins();
    data.printData();
    data.clear();
}

// Sensor Callback

typedef enum {
  SENSOR_STATE_ON,
  SENSOR_STATE_OFF
} sensor_state_t;

void radarSensorCallback() {
  static sensor_state_t sensorState = SENSOR_STATE_ON;
  static unsigned int movementOnTime = 0;

  if (digitalRead(SENSOR_INT_PIN) == HIGH) {
    digitalWrite(DEBUG_PIN, HIGH);
    // start of movement detected
    sensorState = SENSOR_STATE_ON;
    movementOnTime = millis();  
  }
  else {
    digitalWrite(DEBUG_PIN, LOW);
    // end of movement detected
    if (sensorState == SENSOR_STATE_ON) { // check for correct toggling sequence
      sensorState = SENSOR_STATE_OFF;
      unsigned int movementDuration = millis() - movementOnTime;
      data.add(movementDuration);
    }
  }
}

