// Evaluation of PIR Motion Sensors
//
// Christian Raemy, xxx@xxx.ch
//
// DESCRIPTION
// Simple sketch to detect moving objects (people) in range of a PIR Motion Sensor
//
// COMPONENTS
// - Things UNO (1x)
// - PIR Motion Sensor (1x)
// - Red LED (1x)

#include "src/SensorData.h"
#include <TheThingsNetwork.h>

// Set your AppEUI and AppKey
const char *appEui = "70B3D57ED00101BB";
const char *appKey = "BB6B2D5A2F2377DF1C92AE3810B96051";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

typedef struct 
{
  uint16_t slow;
  uint16_t mid;
  uint16_t quick;
} measurements;

measurements count;
uint32_t refresh_ms = 60000;
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

const int LED_RED = 6;
const int SENSOR_INT_PIN = 7; // sensor interrupt pin

typedef enum {
  SENSOR_STATE_ON,
  SENSOR_STATE_OFF
} sensor_state_t;

volatile sensor_state_t sensorState = SENSOR_STATE_OFF;

SensorData data;
int numBins = 3;
unsigned int binBorders[] = {4000, 6000}; // size is numBins-1

volatile unsigned int movementOnTime, movementDuration;

void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
  delay(500);
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
  delay(500);
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);

  resetCounts(count);
  
  configurePins();
  data.setBinBorders(binBorders, numBins-1);
  
  Serial.begin(9600);
  delay(5000);
  
  // clear data and start data acquisition
  data.clear();
  attachInterrupt(digitalPinToInterrupt(SENSOR_INT_PIN), sensorIRQ, CHANGE);

  // Set callback for incoming messages
  ttn.onMessage(message);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}


void loop() {
  
  Serial.println("Data dump");
  data.printBins();
  data.printData();

  uint16_t* bins = (uint16_t*)malloc(numBins*sizeof(uint16_t));
  data.getBins(bins);
   
  count.quick = bins[0];
  count.mid  = bins[1];
  count.slow = bins[2];

  sendMessage();
  
  data.clear();
  delay(refresh_ms);
}

void configurePins() {
  // configure LED pins
  pinMode(LED_RED, OUTPUT);
  // configure interrupt pin
  pinMode(SENSOR_INT_PIN, INPUT);

}

void sensorIRQ() {
  if (digitalRead(SENSOR_INT_PIN) == HIGH) {
    // start of movement detected
    sensorState = SENSOR_STATE_ON;
    movementOnTime = millis();
    digitalWrite(LED_RED, HIGH);  
  }
  else {
    // end of movement detected
    if (sensorState == SENSOR_STATE_ON) { // check for correct toggling sequence
      sensorState = SENSOR_STATE_OFF;
      movementDuration = millis() - movementOnTime;
      data.add(movementDuration);
      digitalWrite(LED_RED, LOW);
    }
  }
}

void resetCounts(measurements &c)
{
  c.slow = 0;
  c.mid = 0;
  c.quick = 0;
}

//transmit counts to ttn
void sendMessage()
{
  //let's fill the data endianness-agnostic
  byte payload[8];
  payload[0] = count.slow / 256;
  payload[1] = count.slow % 256;
  payload[2] = count.mid / 256;
  payload[3] = count.mid % 256;
  payload[4] = count.quick / 256;
  payload[5] = count.quick % 256;

  payload[6] = refresh_ms / 1000 / 256;
  payload[7] = (refresh_ms / 1000) % 256;
  resetCounts(count);
  // Send it off
  ttn.sendBytes(payload, sizeof(payload));
}

//receiving ttn message
void message(const byte *payload, size_t length, port_t port)
{
  debugSerial.println("-- MESSAGE");
  debugSerial.print(length);
  debugSerial.println(" bytes received:");

  if (length > 0)
  {
    uint32_t newRefresh = 0;
    for(int i = 0; i < length; i++)
    {
      debugSerial.print(payload[i]);
      newRefresh += payload[i] * pow(256, length - i - 1);
    }
    debugSerial.println();
    if(newRefresh < 5) // todo: check if bigger then max(uint32_t / 1000)
    {
      debugSerial.print("Error, Refresh rate has to be bigger then 5s, but it's ");
      debugSerial.println(newRefresh);
      return;
    }
    else if(newRefresh * 1000 > UINT32_MAX)
    {
      debugSerial.print("Error, Refresh rate has to be smaller then UINT32_MAX, but it's ");
      debugSerial.println(newRefresh);
      return;
    }
    refresh_ms = newRefresh * 1000;
    debugSerial.print("New Refresh ratin in ms: ");
    debugSerial.println(refresh_ms);
  }
}

//============= End of TX/RX functions ================
