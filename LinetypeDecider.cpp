#include "LinetypeDecider.hpp"


LinetypeDecider::LinetypeDecider(/* args */)
{

}


LinetypeDecider::~LinetypeDecider()
{

}


void LinetypeDecider::updateData(Data& data)
{
    determineLinetype(data);
}

void LinetypeDecider::determineLinetype(Data& data) //Skal opdateres så den detekterer alle linjetyper
{
    uint8_t sensorData = data.getSensorData();
    if(sensorData >= 4) //Højre sensor er 3. bit
    {
        data.setLineType('r');
    }
    else if(sensorData > 1 && sensorData < 4) //Front/midt sensor er 2. bit
    {
        data.setLineType('d');
    }
    else if(sensorData == 1) //Venstre sensor er 1. bit
    {
        data.setLineType('l');
    }
}
