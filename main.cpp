/**
 * @brief Runs a simulation world and prints the resulting statistics.
 * 
 */

#include "worlds/SimpleWorld/World.h"

#include <iostream>

using namespace std;
using namespace SimpleWorld;

int main()
{
    const uint8_t kuiAircraftsCount = 20;
    const uint8_t kuiChargersCount = 3;
    const uint8_t kuiSimulationHours = 3;

    // Create a simulation world with 10 aircrafts and 5 chargers.
    World poWorld(kuiAircraftsCount, kuiChargersCount);

    // Run the simulation for 3 hours.
    poWorld.RunSimulation(kuiSimulationHours);

    // Print the statistics.
    poWorld.PrintStatistics();

    return 0;
}
