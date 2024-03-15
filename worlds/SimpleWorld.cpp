/**
 * @brief Implementation of the SimpleWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "SimpleWorld.h"
#include "aircrafts/Aircraft.h"

#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

/**
 * @brief Construct a new Simple World object.
 * 
 * @param uiAircrafts        The maximum number of aircrafts that can be
 *                           in the world at the same time.
 * @param uiChargers         The maximum number of chargers that can be
 *                           in the world at the same time.
 */
SimpleWorld::SimpleWorld(uint8_t uiAircrafts, uint8_t uiChargers)
    : SimulationWorld(uiAircrafts, uiChargers)
{
    // Create the aircrafts from the start, choosing a random
    // company for each one.
    for (uint8_t i = 0; i < uiAircrafts; i++)
    {
        // Choose a random company for the aircraft.
        int iCompany = rand() % static_cast<int>(AircraftCompany::TotalCompanies);
        AircraftCompany eCompany = static_cast<AircraftCompany>(iCompany);
        
        // Create the aircraft.
        Aircraft* poAircraft = new Aircraft(eCompany);

        // Add the aircraft to the world.
        AddAircraft(poAircraft);
    }

    // Create the chargers from the start.
    for (uint8_t i = 0; i < uiChargers; i++)
    {
        // Create the charger.
        Charger* poCharger = new Charger();

        // Add the charger to the world.
        AddCharger(poCharger);
    }
}

/**
 * @brief Destroy the Simple World object.
 * 
 */
SimpleWorld::~SimpleWorld()
{
    // Destroy the aircrafts.
    for (const Aircraft* poAircraft : moAircrafts)
    {
        delete poAircraft;
    }

    // Destroy the chargers.
    for (const Charger* poCharger : moChargers)
    {
        delete poCharger;
    }
}

void SimpleWorld::RunSimulation(uint16_t uiHours)
{
    // Print the number of aircrafts in the world.
    cout << "Number of aircrafts in the world: " << GetAircraftsCount() << endl;

    // Print the number of chargers in the world.
    cout << "Number of chargers in the world: " << GetChargersCount() << endl;

    // Print the number of hours the simulation will run.
    cout << "Number of hours the simulation will run: " << uiHours << endl;

    // Create the map that will store the simulation events.
    map<float, Aircraft*> moEvents;
}

void SimpleWorld::PrintStatistics() const
{
    // Create the world.
    SimpleWorld oWorld(10, 5);

    // Print the maximum number of aircrafts and chargers.
    cout << "Maximum number of aircrafts: " << oWorld.GetMaxAircrafts() << endl;
    cout << "Maximum number of chargers: " << oWorld.GetMaxChargers() << endl;
}
