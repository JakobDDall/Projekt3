#pragma once
#include "Data.hpp"
#include "LinetypeDecider.hpp"
#include "HandlerAppIF.hpp"
#include "TouchscreenCpp.hpp"
#include <chrono>
#include <unistd.h>

class Navigation
{

public:
    Navigation(/* args */);
    ~Navigation();
    void startMainLoop();
    void determineNextMove();
    

private:
    void determineSimple();
    void determineAdvanced();
    Data data_;
    HandlerAppIF* handlerAppIF_;
    LinetypeDecider* lineDecider_;
    TouchscreenCpp* touchscreen_;
    bool turning_ = false;
    bool turnDone_ = false;
    bool ihavejustturned = false;
    std::chrono::system_clock::time_point turning_timer_;
    std::string* lastMove_;
    
};


