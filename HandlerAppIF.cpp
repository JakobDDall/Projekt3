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
    //*distPointer_ = std::to_string(spiDevice_.requestData(distRequest_));
    //*sensorDataPointer_ = std::to_string(spiDevice_.requestData(sensorRequest_));

    *distPointer_ = std::to_string((int)spiDummy());
    *sensorDataPointer_ = std::to_string((int)spiDummy());
}


void HandlerAppIF::sendCmd()
{
    //spiDevice.sendData(*nextMovePointer);
}

uint8_t HandlerAppIF::spiDummy()
{
    return 69;
}


