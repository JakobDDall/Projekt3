#pragma once
#include "Data.hpp"
#include <string>
#include <iostream>

class LinetypeDecider
{

public:
    LinetypeDecider(Data& data);
    ~LinetypeDecider();
    

    void updateData();

private:
    std::string* sensorDataPointer_;
    std::string* linetypePointer_;
    std::string* currentMovePointer_;
    std::string* currentMode_;
    void determineLinetype();
};
