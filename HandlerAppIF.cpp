#include "HandlerAppIF.hpp"

HandlerAppIF::HandlerAppIF(Data& data)
{
    distPointer_ = data.getDist();
    sensorDataPointer_ = data.getSensorData();
    nextMovePointer_ = data.getNextMove();
    modePointer_ = data.getMode();


    lastMove_ = new std::string;
}


HandlerAppIF::~HandlerAppIF()
{
    delete lastMove_;
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

    if (*lastMove_ == *nextMovePointer_) //Hvis der ikke er sket ændringer i ønsket move, er der ingen grund til at sende besked
    {
        return;
    }
    

    if (*modePointer_ == "Simple" || *modePointer_ == "Advanced")
    {
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
    }
    else if(*modePointer_ == "STOP")
    {
        cmd = 0x15;    
    }   


    spiDevice_.sendData(cmd); //Send beskeden
    *lastMove_ = *nextMovePointer_; //Opdater lastmove
}

uint8_t HandlerAppIF::spiDummy()
{
    return 69;
}




