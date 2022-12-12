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

    switch(sensorData)
    {
        case 0b00100011: //Tre bagerste
            *linetypePointer_ = TYPE_TJUNCTION; 
            break;

        case 0b00100001: //Bagerst midt og vesntre
            *linetypePointer_ = TYPE_LEFT; 
            break;

        case 0b00100000: //Bagerst venstre
            *linetypePointer_ = TYPE_LEFT; 
            break;

        case 0b00000011: //Bagerst midt og højre
            *linetypePointer_ = TYPE_RIGHT; 
            break;

        case 0b00000010: //Bagerst højre
            *linetypePointer_ = TYPE_RIGHT; 
            break;
        
        case 0b00001000: //Kun forreste
            *linetypePointer_ = TYPE_STRAIGHT; 
            break;
        case 0b00001001: //Bagerst og forrest
            *linetypePointer_ = TYPE_STRAIGHT; 
            break;

        default:
            *linetypePointer_ = TYPE_UNKNOWN;
            break;
    }
   
}
