/**
 * @brief Implementation of the SimulationWorld class methods, constructors, and destructor.
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
SimulationWorld::SimulationWorld(uint32_t uiMaxAircrafts, uint32_t uiMaxChargers)
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
 * @return true         If the aircraft was added successfully.
 * @return false        If the aircraft was not added.
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
 * @brief Remove an aircraft from the world.
 * 
 * @param oAircraft     The aircraft to remove.
 * @return true         If the aircraft was removed successfully.
 * @return false        If the aircraft was not removed.
 */
bool SimulationWorld::RemoveAircraft(const Aircraft* oAircraft)
{
    // Find the aircraft in the world.
    auto itAircraft = find(moAircrafts.begin(), moAircrafts.end(), oAircraft);

    // Check if the aircraft was found.
    if (itAircraft != moAircrafts.end())
    {
        // Remove the aircraft from the world.
        moAircrafts.erase(itAircraft);
        return true;
    }

    return false;
}

/**
 * @brief Add a charger to the world.
 * 
 * @param oCharger      The charger to add.
 * @return true         If the charger was added successfully.
 * @return false        If the charger was not added.
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

/**
 * @brief Remove a charger from the world.
 * 
 * @param oCharger      The charger to remove.
 * @return true         If the charger was removed successfully.
 * @return false        If the charger was not removed.
 */

bool SimulationWorld::RemoveCharger(const Charger* oCharger)
{
    // Find the charger in the world.
    auto itCharger = find(moChargers.begin(), moChargers.end(), oCharger);

    // Check if the charger was found.
    if (itCharger != moChargers.end())
    {
        // Remove the charger from the world.
        moChargers.erase(itCharger);
        return true;
    }

    return false;
}
