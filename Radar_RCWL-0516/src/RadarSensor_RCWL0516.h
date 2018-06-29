// RadarSensor_RCWL0516.h

#ifndef _RADARSENSOR_RCWL0516_H_
#define _RADARSENSOR_RCWL0516_H_

#include "Arduino.h"
#include "SensorData.h"



class RadarSensor_RCWL0516 {
    public:
        RadarSensor_RCWL0516();
        virtual ~RadarSensor_RCWL0516();

        int setInterruptPin(int pin); // interrupt pin has to be interrupt capable
        int setEnablePin(int pin);

        int getInterruptPin();
        int getEnablePin();

        int configure();
        int enable();
        int disable();

        void sensorIRQ();
        
    private:
        int _interruptPin;
        int _enablePin;
        bool _configured;
        
        

};


#endif // _RADARSENSOR_RCWL0516_H_