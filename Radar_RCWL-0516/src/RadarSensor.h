// RadarSensor.h

#ifndef _RADARSENSOR_H_
#define _RADARSENSOR_H_

#include "RadarSensor_RCWL0516.h"



extern RadarSensor_RCWL0516 radarSensor;
extern SensorData data;

void setupRadarSensor();

void enableRadarSensor();

void configureStatusPins();

void radarSensorCallback();

void readRadarSensor(uint16_t* ptr, int len);

void printRadarSensor();

#endif // _RADARSENSOR_H_