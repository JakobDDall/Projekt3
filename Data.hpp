#pragma once
#include <stdint.h>
#include <string>

// LineBot v 1.0
// Data-class

// Indeholder al systemets data, og get/set funktioner hertil. Fungerer som bindeled mellem forskellige klasser.


class Data
{
public:
    std::string* getMode();
    std::string* getDist();
    uint8_t* getSensorData();
    std::string* getLineType();
    std::string* getNextMove();

    void setMode(std::string mode);
    void setDist(std::string dist);
    void setSensorDat(uint8_t sensorData);
    void setLineType(std::string type);
    void setNextMove(std::string move);
private:
    std::string mode_;
    std::string dist_;
    uint8_t sensorData_;
    std::string lineType_;
    std::string nextMove_;
    const int N_OF_SENSORS = 8;

};




