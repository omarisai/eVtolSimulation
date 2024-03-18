/**
 * @brief Implementation of the SimulationWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "SimulationWorld.h"

#include <algorithm>
#include <iostream>

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

void SimulationWorld::PrintStatistics() const
{
    // Print the maximum number of aircrafts and chargers.
    cout << endl;
    cout << "===============================================" << endl;
    cout << " Simulation statistics per aircraft type" << endl;
    cout << "===============================================" << endl << endl;
    cout << "Total number of aircrafts types: " << to_string((int)AircraftCompany::TotalCompanies) << endl;
    cout << "Total number of aircrafts: " << to_string(moAircrafts.size()) << endl;
    cout << "Total number of chargers: " << to_string(moChargers.size()) << endl;
    cout << endl;

    // Iterate the aircraft types.
    for (int i = 0; i < static_cast<int>(AircraftCompany::TotalCompanies); i++)
    {
        // Get the aircraft type.
        AircraftCompany eCompany = static_cast<AircraftCompany>(i);
        AircraftType* poAircraftType = AircraftType::GetAircraftType(eCompany);

        // Print the statistics for the aircraft type.
        cout << "Aircraft type: " << poAircraftType->CompanyName() << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Total number of aircrafts: " << to_string(poAircraftType->TotalAircrafts()) << endl;
        cout << "Passenger capacity per aircraft: " << to_string(poAircraftType->GetPassengers()) << " passengers" << endl;
        cout << "Total number of flights: " << to_string(poAircraftType->TotalFlights()) << endl;
        cout << "Total number of miles: " << to_string(poAircraftType->TotalNumberOfMiles()) << endl;
        cout << "Total number of passengers: " << to_string(poAircraftType->TotalNumberOfPassengers()) << endl;
        cout << "Total number of charge sessions: " << to_string(poAircraftType->TotalChargeSessions()) << endl;
        cout << endl;
        cout << "Average flight time per flight: " << to_string(poAircraftType->AverageFlightTimePerFlight()) << " hours" << endl;
        cout << "Average distance travelled per flight: " << to_string(poAircraftType->AverageDistanceTravelledPerFlight()) << " miles" << endl;
        cout << "Average time charging per charge session: " << to_string(poAircraftType->AverageTimeChargingPerChargeSession()) << " hours" << endl;
        cout << "Total number of faults: " << to_string(poAircraftType->TotalNumberOfFaults()) << endl;
        cout << "Total number of passenger miles: " << to_string(poAircraftType->TotalNumberOfPassengerMiles()) << endl;
        cout << endl;
    }

    cout << "===============================================" << endl << endl;
}