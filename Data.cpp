#include "Data.hpp"


char Data::getMode()
{
    return mode_;
}

unsigned int Data::getDist()
{
    return dist_;   
}

uint8_t Data::getSensorData()
{
    return sensorData_;
}

char Data::getLineType()
{
    return lineType_;
}

char Data::getNextMove()
{
    return nextMove_;
}

void Data::setMode(char mode)
{
    mode_ = (mode == 's' | mode == 'n' | mode == 'a') ? mode : 'n';
}

void Data::setDist(unsigned int dist)
{
    dist_ = (dist >= 0 ? dist : 0);
}

void Data::setSensorDat(uint8_t sensorData)
{
    sensorData_ = sensorData;
}

void Data::setLineType(char type)
{
    lineType_ = (type == 'r' | type == 'd' | type == 'l') ? type : 'l';
}

void Data::setNextMove(char move)
{
    nextMove_ = (move == 'l' | move == 'r' | move == 'd') ? move : 'd';
}

