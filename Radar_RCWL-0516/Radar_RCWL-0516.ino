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


#ifdef ARDUINO_SAMD_FEATHER_M0 // pin defines for Adafruit Feather M0
const int LED_RED = 0;
const int LED_GREEN = 1;
const int LED_BLUE = 5;
const int SENSOR_OUT_PIN = 13;
const int SENSOR_EN_PIN = 12;
#endif

// pin defines for other boards can be added here.

int movementOn = LOW; // LOW means no movement detected (active high signal)
int movementOnLast = LOW;

unsigned long startTime;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(SENSOR_OUT_PIN, INPUT);
  pinMode(SENSOR_EN_PIN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(SENSOR_EN_PIN, LOW);
  Serial.begin(9600);
  startTime = millis();
  
}

void loop() {
  unsigned long now = millis();
  if (((now-startTime)/5000)%2 == 0) {
    digitalWrite(SENSOR_EN_PIN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
  else {
    digitalWrite(SENSOR_EN_PIN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  }
  movementOnLast = movementOn;
  movementOn = digitalRead(SENSOR_OUT_PIN);
  if (movementOn != movementOnLast) {
    if (movementOn == HIGH) {
        Serial.println("MOVEMENT DETECTED!");
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
    }
    else {
        Serial.println("silent");
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
    }  
  }
  delay(200);
}