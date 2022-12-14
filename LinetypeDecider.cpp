#include "LinetypeDecider.hpp"
#include "defines.hpp"

LinetypeDecider::LinetypeDecider(Data& data)
{
    currentMode_ = data.getModeP();
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
    
    if(*currentMode_ == "Simple")
    {
        switch(sensorData)
        {
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

            case 0b00101000: // Forreste og bagerst venstre
                *linetypePointer_ = TYPE_STRAIGHT; 
                break;

            case 0b00001010: //Forrst og bagerst højre
                *linetypePointer_ = TYPE_STRAIGHT; 
                break;
            case 0b00001001: //Bagerst og forrest
                *linetypePointer_ = TYPE_STRAIGHT; 
                break;

            case 0b00111111: //ALLE
                *linetypePointer_ = TYPE_STOP; 
                break;

            default:
                *linetypePointer_ = TYPE_UNKNOWN;
                break;
        }
    }
    else if(*currentMode_ == "Advanced")
    {
        switch(sensorData)
        {
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

            //case 0b00101000: // Forreste og bagerst venstre
            //    *linetypePointer_ = TYPE_STRAIGHT; 
            //    break;

            //case 0b00001010: //Forrst og bagerst højre
            //    *linetypePointer_ = TYPE_STRAIGHT; 
            //    break;
            case 0b00001001: //Bagerst og forrest
                *linetypePointer_ = TYPE_STRAIGHT; 
                break;

            case 0b00111111: //ALLE
                *linetypePointer_ = TYPE_STOP; 
                break;

            case 0b00001011:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00011011:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001111:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001010:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00011010:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001110:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;
            
            case 0b00000110:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00000111:
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;
            
            case 0b00100011: //Tre bagerste
                *linetypePointer_ = TYPE_TJUNCTION2; 
                break;

            case 0b00100010:
                *linetypePointer_ = TYPE_TJUNCTION2; 
                break;

            case 0b00101000:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00111000:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00101100:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;
            
            case 0b00101001:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00111001:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00101101:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00110001:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;
            
            case 0b00110000:
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;
            

            //case 0b00000001:
                //*linetypePointer_ = TYPE_UTURN;
              //  break;

            case 0b00101010:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00111010:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101110:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101011:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00111011:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101111:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00110011:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00110010:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00100111:
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00100110:
                *linetypePointer_ = TYPE_4WAY;
                break;

            default:
                *linetypePointer_ = TYPE_UNKNOWN;
                break;
        }












        

    }





   
   
}
