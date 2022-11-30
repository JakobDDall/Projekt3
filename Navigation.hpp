#pragma once
#include "Data.hpp"
#include "LinetypeDecider.hpp"
#include "HandlerAppIF.hpp"
#include "TouchscreenCpp.hpp"

class Navigation
{

public:
    Navigation(/* args */);
    ~Navigation();
    void startMainLoop();
    void determineNextMove();
    

private:
    void printAllData();
    void determineSimple();
    void rightTurn();
    void leftTurn();
    void uTurn();
    Data data_;
    HandlerAppIF* handlerAppIF_;
    LinetypeDecider* lineDecider_;
    TouchscreenCpp* touchscreen_;
};


