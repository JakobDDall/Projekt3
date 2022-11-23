#include "Data.hpp"
#include <iostream>
#include "TouchscreenCpp.hpp"

int main()
{
    // LinetypeDecider l;
    Data data;
    data.setDist("500");
    data.setLineType("Type 2");
    data.setMode("Mode 2");
    data.setNextMove("Move 5");
    data.setSensorDat(0b00000101);

    std::cout << "Mode: " << *data.getMode() << std::endl;
    std::cout << "Dist: " << *data.getDist() << std::endl;
    std::cout << "Line type: " << *data.getLineType() << std::endl;
    std::cout << "Move: " << *data.getNextMove() << std::endl;

    std::cout << "Sensordata: " << *data.getSensorData() << std::endl << std::endl << std::endl;

    TouchscreenCpp screen("data.txt", data);
    screen.updateData();
    screen.updateScreen();
    

    std::cout << "Mode: " << *data.getMode() << std::endl;
    std::cout << "Dist: " << *data.getDist() << std::endl;
    std::cout << "Line type: " << *data.getLineType() << std::endl;
    std::cout << "Move: " << *data.getNextMove() << std::endl;
    
}