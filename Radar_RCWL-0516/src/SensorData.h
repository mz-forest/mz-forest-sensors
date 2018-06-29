// SensorData.h
//
// Andre Meyer, mail@andmeyer.ch
//
// Class for storing sensor data


#ifndef _SENSORDATA_H
#define _SENSORDATA_H

#include <stdint.h>

#define BUFFER_SIZE 256

class SensorData {

    public:

        SensorData();
        virtual ~SensorData();

        int setBinBorders(unsigned int* binBorders, int len);
        
        int clear();
        int add(unsigned int val);

        int getNumBins();
        int getBins(uint16_t* bins);
        int printBins();
        
        int printData();

    private:
        int _numBins;
        uint16_t* _bins;
        unsigned int* _binBorders;
        unsigned int _dataBuffer[BUFFER_SIZE];
        int _dataIndex;
        bool _dataOverflow;

};

#endif // _SENSORDATA_H