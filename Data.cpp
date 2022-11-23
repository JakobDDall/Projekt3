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

void Data::setMode(std::string mode)
{
    mode_ = mode;
    //mode_ = (mode == "r" | mode == "n" | mode == "") ? mode : "n";
}

void Data::setDist(std::string dist)
{
    dist_ = dist;
    //dist_ = (dist != "0" ? dist : "0");
}

void Data::setSensorData(std::string sensorData)
{
    sensorData_ = sensorData;
}

void Data::setLineType(std::string type)
{
    lineType_ = type;
    //lineType_ = (type == "r" | type == "d" | type == "l") ? type : "l";
}

void Data::setNextMove(std::string move)
{
    nextMove_ = move;
    //nextMove_ = (move == "l" | move == "r" | move == "d") ? move : "d";
}

