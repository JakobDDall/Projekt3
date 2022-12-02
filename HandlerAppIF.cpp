#include "HandlerAppIF.hpp"

HandlerAppIF::HandlerAppIF(Data& data)
{
    distPointer_ = data.getDistP();
    sensorDataPointer_ = data.getSensorDataP();
    nextMovePointer_ = data.getNextMoveP();
    modePointer_ = data.getModeP();


    lastMove_ = new std::string;
}


HandlerAppIF::~HandlerAppIF()
{
    delete lastMove_;
}



void HandlerAppIF::updateData()
{
    int tmp = std::stoi(*(distPointer_));
    tmp += spiDevice_.requestData(distRequest_);
    *distPointer_ = std::to_string(tmp);
    *sensorDataPointer_ = std::to_string(spiDevice_.requestData(sensorRequest_));


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
        else if(*nextMovePointer_ == "Stop")
        {
            cmd = 0x15;
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




