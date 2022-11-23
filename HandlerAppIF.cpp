#include "HandlerAppIF.hpp"

HandlerAppIF::HandlerAppIF(int mode, int speed, int delay, int bits_per_word)
{
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_));
    spi_config_.mode = mode;
    spi_config_.speed = speed;
    spi_config_.delay = delay;
    spi_config_.bits_per_word = bits_per_word;
    mySPI = new SPI("/dev/spidev1.2", &spi_config_);
    
}


HandlerAppIF::~HandlerAppIF()
{
    delete mySPI;
}



void HandlerAppIF::updateData(Data& data)
{
    requestData(data);
}


void HandlerAppIF::sendCmd(Data& data) //Send spi kommando nextMove vha data.getNextMove
{
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_)); 
}


void HandlerAppIF::requestData(Data& data)
{
    memset(tx_buffer_,0,sizeof(tx_buffer_));
    memset(rx_buffer_,0,sizeof(rx_buffer_));
    
    if(mySPI->begin())
    {
        //Request distance
        memcpy(tx_buffer_, &distRequest_, sizeof(distRequest_));   
        printf("sending %X, to spidev2.1 in full duplex \n ",tx_buffer_[0]);
        mySPI->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
        printf("Dist er: %i\n",rx_buffer_[0]);
        data.setDist(rx_buffer_[0]);

        memset(tx_buffer_,0,sizeof(tx_buffer_));
        memset(rx_buffer_,0,sizeof(rx_buffer_));


        //Request sensordata
        memcpy(tx_buffer_, &sensorRequest_, sizeof(distRequest_));         
        printf("sending %X, to spidev2.1 in full duplex \n ",tx_buffer_[0]);
        mySPI->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
        printf("Sensordata er: %i\n",rx_buffer_[0]);
        data.setSensorData(rx_buffer_[0]);
    }


}
