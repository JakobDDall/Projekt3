
#include "Data.hpp"
#include "LinetypeDecider.hpp"
#include "HandlerAppIF.hpp"
#include "TouchscreenCpp.hpp"
#include "Navigation.hpp"



#include <iostream>
int main()
{
    Navigation nav;

    //Main loop foregår i Navigation klassen
    nav.startMainLoop();
    
    return 0;
}