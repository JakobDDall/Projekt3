#pragma once
#include "Data.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>

class TouchscreenCpp
{
private:
    std::fstream dataFile_;
    std::string fileName_;
    std::list<std::string*> lineList;
public:
    TouchscreenCpp(std::string fileName, Data& data); //Lav filer. Gem lokationer.
    ~TouchscreenCpp(); //Slet filer

    void updateData(); //Opdater data klassen. Læs fra filer og skriv indhold videre
    void updateScreen(); //Opdater hvad der vises på skærm. Læs fra data klasse, skriv til fil.

    void readFromFile();
    void writeToFile();
};
