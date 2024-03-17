/**
 * @brief Implementation of the SimulationWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "SimulationWorld.h"

#include <algorithm>

using namespace std;


SimulationWorld::SimulationWorld(uint8_t uiMaxAircrafts, uint8_t uiMaxChargers)
    : muiMaxAircrafts(uiMaxAircrafts), muiMaxChargers(uiMaxChargers)
{
    // Reserve memory for the aircrafts and chargers vectors.
    moAircrafts.reserve(muiMaxAircrafts);
    moChargers.reserve(muiMaxChargers);
}

SimulationWorld::~SimulationWorld()
{
    // Clear the aircrafts and chargers vectors.
    moAircrafts.clear();
    moChargers.clear();
}

bool SimulationWorld::AddAircraft(Aircraft* oAircraft)
{
    // Check if there is space for the aircraft.
    if (moAircrafts.size() < muiMaxAircrafts)
    {
        // Add the aircraft to the world.
        moAircrafts.push_back(oAircraft);
        return true;
    }

    // TODO: Throw an exception if there is no space for the aircraft.
    return false;
}

bool SimulationWorld::AddCharger(Charger* oCharger)
{
    // Check if there is space for the charger.
    if (moChargers.size() < muiMaxChargers)
    {
        // Add the charger to the world.
        moChargers.push_back(oCharger);
        return true;
    }

    // TODO: Throw an exception if there is no space for the charger.
    return false;
}
