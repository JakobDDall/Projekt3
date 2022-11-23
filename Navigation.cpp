#include "Navigation.hpp"

Navigation::Navigation(/* args */)
{
    handlerAppIF_ = new HandlerAppIF(data_);
    lineDecider_ = new LinetypeDecider(data_);
    touchscreen_ = new TouchscreenCpp("test.txt", data_);


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
    printAllData();
    touchscreen_->updateData(); //Skal ske først! læser brugerinput. Overskriver desuden data... :-)
    handlerAppIF_->updateData(); //Hent ny data fra PSoC
    lineDecider_->updateData(); //del 1 af: Behandl data fra PSoC
    determineNextMove();        //del 2 af: Behandl data fra PSoC
    touchscreen_->updateScreen();
    handlerAppIF_->sendCmd();
    printAllData();
}


void Navigation::determineNextMove() //TODO Opdater så den passer på alle linjetyper
{
    std::string lineType = *data_.getLineType();
    if(lineType == "r")
    {
        data_.setNextMove("r");
    }
    else if(lineType == "d")
    {
        data_.setNextMove("d");
    }
    else if(lineType == "l")
    {
        data_.setNextMove("l");
    }
    else
    {
        data_.setNextMove("move determined!");
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
