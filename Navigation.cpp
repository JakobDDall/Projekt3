#include "Navigation.hpp"
#include "defines.hpp"
#include <unistd.h>


Navigation::Navigation(/* args */)
{
    handlerAppIF_ = new HandlerAppIF(data_);
    lineDecider_ = new LinetypeDecider(data_);
    touchscreen_ = new TouchscreenCpp("Screen.txt", data_);

        std::cout << "-------------------- Setting initialdata entries ----------" << std::endl;
        data_.setDist("0");
        data_.setLineType("0");
        data_.setMode("STOP");
        data_.setNextMove("0");
        data_.setSensorData("0");


        lastMove_ = new std::string;
}

Navigation::~Navigation()
{
    delete handlerAppIF_;
    delete lineDecider_;
    delete touchscreen_;
    delete lastMove_;
}


void Navigation::startMainLoop()
{
    while (1)
    {
        touchscreen_->updateData(); //Skal ske først! læser brugerinput. Overskriver desuden data... :-)
        handlerAppIF_->updateData(); //Hent ny data fra PSoC
        lineDecider_->updateData(); //del 1 af: Behandl data fra PSoC
        determineNextMove();        //del 2 af: Behandl data fra PSoC
        touchscreen_->updateScreen();
        handlerAppIF_->sendCmd();
        printAllData(); 
        usleep(10000);
    }


}
//Logik til beslutningstagen er som følger:
//Move bestemmes:
    //Navigation -> determineNextMove() forholder sig til hvilken mode der er valg, og kalder passende funktion
    //Denne funktion ser på hvad linebot netop nu er i gang med, og bestemmer næste move herudfra.
    //Eksempelvis: Kører vi ligeud analyserer vi linjetype, er vi ved at dreje, ser vi blot på en enkelt sensor

    //Efter ovenstående har kørt, skulle robotten meget gerne have skrevet et move ind i nextMove variablen i data klassen.

//Move sendes
    //HandlerAppIF holder i hvert gennemløb af main-loop øje med om der er sket ændringer i robottens næste move.
    //Hvis det er tilfældet, sendes ny kommando til PSoC.


void Navigation::determineNextMove()
{
    if (*data_.getModeP() == "STOP") //Hvis stop er valgt, er beslutningen nem
    {
        *data_.getNextMoveP() = TYPE_STOP;
        printf("determine move i stop mode \n");
        return;
    }
    else if (*data_.getModeP() == "Simple")
    {
        determineSimple();
        printf("determine move i simple mode \n");
        return;
    }
    else if (*data_.getModeP() == "Advanced")
    {
        determineAdvanced();
        return;
    }
}

void Navigation::printAllData()
{
    std::cout << "-------------------- Printing all data entries ----------" << std::endl;
    std::cout << "Dist: " << *data_.getDistP() << std::endl;
    std::cout << "Line type: " << *data_.getLineTypeP() << std::endl;
    std::cout << "Mode: " << *data_.getModeP() << std::endl;
    std::cout << "Move: " << *data_.getNextMoveP() << std::endl;
    std::cout << "Sensordata: " << *data_.getSensorDataP() << std::endl;
}

void Navigation::determineSimple()
{
    std::string linetype = *data_.getLineTypeP();
    std::string nextMove = *data_.getNextMoveP();
    uint8_t sensorData = std::stoi(*data_.getSensorDataP());
 
    if(nextMove == MOV_STRAIGHT || nextMove == MOV_ADJ_RIGHT || nextMove == MOV_ADJ_LEFT)
    {
        if(ihavejustturned)
        {
            printf("I made it in here --------------------------------------------------------------------- \n");
            if (turnDone_ == false)
            {
                turning_timer_ = std::chrono::system_clock::now();
                turnDone_ = true;
            }
            if(turnDone_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 1000))
            {
                turnDone_ = false;
                ihavejustturned = false;
            }
        }

        else if(linetype == TYPE_RIGHT) //T-Junction passer ikke i simple|| linetype == TYPE_TJUNCTION)
        {                        
            *data_.getNextMoveP() = MOV_RIGHT;
        }

        else if(linetype == TYPE_LEFT)
        {
            *data_.getNextMoveP() = MOV_LEFT;
        }

        else if((sensorData & SENSOR_FRONTRIGHT) && !(sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_RIGHT;
        }

        else if(!(sensorData & SENSOR_FRONTRIGHT) && (sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_LEFT;
        }
        else if(linetype == TYPE_STRAIGHT)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }

        else if(linetype == TYPE_STOP)
        {
            *data_.getNextMoveP() = MOV_STOP;
        }
    }
    else if (nextMove == MOV_STOP) //Hvis vi er standset
    {
       if (linetype == TYPE_STRAIGHT)
       {
        *data_.getNextMoveP() = MOV_STRAIGHT;
       }
    }
    else if(nextMove == MOV_RIGHT || nextMove == MOV_LEFT)
    {
        if (turning_ == false)
            {
                
                turning_timer_ = std::chrono::system_clock::now();
                turning_ = true;
            }
            if(turning_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 500))
            {
                if(sensorData & SENSOR_FRONT)
                {
                    
                    *data_.getNextMoveP() = MOV_STRAIGHT;
                    turning_ = false;
                    ihavejustturned = true;
                }
            }
    }

    *lastMove_ = *data_.getNextMoveP(); //Opdater lastmove
}

void Navigation::determineAdvanced()
{
    std::string linetype = *data_.getLineTypeP();
    std::string nextMove = *data_.getNextMoveP();
    uint8_t sensorData = std::stoi(*data_.getSensorDataP());
 
    if(nextMove == MOV_STRAIGHT || nextMove == MOV_ADJ_RIGHT || nextMove == MOV_ADJ_LEFT)
    {
        if(ihavejustturned)
        {
            printf("I made it in here --------------------------------------------------------------------- \n");
            if (turnDone_ == false)
            {
                turning_timer_ = std::chrono::system_clock::now();
                turnDone_ = true;
            }
            if(turnDone_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 1000))
            {
                turnDone_ = false;
                ihavejustturned = false;
            }
        }

        else if(linetype == TYPE_RIGHT || linetype == TYPE_TJUNCTION1 || linetype == TYPE_TJUNCTION2 || linetype == TYPE_4WAY || linetype == TYPE_UTURN)
        {                        
            *data_.getNextMoveP() = MOV_RIGHT;
        }

        else if(linetype == TYPE_TJUNCTION3)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }
        else if(linetype == TYPE_LEFT)
        {
            *data_.getNextMoveP() = MOV_LEFT;
        }

        else if((sensorData & SENSOR_FRONTRIGHT) && !(sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_RIGHT;
        }

        else if(!(sensorData & SENSOR_FRONTRIGHT) && (sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_LEFT;
        }
        else if(linetype == TYPE_STRAIGHT)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }

        else if(linetype == TYPE_STOP)
        {
            *data_.getNextMoveP() = MOV_STOP;
        }
    }
    else if (nextMove == MOV_STOP) //Hvis vi er standset
    {
       if (linetype == TYPE_STRAIGHT)
       {
        *data_.getNextMoveP() = MOV_STRAIGHT;
       }
    }
    else if(nextMove == MOV_RIGHT || nextMove == MOV_LEFT)
    {
        if (turning_ == false)
            {
                
                turning_timer_ = std::chrono::system_clock::now();
                turning_ = true;
            }
            if(turning_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 500))
            {
                if(sensorData & SENSOR_FRONT)
                {
                    
                    *data_.getNextMoveP() = MOV_STRAIGHT;
                    turning_ = false;
                    ihavejustturned = true;
                }
            }
            else if(nextMove == MOV_LEFT && sensorData & SENSOR_RIGHT)
            {
                *data_.getNextMoveP() = MOV_RIGHT;
                turning_ = false;
            }
    }



    *lastMove_ = *data_.getNextMoveP(); //Opdater lastmove
}
