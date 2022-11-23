#pragma once
#include <stdint.h>

// LineBot v 1.0
// Data-class

// Indeholder al systemets data, og get/set funktioner hertil. Fungerer som bindeled mellem forskellige klasser.


class Data
{
public:
    char getMode();
    unsigned int getDist();
    uint8_t getSensorData();
    char getLineType();
    char getNextMove();

    void setMode(char mode);
    void setDist(unsigned int dist);
    void setSensorDat(uint8_t sensorData);
    void setLineType(char type);
    void setNextMove(char move);
private:
    char mode_;
    unsigned int dist_;
    uint8_t sensorData_;
    char lineType_;
    char nextMove_;
    const int N_OF_SENSORS = 8;

};




