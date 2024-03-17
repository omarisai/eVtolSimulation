/**
 * @brief Implementation of the SimpleWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "World.h"
#include "AircraftEvents.h"
#include "Event.h"
#include "aircrafts/Aircraft.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

namespace SimpleWorld
{ 
    /**
     * @brief Construct a new Simple World object.
     * 
     * @param uiAircrafts        The maximum number of aircrafts that can be
     *                           in the world at the same time.
     * @param uiChargers         The maximum number of chargers that can be
     *                           in the world at the same time.
     */
    World::World(uint8_t uiAircrafts, uint8_t uiChargers)
        : SimulationWorld(uiAircrafts, uiChargers),
        mfCurrentTime(0)
    {
        cout << "Creating a simple world with " << to_string(uiAircrafts) << " aircrafts and "
            << to_string(uiChargers) << " chargers." << endl << endl;

        cout << "Aircrafts added to the world:";

        // TODO: Use a random seed based on the current time.

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

            // Print that the aircraft was added to the world.
            cout << " " << poAircraft->GetName();
        }

        cout << endl << endl << "Chargers added to the world:";

        // Create the chargers from the start.
        for (uint8_t i = 0; i < uiChargers; i++)
        {
            // Create the charger.
            Charger* poCharger = new Charger();

            // Add the charger to the world.
            AddCharger(poCharger);

            // Print that the charger was added to the world.
            cout << " " << poCharger->GetName();
        }

        cout << endl << endl;
    }

    /**
     * @brief Destroy the Simple World object.
     * 
     */
    World::~World()
    {
        // Destroy the aircrafts.
        for (const Aircraft* poAircraft : GetAircrafts())
        {
            delete poAircraft;
        }

        // Destroy the chargers.
        for (const Charger* poCharger : GetChargers())
        {
            delete poCharger;
        }
    }

    void World::RunSimulation(uint16_t uiHours)
    {
        // Set the simulation time.
        SetSimulationTime(uiHours);

        // Print the number of aircrafts in the world.
        cout << "Number of aircrafts in the world: " << GetAircraftsCount() << endl;

        // Print the number of chargers in the world.
        cout << "Number of chargers in the world: " << GetChargersCount() << endl;

        // Print the number of hours the simulation will run.
        cout << "Running the simulation for " << to_string(uiHours) << " hours." << endl << endl;
        
        // Indicate the start of the simulation events.
        cout << "Simulation events:" << endl;

        // Create the events for the aircrafts.
        for (Aircraft* poAircraft : GetAircrafts())
        {
            // Schedule a event for the aircraft to take off.
            ScheduleEvent(0, poAircraft, AircraftEvent::TakeOff);
        }
        
        // Process the events until reaching the end of the simulation.
        while (moEvents.size() > 0)
        {
            // Get the first event.
            Event oEvent = moEvents.top();
            moEvents.pop();

            // Update the current time.
            mfCurrentTime = oEvent.GetTime();

            // Process the event.
            ProcessEvent(&oEvent);
        }

        // Indicate the end of the simulation events.
        cout << endl << "End of simulation events." << endl << endl;
    }

    float World::ScheduleEvent(float fTime, Aircraft* poAircraft, AircraftEvent peAircraftEvent, bool force)
    {
        // Check if the current time is the end of the simulation and the event is not forced.
        if (mfCurrentTime == GetSimulationTime() && !force)
        {
            return 0;
        }

        // Get the time when the event will happen.
        float fTriggeringTime = fTime + mfCurrentTime;

        // Check if the triggering time does not exceed the simulation time.
        if (fTriggeringTime > GetSimulationTime())
        {
            // Adjust the triggering time to the simulation time.
            fTriggeringTime = GetSimulationTime();
        }

        // Allocate the event.
        Event poEvent(peAircraftEvent, poAircraft, fTriggeringTime);

        // Add the event to the map.
        moEvents.push(poEvent);

        // Return the triggering time.
        return fTriggeringTime - mfCurrentTime;
    }

    bool World::AssignCharger(Aircraft* poAircraft)
    {
        // Find the first available charger.
        for (Charger* poCharger : GetChargers())
        {
            // Check if the charger is not being used.
            if (!poCharger->IsCharging())
            {
                // Charge the aircraft.
                ChargeAircraft(poAircraft, poCharger);
                return true;
            }
        }

        return false;
    }

    void World::ChargeAircraft(Aircraft* poAircraft, Charger* poCharger)
    {
        // Charge the aircraft.
        float fTime = poAircraft->ChargeAircraft(poCharger);

        // Schedule the StopCharge event to happen when the aircraft is fully charged.
        fTime = ScheduleEvent(fTime, poAircraft, AircraftEvent::StopCharge);

        // Print that the aircraft is charging.
        cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
            << " is charging at " << poCharger->GetName()
            << " for " << fTime << " hours." << endl;
    }

    void World::ProcessEvent(Event* poEvent)
    {
        // Execute the event.
        switch (poEvent->GetType())
        {
            case AircraftEvent::TakeOff:
            {
                // Take off the aircraft and get the time it will take to discharge de battery.
                float fTime = poEvent->GetAircraft()->TakeOff();

                // Schedule the land event to happen when the aircraft will be out of battery.
                fTime = ScheduleEvent(fTime, poEvent->GetAircraft(), AircraftEvent::Land, true);

                // Print that the aircraft is taking off.
                cout << GetTimeString() << ": Aircraft " << poEvent->GetAircraft()->GetName()
                    << " is taking off and will fly for " << to_string(fTime) << " hours." << endl;
            }
            break;

            case AircraftEvent::Land:
            {
                // Land the aircraft.
                poEvent->GetAircraft()->Land();

                // Schedule the charge event to inmediately charge the aircraft.
                ScheduleEvent(0, poEvent->GetAircraft(), AircraftEvent::Charge);

                // Print that the aircraft is landing.
                cout << GetTimeString() << ": Aircraft " << poEvent->GetAircraft()->GetName()
                    << " is landing." << endl;
            }
            break;

            case AircraftEvent::Charge:
            {
                // Find an available charger for the aircraft or wait in the queue.
                if (!AssignCharger(poEvent->GetAircraft()))
                {
                    // If the aircraft is not charging, add the aircraft to the queue.
                    moAircraftsQueue.push(poEvent->GetAircraft());

                    // Print that the aircraft is waiting to be charged.
                    cout << GetTimeString() << ": Aircraft " << poEvent->GetAircraft()->GetName()
                        << " is waiting for a free charger." << endl;
                }
            }
            break;

            case AircraftEvent::StopCharge:
            {
                // Stop charging the aircraft and get the newly available charger.
                Charger* poCharger = poEvent->GetAircraft()->StopCharging();

                // Schedule the take off event to inmediately take off the aircraft.
                ScheduleEvent(0, poEvent->GetAircraft(), AircraftEvent::TakeOff);

                // Print that the aircraft is fully charged.
                cout << GetTimeString() << ": Aircraft " << poEvent->GetAircraft()->GetName()
                    << " is fully charged and leaving " << poCharger->GetName() << "." << endl;

                // Check if there are aircrafts waiting to be charged.
                if (moAircraftsQueue.size() > 0)
                {
                    // Get the first aircraft in the queue.
                    Aircraft* poAircraft = moAircraftsQueue.front();
                    moAircraftsQueue.pop();

                    // Charge the aircraft.
                    ChargeAircraft(poAircraft, poCharger);
                }
            }
            break;
        }
    }

    void World::PrintStatistics() const
    {
        // Print the maximum number of aircrafts and chargers.
        cout << "Maximum number of aircrafts: " << GetMaxAircrafts() << endl;
        cout << "Maximum number of chargers: " << GetMaxChargers() << endl;
    }

    string World::GetTimeString() const
    {
        // Convert the current time to a string with 2 decimal positions.
        stringstream oTime;
        oTime << fixed << setprecision(2) << mfCurrentTime;

        // Return the formatted time string.
        return oTime.str();
    }

} // namespace SimpleWorld
