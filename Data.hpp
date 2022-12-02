#pragma once
#include <stdint.h>
#include <string>

// LineBot v 1.0
// Data-class

// Indeholder al systemets data, og get/set funktioner hertil. Fungerer som bindeled mellem forskellige klasser.


class Data
{
public:
    std::string* getModeP();
    std::string* getDistP();
    std::string* getSensorDataP();
    std::string* getLineTypeP();
    std::string* getNextMoveP();

    void setMode(std::string mode);
    void setDist(std::string dist);
    void setSensorData(std::string sensorData);
    void setLineType(std::string type);
    void setNextMove(std::string move);

    void addSensorData(std::string data);

    //Kan gøres:
    //Implementer sensordata som gennemsnit af sidste x elementer.
    //Indsæt modtaget data i circular list
    //Beregn gennemsnit af listens medlemmer
    //Afrund til nærmeste heltal
    //Indsæt som værdien i sensorData_
private:
    std::string mode_;
    std::string dist_;
    std::string sensorData_;
    std::string lineType_;
    std::string nextMove_;
    const int N_OF_SENSORS = 8;

};




