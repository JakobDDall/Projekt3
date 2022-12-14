#pragma once
#include "Data.hpp"
#include "SpiDevice.hpp"
#include <string>

class HandlerAppIF
{
public:
    HandlerAppIF(Data& data); 
    ~HandlerAppIF();
    void updateData();
    void sendCmd();
    void sendMode();

private:
    SpiDevice spiDevice_;
    std::string* distPointer_;
    std::string* sensorDataPointer_;
    std::string* nextMovePointer_;
    std::string* modePointer_;
    std::string* lastMove_;
    const uint8_t distRequest_ = distRequest;
    const uint8_t sensorRequest_ = sensorRequest;
    const float cmPerClockCycle = 0.054; //Dette er antallet af cm som LineBot kører pr. clock fra encoders. 
                                         //Der er 380 clock signaler pr hele hjul rotation. Linebottens diameter er 6,634cm.
                                         //Herved er omkredsen 20,84cm. Divideres dette med 380, får vi 0,054cm pr clock cycle.
};

