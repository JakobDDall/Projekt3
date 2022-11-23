#include "Navigation.hpp"

Navigation::Navigation(/* args */)
{
}

Navigation::~Navigation()
{
}


void Navigation::startMainLoop()
{
    data_.setMode('s'); //Start i stop mode
    while(data_.getMode() == 's')
    {
        //Læs fra user input
    }

    while(1)
    {
        handlerAppIF_.updateData(data_);
        lineDecider_.updateData(data_);
        //Skærm opdater data
        determineNextMove();
        //Send data til skærm
        handlerAppIF_.sendCmd(data_);
    }
}


void Navigation::determineNextMove() //TODO Opdater så den passer på alle linjetyper
{
    char lineType = data_.getLineType();
    if(lineType == 'r')
    {
        data_.setNextMove('r');
    }
    else if(lineType == 'd')
    {
        data_.setNextMove('d');
    }
    else if(lineType == 'l')
    {
        data_.setNextMove('l');
    }
}
