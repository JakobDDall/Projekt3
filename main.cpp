
#include "Data.hpp"
#include <iostream>
#include "LinetypeDecider.hpp"
#include "HandlerAppIF.hpp"

int main()
{
    {
        LinetypeDecider l;
        Data data;
        HandlerAppIF h;
        data.setDist(500);
        data.setLineType('l');
        data.setMode('a');
        data.setNextMove('r');
        data.setSensorData(0b00000101);


        std::cout << "Dist: " << data.getDist() << std::endl;
        std::cout << "Line type: " << data.getLineType() << std::endl;
        std::cout << "Mode: " << data.getMode() << std::endl;
        std::cout << "Move: " << data.getNextMove() << std::endl;
        std::cout << "Sensordata: " << data.getSensorData() << std::endl;

        l.updateData(data);
        h.updateData(data);

        std::cout << "New line type: " << data.getLineType() << std::endl;
        std::cout << "New distance: " << data.getDist() << std::endl;
        std::cout << "New sensordata: " << data.getSensorData() << std::endl;
    }

    return 0;

}