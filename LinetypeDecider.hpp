#pragma once
#include "Data.hpp"

class LinetypeDecider
{

public:
    LinetypeDecider(/* args */);
    ~LinetypeDecider();


    void updateData(Data& data);

private:
    void determineLinetype();
};
