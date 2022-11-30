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


void Navigation::determineNextMove()
{   
    if (*data_.getMode == "Stop") //Hvis stop er valgt, er beslutningen nem
    {
        *data_.getNextMove() = "Stop";
        return;
    }
    else if (*data_.getMode == "Simple")
    {
        determineSimple();
        return;
    }
    else if (*data_.getMode == "Advanced")
    {
        //Kald determine advanced
        return;
    }
}

void Navigation::printAllData()
{
    std::cout << "-------------------- Printing all data entries ----------" << std::endl;
    std::cout << "Dist: " << *data_.getDist() << std::endl;
    std::cout << "Line type: " << *data_.getLineType() << std::endl;
    std::cout << "Mode: " << *data_.getMode() << std::endl;
    std::cout << "Move: " << *data_.getNextMove() << std::endl;
    std::cout << "Sensordata: " << *data_.getSensorData() << std::endl;
}

void Navigation::determineSimple()
{
    std::string linetype = *data_.getLineType();
    std::string nextMove = *data_.getNextMove();
    uint8_t sensorData = std::stoi(*data_.getSensorData());
    if (nextMove == TYPE_STRAIGHT || nextMove == TYPE_STOP) //Hvis vi kører ligeud, eller er standset skal vi blot holde øje med linjetypen.
    {
        if ((linetype == TYPE_4WAY) || (linetype == TYPE_TJUNCTION) || (linetype == TYPE_RIGHT))
        {
            *data_.getNextMove() == TYPE_RIGHT;
        }
        else if ((linetype == TYPE_LEFT))
        {
            *data_.getNextMove() == TYPE_LEFT;
        }
        else if ((linetype == TYPE_STRAIGHT))
        {
            *data_.getNextMove() == TYPE_STRAIGHT;
        }
        else if ((linetype == TYPE_UTURN))
        {
            *data_.getNextMove() == TYPE_UTURN;
        }
        else if ((linetype == TYPE_UNKNOWN))
        {
            *data_.getNextMove() == TYPE_STOP;
        } 
    }
    else if (nextMove == TYPE_RIGHT) //Hvis vi drejer til højre, skal vi vente til vi igen kan se en linje med højre sensor
    {
        if (sensorData & RIGHT)
        {
            *data_.getNextMove() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
    else if (nextMove == TYPE_LEFT) //Hvis vi drejer til vesntre, skal vi vente til vi igen kan se en linje med vesntre sensor
    {
        if (sensorData & LEFT)
        {
            *data_.getNextMove() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
    else if (nextMove == TYPE_UTURN) //Hvis vi laver u vending, skal vi vente til vi igen kan se en linje med front sensor
    {
        if (sensorData & FRONT)
        {
            *data_.getNextMove() == TYPE_STOP; //Når vi igen kan se linjen stopper vi
        }
    }
    
    //Hvis vi er ved at 
    
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