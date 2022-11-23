#pragma once
#include "Data.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spidev_lib++.h>
#include <unistd.h>


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
    uint8_t tx_buffer_[1];
    uint8_t rx_buffer_[1];
    SPI *mySPI = NULL;
    const uint8_t distRequest_ = 0x55; //Denne skal sættes til en hardcoded værdi, som sendes fra RPi til PSoC ved spi request
    const uint8_t sensorRequest_ = 0x44;
};

