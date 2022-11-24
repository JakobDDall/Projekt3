#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spidev_lib++.h>
#include <iostream>

class SpiDevice
{
private:
    spi_config_t spi_config_;
    int mode_;
    int speed_;
    uint8_t tx_buffer_[1];
    uint8_t rx_buffer_[1];
    SPI* mySpi_ = NULL;

public:
    SpiDevice(int mode = 0, int speed = 1000000, int delay = 0, int wordlen = 8);
    ~SpiDevice();
    uint8_t requestData(uint8_t request);
    void sendData(uint8_t cmd);
};
