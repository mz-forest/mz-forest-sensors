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
const int SENSOR_INT_PIN = 13; // sensor interrupt pin
const int SENSOR_EN_PIN = 12;
#endif

// pin defines for other boards can be added here.

volatile int count = 0;

void setup() {
  configurePins();
  attachInterrupt(digitalPinToInterrupt(SENSOR_INT_PIN), sensorIRQ, RISING);

  // set default pin levels
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(SENSOR_EN_PIN, HIGH);
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  
  Serial.print("count ");
  Serial.println(count);
  if (count > 5) {
    digitalWrite(LED_RED, HIGH);
    
  }
  if (count > 10) {
    digitalWrite(LED_BLUE, HIGH);
  }

  delay(1000);
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
  count++;
}