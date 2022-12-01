#include "Data.hpp"


std::string* Data::getMode()
{
    return &mode_;
}

std::string* Data::getDist()
{
    return &dist_;   
}

std::string* Data::getSensorData()
{
    return &sensorData_;
}

std::string* Data::getLineType()
{
    return &lineType_;
}

std::string* Data::getNextMove()
{
    return &nextMove_;
}
