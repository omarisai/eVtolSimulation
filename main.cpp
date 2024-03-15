/**
 * @brief Runs a simulation world and prints the resulting statistics.
 * 
 */

#include <iostream>

#include "worlds/SimulationWorld.h"
#include "worlds/SimpleWorld.h"

using namespace std;

int main()
{
    const uint8_t kuiAircraftsCount = 20;
    const uint8_t kuiChargersCount = 3;
    const uint8_t kuiSimulationHours = 3;

    // Create a simulation world with 10 aircrafts and 5 chargers.
    SimulationWorld* poWorld = new SimpleWorld(kuiAircraftsCount, kuiChargersCount);

    // Run the simulation for 3 hours.
    poWorld->RunSimulation(kuiSimulationHours);

    // Print the statistics.
    poWorld->PrintStatistics();

    // Destroy the world.
    delete poWorld;

    return 0;
}
