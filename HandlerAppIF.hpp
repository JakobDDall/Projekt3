#pragma once
#include "Data.hpp"
#include <spidev_lib++.h>

class HandlerAppIF
{
public:
    HandlerAppIF(int mode=0, int speed=1000000, int delay=0, int bits_per_word=8); //Indsæt defaultværdier
    ~HandlerAppIF();
    void updateData(Data& data);
    void sendCmd(Data& data);

private:
    void requestData(Data& data);
    int mode_;
    int speed_;
    spi_config_t spi_config_;
    uint8_t tx_buffer_[2];
    uint8_t rx_buffer_[2];
    SPI *mySPI;
    const uint16_t request_ = 0x5555; //Denne skal sættes til en hardcoded værdi, som sendes fra RPi til PSoC ved spi request
};

