#include "HandlerAppIF.hpp"

HandlerAppIF::HandlerAppIF(int mode, int speed, int delay, int bits_per_word)
{
    tx_buffer_ = {0x0000};
    rx_buffer_ = {0x0000};
    spi_config_.mode = mode;
    spi_config_.speed = speed;
    spi_config_.delay = delay;
    spi_config_.bits_per_word = bits_per_word;
    mySPI = new SPI("/dev/spidev1.2", &spi_config_);
}


HandlerAppIF::~HandlerAppIF()
{
    delete[] mySPI;
}



void HandlerAppIF::updateData(Data& data)
{
    requestData(data);
}


void HandlerAppIF::sendCmd(Data& data) //Send spi kommando nextMove vha data.getNextMove
{
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_));
    
      
    memcpy(tx_buffer_, (char*)&data.getNextMove(), sizeof(request_)); //Der skal lige være noget andet en data.getNextMove, da det er en char lige nu
    printf("sending %X, to spidev2.1 in full duplex \n ",tx_buffer[0]);
    mySPI->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
    
}


void HandlerAppIF::requestData(Data& data)
{
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_));
    
      
    memcpy(tx_buffer_, (char*)&request_, sizeof(request_)); 
    printf("sending %X, to spidev2.1 in full duplex \n ",tx_buffer[0]);
    mySPI->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));

    //De 8  MSB er distance:
    data.setDist(rx_buffer_[1]);
    //De 8 LSB er sensordata:
    data.setSensorData(rx_buffer_[0]);

}
