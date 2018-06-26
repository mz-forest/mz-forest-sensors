// Evaluation of Infrared Sensors
//
// Andre Meyer, mail@andmeyer.ch
//
// DESCRIPTION
// Simple sketch to detect obstacles in range of an infrared sensor
//
// COMPONENTS
// - Adafruit Feather M0 Wifi (1x)
// - Flying-Fish IR Sensor (1x)
// - Green LED (1x)
// - Red LED (1x)
// - 220R resistor (2x)


#ifdef ARDUINO_SAMD_FEATHER_M0 // pin defines for Adafruit Feather M0
const int LED_RED = 0;
const int LED_GREEN = 1;
const int SENSOR_OUT_PIN = 13;
#endif

// pin defines for other boards can be added here.

int obstacleInRange = HIGH; // HIGH means no obstacle in range (active low signal)
int obstacleInRangeLast = HIGH;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(SENSOR_OUT_PIN, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  obstacleInRangeLast = obstacleInRange;
  obstacleInRange = digitalRead(SENSOR_OUT_PIN);
  if (obstacleInRange != obstacleInRangeLast) {
    if (obstacleInRange == LOW) {
        Serial.println("OBSTACLE IN RANGE!");
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
    }
    else {
        Serial.println("clear");
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
    }  
  }
  delay(200);
}