// RadarSensor_RCWL0516.cpp

#include "RadarSensor_RCWL0516.h"

RadarSensor_RCWL0516::RadarSensor_RCWL0516() : _interruptPin(-1), _enablePin(-1), _configured(false) {

}

RadarSensor_RCWL0516::~RadarSensor_RCWL0516() {

}

int RadarSensor_RCWL0516::setInterruptPin(int pin) {
    _interruptPin = pin;
}

int RadarSensor_RCWL0516::setEnablePin(int pin) {
    _enablePin = pin;
}

int RadarSensor_RCWL0516::getInterruptPin() {
    return _interruptPin;
}

int RadarSensor_RCWL0516::getEnablePin() {
    return _enablePin;
}

int RadarSensor_RCWL0516::configure() {
    if (_interruptPin < 0 || _enablePin < 0) {
        return 1;
    }
    pinMode(_interruptPin, INPUT_PULLDOWN);
    // configure sensor enable pin
    pinMode(_enablePin, OUTPUT);
    _configured = true;
}

int RadarSensor_RCWL0516::enable() {
    if (!_configured) {
        return 1;
    }
    digitalWrite(_enablePin, HIGH); // set enable pin
    return 0;
}

int RadarSensor_RCWL0516::disable() {
    if (!_configured) {
        return 1;
    }
    digitalWrite(_enablePin, LOW);
    return 0;
}


