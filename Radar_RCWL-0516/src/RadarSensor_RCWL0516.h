// RadarSensor_RCWL0516.h

#ifndef _RADARSENSOR_RCWL0516_H_
#define _RADARSENSOR_RCWL0516_H_

class RadarSensor_RCWL0516 {
    public:
        RadarSensor_RCWL0516();
        virtual ~RadarSensor_RCWL0516();

        int setInterruptPin();
        int setEnablePin();

        int getInterruptPin();
        int getEnablePin();

        int setInterruptData();

        int configurePins();
        int enable();


        void IRQ();

    private:
        int _interruptPin;
        int _enablePin;
        SensorData* _interruptData;
};

#endif // _RADARSENSOR_RCWL0516_H_