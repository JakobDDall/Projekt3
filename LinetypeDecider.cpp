#include "LinetypeDecider.hpp"
#include "defines.hpp"

LinetypeDecider::LinetypeDecider(Data& data)
{
    sensorDataPointer_ = data.getSensorDataP();
    linetypePointer_ = data.getLineTypeP();
}


LinetypeDecider::~LinetypeDecider()
{

}


void LinetypeDecider::updateData()
{    
    determineLinetype();
}

void LinetypeDecider::determineLinetype() 
{
    //uint 8 indeholdersensordata. Hver bit repræsenterer status af en sensor
    //0bxx123456
    //1 er LEFT
    //2 er FRONTLEFT
    //3 er FRONT
    //4 er FRONTRIGHT
    //5 er RIGHT
    //6 er BACK


    //Logikken her kigger på bits i sensordata, og giver et (temmelig dårligt) gæt på hvilken linje vi er på
    //Kan forbedres meget
    uint8_t sensorData = std::stoi(*sensorDataPointer_);
    sensorData &= 0b00111111; //Clear first 2 bits, leave the rest

    
    if((sensorData & FRONT) && !(sensorData & FRONTLEFT) && !(sensorData & FRONTRIGHT)) 
    {
        *linetypePointer_ = TYPE_STRAIGHT;
    }
    else if((sensorData & FRONT) && (sensorData & FRONTLEFT) && (sensorData & FRONTRIGHT)) 
    {
        *linetypePointer_ = TYPE_TJUNCTION;
    }
    else
    {
        *linetypePointer_ = TYPE_UNKNOWN;
    }
   
}
