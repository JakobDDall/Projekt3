#include "SpiDevice.hpp"

SpiDevice::SpiDevice(int mode, int speed, int delay, int wordlen)
{
    spi_config_.mode = mode;
    spi_config_.speed = speed;
    spi_config_.delay = delay;
    spi_config_.bits_per_word = wordlen;
    mySpi_ = new SPI("/dev/spidev1.2", &spi_config_); //Åbner SPI node på RPi og sætter dens config
}

SpiDevice::~SpiDevice()
{
    delete mySpi_;
}


uint8_t SpiDevice::requestData(uint8_t request)
{
    if (!mySpi_->begin()) //Hvis SPI transfer ikke kan begyndes
    {
        return 0x01;
    }
    //Clear TX og RX buffers
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_)); 

    //Lægger request ind i TX buffer
    memcpy(tx_buffer_, &request, sizeof(request));   

    //Sender SPI request (TX buffer) og gemmer SPI response (RX buffer)
    mySpi_->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));

    //Returnerer SPI response
    return rx_buffer_[0];
}


