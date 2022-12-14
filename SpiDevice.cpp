#include "SpiDevice.hpp"

SpiDevice::SpiDevice(int mode, int speed, int delay, int wordlen)
{
    spi_config_.mode = mode;
    spi_config_.speed = speed;
    spi_config_.delay = delay;
    spi_config_.bits_per_word = wordlen;
    mySpi_ = new SPI("/dev/spidev1.2", &spi_config_);
}

SpiDevice::~SpiDevice()
{
    delete mySpi_;
}


uint8_t SpiDevice::requestData(uint8_t request)
{
    if (!mySpi_->begin()) //Hvor ofte skal det her skrives? Måske bare en enkelt gang i constructor??
    {
        std::cout << "Error in spi.begin()! \n " << std::endl;
        return 0x01;
    }
    
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_)); 
    memcpy(tx_buffer_, &request, sizeof(request));   
    mySpi_->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
    return rx_buffer_[0];
}

void SpiDevice::sendData(uint8_t cmd)
{
    if (!mySpi_->begin()) //Hvor ofte skal det her skrives? Måske bare en enkelt gang i constructor??
    {
        std::cout << "Error in spi.begin()! \n " << std::endl;
        return;
    }
    
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_)); 
    memcpy(tx_buffer_, &cmd, sizeof(cmd));   
    printf("Sending command via SPI: %X \n ",tx_buffer_[0]);
    mySpi_->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
    printf("Received response via SPI: %X \n ",rx_buffer_[0]);
}

