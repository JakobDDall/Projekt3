#include "Data.hpp"


std::string* Data::getModeP()
{
    return &mode_;
}

std::string* Data::getDistP()
{
    return &dist_;   
}

std::string* Data::getSensorDataP()
{
    return &sensorData_;
}

std::string* Data::getLineTypeP()
{
    return &lineType_;
}

std::string* Data::getNextMoveP()
{
    return &nextMove_;
}

void Data::setMode(std::string mode)
{
    mode_ = mode;
}

void Data::setDist(std::string dist)
{
    dist_ = dist;
}

void Data::setSensorData(std::string sensorData)
{
    sensorData_ = sensorData;
}

void Data::setLineType(std::string type)
{
    lineType_ = type;
}

void Data::setNextMove(std::string move)
{
    nextMove_ = move;
}

void Data::addSensorData(std::string data)
{
    
}
