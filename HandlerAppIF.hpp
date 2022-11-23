#pragma once
#include "Data.hpp"

class HandlerAppIF
{
public:
    HandlerAppIF(int mode, int speed); //Indsæt defaultværdier
    ~HandlerAppIF();
    void updateData(Data& data);
    void sendCmd(Data& data);

private:
    void requestData(Data& data);
    int mode_;
    int speed_;
};

