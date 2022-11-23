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

private:
    SpiDevice spiDevice_;
    std::string* distPointer_;
    std::string* sensorDataPointer_;
    std::string* nextMovePointer_;
    const uint8_t distRequest_ = 0x55; //Denne skal sættes til en hardcoded værdi, som sendes fra RPi til PSoC ved spi request
    const uint8_t sensorRequest_ = 0x44;
};

