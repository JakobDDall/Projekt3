#include "Navigation.hpp"
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


void Navigation::determineNextMove() //TODO Opdater så den passer på alle linjetyper
{   
    if(*data_.getCurrentMove() == TYPE_STRAIGHT)
    
    
    *data_.getCurrentMove();




    
    
    // switch på current move


    // hvis current move er stop

    // gør noget stop halløj



    // hvis current move er straight

    // check linjetype
    // sæt sæt nextmove

    // hvis current move er "turningRight"

    // hvis vi skal stoppe med at dreje
    // stop med at dreje

    // hvis vi skal blive ved med at dreje
    // ingenting :)
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


void Navigation::rightTurn()
{

}

void Navigation::leftTurn()
{

}

void Navigation::uTurn()
{

}