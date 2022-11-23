// #include "SpiDevice.hpp"

// SpiDevice::SpiDevice(int mode, int speed, int delay, int wordlen)
// {
//     spi_config_.mode = mode;
//     spi_config_.speed = speed;
//     spi_config_.delay = delay;
//     spi_config_.bits_per_word = bits_per_word;
//     mySPI_ = new SPI("/dev/spidev1.2", &spi_config_);
// }

// SpiDevice::~SpiDevice()
// {
//     delete mySpi;
// }


// uint8_t SpiDevice::requestData(uint8_t request)
// {
//     if (!mySPI_.begin()) //Hvor ofte skal det her skrives? Måske bare en enkelt gang i constructor??
//     {
//         std::cout << "Error in spi.begin()! \n " << std::endl;
//         break;
//     }
    
//     memset(tx_buffer_,0,sizeof(tx_buffer_));
//     memset(rx_buffer_,0,sizeof(rx_buffer_)); 
//     memcpy(tx_buffer_, &request, sizeof(request));   
//     printf("sending %X request, to spidev in full duplex \n ",tx_buffer_[0]);
//     mySPI->xfer(tx_buffer_,sizeof(tx_buffer_),rx_buffer_,sizeof(rx_buffer_));
//     printf("Dist er: %i\n",rx_buffer_[0]);
//     return rx_buffer_[0];
// }

// uint8_t SpiDevice::sendData()
// {
//     //Skal laves. Ved ik hvordan man sender uden at læse? er måske same
// }

