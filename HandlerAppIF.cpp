#include "HandlerAppIF.hpp"

HandlerAppIF::HandlerAppIF(Data& data)
{
    distPointer_ = data.getDist();
    sensorDataPointer_ = data.getSensorData();
    nextMovePointer_ = data.getNextMove();
}


HandlerAppIF::~HandlerAppIF()
{
}



void HandlerAppIF::updateData()
{
    *distPointer_ = std::to_string(spiDevice_.requestData(distRequest_));
    *sensorDataPointer_ = std::to_string(spiDevice_.requestData(sensorRequest_));

    // *distPointer_ = std::to_string((int)spiDummy());
    // *sensorDataPointer_ = std::to_string((int)spiDummy());
}


void HandlerAppIF::sendCmd()
{
    uint8_t cmd;

    if (*nextMovePointer_ == "Right")
    {
        cmd = 0x11;
    }
    else if(*nextMovePointer_ == "Left")
    {
        cmd = 0x12;
    }
    else if(*nextMovePointer_ == "Straight")
    {
        cmd = 0x13;
    }
    else if(*nextMovePointer_ == "Uturn")
    {
        cmd = 0x14;
    }
    else if(*nextMovePointer_ == "Stop")
    {
        cmd = 0x15;
    }
    
    spiDevice_.sendData(cmd);
}

uint8_t HandlerAppIF::spiDummy()
{
    return 69;
}


