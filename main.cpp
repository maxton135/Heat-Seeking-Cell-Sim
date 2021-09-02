#include <iostream>
#include "Simulation.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    
    Simulation sim;

    while (sim.running())
    {
        sim.update();
        sim.render();
    }

    return 0;
}