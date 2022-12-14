#include "HandlerAppIF.hpp"
#include "defines.hpp"
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

HandlerAppIF::HandlerAppIF(Data& data)
{
    //Get datavariables as pointers
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
    //Læs distance
    //Bed om sensordata
    //Læs sensordata
    //Det man requester bliver først sendt næste SPI transfer igen, herved anvendes dummy requests.
    double tmp = std::stod(*(distPointer_));
    spiDevice_.requestData(distRequest_); //Bed om dist. Ignorer svar
    (spiDevice_.requestData(0x00)); //dummy
    tmp += (static_cast<int8_t>(spiDevice_.requestData(0x00)) * cmPerClockCycle); //Modtag dist.
    (spiDevice_.requestData(sensorRequest_)); // Bed om sensor
    std::to_string(spiDevice_.requestData(0x00)); //dummy
    *sensorDataPointer_= std::to_string(spiDevice_.requestData(0x00)); //Modtag sensor
    *distPointer_ = std::to_string(tmp);
}

void HandlerAppIF::sendCmd()
{
    uint8_t cmd;
    std::fstream dataFile_;

    if (*lastMove_ == *nextMovePointer_) //Hvis der ikke er sket ændringer i ønsket move, er der ingen grund til at sende besked
    {
        return;
    }

    //Bestem hvilken kommando skal sendes til PSoC
    if (*modePointer_ == "Simple" || *modePointer_ == "Advanced")
    {
        if (*nextMovePointer_ == MOV_LEFT)
        {
            cmd = CMD_LEFTTURN;
        }
        else if(*nextMovePointer_ == MOV_RIGHT)
        {
            cmd = CMD_RIGHTTURN;
        }
        else if(*nextMovePointer_ == MOV_STRAIGHT)
        {
            cmd = CMD_STRAIGHT;
        }
        else if(*nextMovePointer_ == MOV_STOP)
        {
            cmd = CMD_STOP;
        }
        else if(*nextMovePointer_ == MOV_ADJ_LEFT)
        {
            cmd = CMD_ADJ_LEFT;
        }
        else if(*nextMovePointer_ == MOV_ADJ_RIGHT)
        {
            cmd = CMD_ADJ_RIGHT;
        }
    }
    else if(*modePointer_ == "STOP")
    {
        cmd = CMD_STOP;    
    }   


    spiDevice_.requestData(cmd); //Send beskeden
    *lastMove_ = *nextMovePointer_; //Opdater lastmove
}

