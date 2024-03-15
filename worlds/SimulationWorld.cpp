/**
 * @brief Implementation of the SimulationWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "SimulationWorld.h"

#include <algorithm>

using namespace std;

/**
 * @brief Construct a new Simulation World object.
 * 
 * @param uiMaxAircrafts     The maximum number of aircrafts that can be
 *                           in the world at the same time.
 * @param uiMaxChargers      The maximum number of chargers that can be
 *                           in the world at the same time.
 */
SimulationWorld::SimulationWorld(uint8_t uiMaxAircrafts, uint8_t uiMaxChargers)
    : muiMaxAircrafts(uiMaxAircrafts), muiMaxChargers(uiMaxChargers)
{
    // Reserve memory for the aircrafts and chargers vectors.
    moAircrafts.reserve(muiMaxAircrafts);
    moChargers.reserve(muiMaxChargers);
}

/**
 * @brief Destroy the Simulation World object.
 * 
 */
SimulationWorld::~SimulationWorld()
{
    // Clear the aircrafts and chargers vectors.
    moAircrafts.clear();
    moChargers.clear();
}

/**
 * @brief Add an aircraft to the world.
 * 
 * @param oAircraft     The aircraft to add.
 * 
 * @return If the aircraft was added successfully.
 */
bool SimulationWorld::AddAircraft(const Aircraft* oAircraft)
{
    // Check if there is space for the aircraft.
    if (moAircrafts.size() < muiMaxAircrafts)
    {
        // Add the aircraft to the world.
        moAircrafts.push_back(oAircraft);
        return true;
    }

    return false;
}

/**
 * @brief Add a charger to the world.
 * 
 * @param oCharger      The charger to add.
 * 
 * @return If the charger was added successfully.
 */
bool SimulationWorld::AddCharger(const Charger* oCharger)
{
    // Check if there is space for the charger.
    if (moChargers.size() < muiMaxChargers)
    {
        // Add the charger to the world.
        moChargers.push_back(oCharger);
        return true;
    }

    return false;
}
