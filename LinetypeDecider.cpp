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


    //Logikken her kigger på bits i sensordata, og bestemmer linjetypen
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

            case 0b00001001: //Bagerst og forrest
                *linetypePointer_ = TYPE_STRAIGHT; 
                break;

            case 0b00111111: //ALLE
                *linetypePointer_ = TYPE_STOP; 
                break;

            case 0b00001011: //forrest, højre og bagerst
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00011011: //venstre forrest, forrest, højre og bagerst
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001111: //forrest, højre forrest, højre og bagerst
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001010: //forrest og højre
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00011010: //venstre forrest, forrest og højre
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00001110: //forrest, højre forrest og højre
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;
            
            case 0b00000110: //højre forrest og højre
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;

            case 0b00000111: //højre forrest, højre og bagerst
                *linetypePointer_ = TYPE_TJUNCTION1;
                break;
            
            case 0b00100011: //venstre, højre og bagerst
                *linetypePointer_ = TYPE_TJUNCTION2; 
                break;

            case 0b00100010: //venstre og højre
                *linetypePointer_ = TYPE_TJUNCTION2; 
                break;

            case 0b00101000: //venstre og forrest
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00111000: //venstre, venstre forrest  og forrest
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00101100: //venstre, forrest og højre forrest
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;
            
            case 0b00101001: //venstre forrest og bagerst
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00111001: //venstre, venstre forrest, forrest og bagerst
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00101101: //venstre, forrest, højre forrest og bagerst
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00110001: //venstre, venstre forrest og bagerst
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;
            
            case 0b00110000: //venstre og venstre forrest
                *linetypePointer_ = TYPE_TJUNCTION3;
                break;

            case 0b00101010: //venstre, forrest og højre
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00111010: //venstre, venstre forrest, forrest og højre
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101110: //venstre, forrest, højre forrest og højre
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101011: //venstre, forrest, højre og bagerst
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00111011: //venstre, venstre forrest, forrest, højre og bagerst
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00101111: //venstre, forrest, højre forrest, højre og bagerst
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00110011: //venstre, venstre forrest, højre og bagerst
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00110010: //venstre, venstre forrest og højre
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00100111: //venstre, højre forrest og bagerst
                *linetypePointer_ = TYPE_4WAY;
                break;

            case 0b00100110: //venstre, højre forrest, og højre
                *linetypePointer_ = TYPE_4WAY;
                break;

            default:
                *linetypePointer_ = TYPE_UNKNOWN;
                break;
        }












        

    }





   
   
}
