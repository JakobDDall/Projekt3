#include "Navigation.hpp"
#include "defines.hpp"
#include <unistd.h>

Navigation::Navigation(/* args */)
{
    handlerAppIF_ = new HandlerAppIF(data_);
    lineDecider_ = new LinetypeDecider(data_);
    touchscreen_ = new TouchscreenCpp("Screen.txt", data_);

        std::cout << "-------------------- Setting initialdata entries ----------" << std::endl;
        data_.setDist("testDist");
        data_.setLineType("testType");
        data_.setMode("testMode");
        data_.setNextMove("testMove");
        data_.setSensorData("testData");
}

Navigation::~Navigation()
{
    delete handlerAppIF_;
    delete lineDecider_;
    delete touchscreen_;
}


void Navigation::startMainLoop()
{
    while (1)
    {
           //printAllData();
        touchscreen_->updateData(); //Skal ske først! læser brugerinput. Overskriver desuden data... :-)
    
    // Hvis mode er stop, så send STOP!
        handlerAppIF_->updateData(); //Hent ny data fra PSoC
        lineDecider_->updateData(); //del 1 af: Behandl data fra PSoC
        determineNextMove();        //del 2 af: Behandl data fra PSoC
        touchscreen_->updateScreen();
        handlerAppIF_->sendCmd();
        printAllData();
        sleep(1);
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
    if (*data_.getModeP == "Stop") //Hvis stop er valgt, er beslutningen nem
    {
        *data_.getNextMoveP() = "Stop";
        return;
    }
    else if (*data_.getModeP == "Simple")
    {
        determineSimple();
        return;
    }
    else if (*data_.getModeP == "Advanced")
    {
        //Kald determine advanced
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
    if (nextMove == TYPE_STRAIGHT || nextMove == TYPE_STOP) //Hvis vi kører ligeud, eller er standset skal vi blot holde øje med linjetypen.
    {
        if ((linetype == TYPE_4WAY) || (linetype == TYPE_TJUNCTION) || (linetype == TYPE_RIGHT))
        {
            *data_.getNextMoveP() == TYPE_RIGHT;
        }
        else if ((linetype == TYPE_LEFT))
        {
            *data_.getNextMoveP() == TYPE_LEFT;
        }
        else if ((linetype == TYPE_STRAIGHT))
        {
            *data_.getNextMoveP() == TYPE_STRAIGHT;
        }
        else if ((linetype == TYPE_UTURN))
        {
            *data_.getNextMoveP() == TYPE_UTURN;
        }
        else if ((linetype == TYPE_UNKNOWN))
        {
            *data_.getNextMoveP() == TYPE_STOP;
        } 
    }
    else if (nextMove == TYPE_RIGHT) //Hvis vi drejer til højre, skal vi vente til vi igen kan se en linje med højre sensor
    {
        if (sensorData & RIGHT)
        {
            *data_.getNextMoveP() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
    else if (nextMove == TYPE_LEFT) //Hvis vi drejer til vesntre, skal vi vente til vi igen kan se en linje med vesntre sensor
    {
        if (sensorData & LEFT)
        {
            *data_.getNextMoveP() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
    else if (nextMove == TYPE_UTURN) //Hvis vi laver u vending, skal vi vente til vi igen kan se en linje med front sensor
    {
        if (sensorData & FRONT)
        {
            *data_.getNextMoveP() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
}

void Navigation::rightTurn()
{

}

void Navigation::leftTurn()
{

}

void Navigation::uTurn()
{

}