#include "TouchscreenCpp.hpp"


TouchscreenCpp::TouchscreenCpp(std::string fileName, Data& data)
{
    //Gem filnavn i variabel
    fileName_ = fileName;
    //
    dataFile_.open(fileName_, std::fstream::out | std::fstream::trunc);
    dataFile_ << "mode init: 1\ndist init: 2\nlinetype init: 3\nnextmove init: 4\n";
    dataFile_.close();

    
    lineList.push_back(data.getMode());
    lineList.push_back(data.getDist());
    lineList.push_back(data.getLineType());
    lineList.push_back(data.getNextMove());
}

TouchscreenCpp::~TouchscreenCpp()
{
    //std::remove(fileName_.c_str());
}

void TouchscreenCpp::updateData()
{
    dataFile_.open(fileName_, std::fstream::in); //Åbn fil
    dataFile_.seekg (0, std::ios::beg); //Ryk filepointer til start
    std::string temp; //temp variabel til at gemme streng

    for (auto i : lineList) //Loop gennem de 4 tilknyttede elementer i data klassen.
    {
        std::getline(dataFile_, temp); //Gem linjens tekst i temp strengen
        *i = temp; //Skriv linjen til data klassens tilsvarende element
    }
    dataFile_.close();
}


void TouchscreenCpp::updateScreen()
{
    dataFile_.open(fileName_, std::fstream::out | std::fstream::trunc); //Åbn og clear fil
    dataFile_.seekg (0, std::ios::beg); //Ryk filepointer til start
    for (auto i : lineList) //Loop gennem de 4 tilknyttede elementer i data klassen.
    {   
        dataFile_ << *i << std::endl;
    }
    dataFile_.close();
}
