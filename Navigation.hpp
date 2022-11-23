#pragma once
#include "Data.hpp"
#include "LinetypeDecider.hpp"
#include "HandlerAppIF.hpp"

class Navigation
{

public:
    Navigation(/* args */);
    ~Navigation();
    void startMainLoop();
    void determineNextMove();

private:
    Data data_;
    HandlerAppIF handlerAppIF_;
    LinetypeDecider lineDecider_;
    //Implementer touchscreen også
};


