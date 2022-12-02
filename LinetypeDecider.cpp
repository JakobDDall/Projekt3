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
    //0bxxx12345
    //1 er venstre sensor
    //2 er vesntre front
    //3 er center front
    //4 er højre front
    //5 er højre sensor


    //Logikken her kigger på bits i sensordata, og giver et (temmelig dårligt) gæt på hvilken linje vi er på
    //Kan forbedres meget
    uint8_t sensorData = std::stoi(*sensorDataPointer_);


    *linetypePointer_ = TYPE_UNKNOWN;
    return;
    
    if(!(sensorData & FRONT) && (sensorData & LEFT) && (sensorData & RIGHT)) 
    {
        *linetypePointer_ = TYPE_TJUNCTION;
    }
    else if((sensorData & FRONT) && (sensorData & LEFT) && (sensorData & RIGHT)) 
    {
        *linetypePointer_ = TYPE_4WAY;
    }
    else if((sensorData & LEFT) && !(sensorData & RIGHT)) 
    {
        *linetypePointer_ = TYPE_LEFT;
    }
    else if((sensorData & RIGHT) && !(sensorData & LEFT)) 
    {
        *linetypePointer_ = TYPE_RIGHT;
    }
    else if((sensorData & FRONT) && !(sensorData & LEFT) && !(sensorData & RIGHT)) 
    {
        *linetypePointer_ = TYPE_STRAIGHT;
    }
    else
    {
        *linetypePointer_ = TYPE_UNKNOWN;
    }
   
}
