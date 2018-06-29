// SensorData.cpp

#include "SensorData.h"
#include "limits.h"
#include "Arduino.h"

SensorData::SensorData() : _numBins(0), _bins(NULL), _binBorders(NULL), _dataIndex(0), _dataOverflow(false) {
    clear();
}

SensorData::~SensorData() {
    if (_bins) {
        free(_bins);
        _bins = NULL;
    }
    if (_binBorders) {
        free(_binBorders);
        _binBorders = NULL;
    }
}

int SensorData::setBinBorders(unsigned int* binBorders, int len) {
    _numBins = len+1;
    if (_binBorders) {
        free(_binBorders);
    }
    _binBorders = (unsigned int*)malloc(len*sizeof(unsigned int));
    memcpy(_binBorders, binBorders, len*sizeof(unsigned int));
    if (_bins) {
        free(_bins);
    }
    _bins = (uint16_t*)malloc(_numBins*sizeof(uint16_t));
    clear(); // clear data structure
}

int SensorData::clear() {
    // clear bins
    if (_bins) {
        memset(_bins, 0, _numBins*sizeof(uint16_t));
    }
    // clear buffer
    memset(_dataBuffer, 0, BUFFER_SIZE*sizeof(unsigned int));
    _dataIndex = 0;
    _dataOverflow = false;
}

int SensorData::add(unsigned int val) {
    // fill bin
    if (_bins) {
        int binIdx = _numBins-1;
        for (int i=0; i<_numBins-1; i++) {
            if (val < _binBorders[i]) {
                binIdx = i;
                break;
            }
        }
        _bins[binIdx]++;    
    }
    // fill buffer
    if (_dataIndex < BUFFER_SIZE) {
        _dataBuffer[_dataIndex++] = val;
    }
    else {
        _dataOverflow = true;
    }
    return 0;
}

int SensorData::getNumBins() {
    return _numBins;
}

int SensorData::getBins(uint16_t* bins) {
    memcpy(bins, _bins, _numBins*sizeof(uint16_t));
    return 0;
}

int SensorData::printBins() {
    uint16_t* bins = (uint16_t*)malloc(_numBins*sizeof(uint16_t));
    getBins(bins);
    for (int i=0; i<_numBins; i++) {  
        Serial.print("[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(bins[i]);
        Serial.print(" ");
    }
    Serial.println();
    return 0;
}

int SensorData::printData() {
    //Serial.print("index: ");
    //Serial.println(_dataIndex);
    //Serial.print("overflow: ");
    //Serial.println(_dataOverflow);
    for (int i=0; i<_dataIndex; i++) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(_dataBuffer[i]);
    }
    return 0;
}


