#pragma once
#include <stdint.h>
#include <string>

// LineBot v 1.0
// Data-class

// Contains data for the whole system. Get/set functions has been made to use/set the data. This classe acts as a link between different classes.

class Data
{
public:
    std::string* getModeP();
    std::string* getDistP();
    std::string* getSensorDataP();
    std::string* getLineTypeP();
    std::string* getNextMoveP();

    void setMode(std::string mode);
    void setDist(std::string dist);
    void setSensorData(std::string sensorData);
    void setLineType(std::string type);
    void setNextMove(std::string move);

    void addSensorData(std::string data);

private:
    std::string mode_;
    std::string dist_;
    std::string sensorData_;
    std::string lineType_;
    std::string nextMove_;
};




