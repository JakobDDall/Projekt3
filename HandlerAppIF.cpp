#include "HandlerAppIF.hpp"
#include "defines.hpp"
#include <unistd.h>

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

    //Bed PSoC om at sende distance
    //Læs distance og bed om sensor på samme tid
    //Læs sensor
    //Send cmd

    int tmp = std::stoi(*(distPointer_));
    spiDevice_.requestData(distRequest_); //Bed om dist. Ignorer svar
    (spiDevice_.requestData(0x00)); //dummy
    tmp += (spiDevice_.requestData(0x00)); //Modtag dist. 
    (spiDevice_.requestData(sensorRequest_)); // Bed om sensor
    std::to_string(spiDevice_.requestData(0x00)); //dummy
    *sensorDataPointer_= std::to_string(spiDevice_.requestData(0x00)); //Modtag sensor
    *distPointer_ = std::to_string(tmp);
}

void HandlerAppIF::sendCmd()
{
    uint8_t cmd;

    // if (*lastMove_ == *nextMovePointer_) //Hvis der ikke er sket ændringer i ønsket move, er der ingen grund til at sende besked
    // {
    //     printf("Move did not change from last loop \n");
    //     return;
    // }
    

    if (*modePointer_ == "Simple" || *modePointer_ == "Advanced")
    {
        if (*nextMovePointer_ == TYPE_RIGHT)
        {
            cmd = 0x11;
        }
        else if(*nextMovePointer_ == TYPE_LEFT)
        {
            cmd = 0x12;
        }
        else if(*nextMovePointer_ == TYPE_STRAIGHT)
        {
            cmd = 0x13;
        }
        else if(*nextMovePointer_ == TYPE_UTURN)
        {
            cmd = 0x14;
        }
        else if(*nextMovePointer_ == TYPE_STOP)
        {
            cmd = 0x15;
        }
    }
    else if(*modePointer_ == "STOP")
    {
        cmd = 0x15;    
    }   


    spiDevice_.requestData(cmd); //Send beskeden
    *lastMove_ = *nextMovePointer_; //Opdater lastmove
}

uint8_t HandlerAppIF::spiDummy()
{
    return 69;
}




