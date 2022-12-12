#include "HandlerAppIF.hpp"
#include "defines.hpp"
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

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
    std::fstream dataFile_;

    if (*lastMove_ == *nextMovePointer_) //Hvis der ikke er sket ændringer i ønsket move, er der ingen grund til at sende besked
    {
        printf("Move did not change from last loop \n");
        return;
    }
       
        dataFile_.open("Move.txt", std::fstream::out | std::fstream::app);
        dataFile_ << "\n";
        dataFile_ << *nextMovePointer_ << std::endl;
        dataFile_.close();


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

uint8_t HandlerAppIF::spiDummy()
{
    return 69;
}




