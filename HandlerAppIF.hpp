#pragma once
#include "Data.hpp"
#include "SpiDevice.hpp"
#include <string>

#define distRequest 0x55
#define sensorRequest 0x44

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
    std::string* chosenMode_;
    const uint8_t distRequest_ = distRequest; //Denne skal sættes til en hardcoded værdi, som sendes fra RPi til PSoC ved spi request
    const uint8_t sensorRequest_ = sensorRequest;
    uint8_t spiDummy();
};

