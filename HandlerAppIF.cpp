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
    *distPointer_ = spiDevice_.requestData(distRequest_);
    *sensorDataPointer_ = spiDevice_.requestData(sensorRequest_);
}


void HandlerAppIF::sendCmd()
{
    //spiDevice.sendData(*nextMovePointer);
}


