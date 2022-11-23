#include "LinetypeDecider.hpp"


LinetypeDecider::LinetypeDecider(Data& data)
{
    sensorDataPointer_ = data.getSensorData();
    linetypePointer_ = data.getLineType();
}


LinetypeDecider::~LinetypeDecider()
{

}


void LinetypeDecider::updateData()
{
    determineLinetype();
}

void LinetypeDecider::determineLinetype() //Skal opdateres så den detekterer alle linjetyper
{
    uint8_t sensorData = std::stoi(*sensorDataPointer_);
    if(sensorData >= 4) //Højre sensor er 3. bit
    {
        *linetypePointer_ = "Linetype: r";
    }
    else if(sensorData > 1 && sensorData < 4) //Front/midt sensor er 2. bit
    {
        *linetypePointer_ = "Linetype: d";
    }
    else if(sensorData == 1) //Venstre sensor er 1. bit
    {
        *linetypePointer_ = "Linetype: l";
    }
}
