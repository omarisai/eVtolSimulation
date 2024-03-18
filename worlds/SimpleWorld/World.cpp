/**
 * @brief Implementation of the SimpleWorld class methods,
 *        constructors, and destructor.
 * 
 */

#include "World.h"
#include "AircraftEvents.h"
#include "Event.h"
#include "aircrafts/Aircraft.h"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <ctime>
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

        cout << "Aircrafts added to the world:" << endl;

        // Set the random seed for the aircrafts creation.
        //srand(static_cast<unsigned int>(time(0)));

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

        // Print the aircrafts added to the world in groups per type.
        for (uint8_t i = 0; i < static_cast<uint8_t>(AircraftCompany::TotalCompanies); i++)
        {
            // Get the pointer to the aircraft type.
            AircraftType* poAircraftType = AircraftType::GetAircraftType(static_cast<AircraftCompany>(i));

            // Print the company name and the number of aircrafts of that type.
            cout << poAircraftType->CompanyName() << ": " << to_string(poAircraftType->TotalAircrafts()) << endl;

            // Print the aircrafts of that type.
            for (Aircraft* poAircraft : GetAircrafts())
            {
                if (poAircraft->GetAircraftType() == poAircraftType)
                {
                    cout << " " << poAircraft->GetName();
                }
            }

            cout << endl;
        }

        cout << endl << endl << "Chargers added to the world:" << endl;

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

        // Create the events for the aircrafts depending on its current state.
        for (Aircraft* poAircraft : GetAircrafts())
        {
            // Check if the aircraft has full battery charge.
            if (poAircraft->GetBatteryCharge() == poAircraft->GetAircraftType()->GetBatteryCapacity())
            {
                // Schedule a event for the aircraft to take off.
                ScheduleEvent(0, poAircraft, AircraftEvent::TakeOff);
            }
            else
            {
                // Schedule a event for the aircraft to charge.
                ScheduleEvent(0, poAircraft, AircraftEvent::Charge);
            }
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

        // Free the charging queue.
        while (moAircraftsQueue.size() > 0)
        {
            // Get the first aircraft in the queue.
            Aircraft* poAircraft = moAircraftsQueue.front();
            moAircraftsQueue.pop();

            // Print that the aircraft is not waiting to be charged anymore.
            cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
                << " is not waiting for a free charger anymore." << endl;
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

    bool World::ChargeAircraft(Aircraft* poAircraft, Charger* poCharger)
    {
        // Get the time it takes to fully charge the aircraft in hours.
        float fTimeToCharge = poAircraft->GetTimeToFullCharge();

        // Schedule the StopCharge event to happen when the aircraft
        // stops charging, and get the real charging time in case the
        // simulation time ends sooner.
        fTimeToCharge = ScheduleEvent(fTimeToCharge, poAircraft, AircraftEvent::StopCharge);

        // Abort charging if the simulation already ended.
        if (fTimeToCharge == 0)
        {
            return false;
        }

        // Get the charging rate of the aircraft.
        float fChargingRate = poAircraft->GetAircraftType()->GetBatteryCapacity() / poAircraft->GetAircraftType()->GetTimeToCharge();

        // Get the energy to charge the aircraft without exceeding the battery capacity.
        float fEnergy =  min(fTimeToCharge * fChargingRate, poAircraft->GetAircraftType()->GetBatteryCapacity() - poAircraft->GetBatteryCharge());

        // Charge the aircraft.
        float fTime = poAircraft->ChargeAircraft(poCharger, fEnergy);

        // Print that the aircraft is charging.
        cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
            << " is charging at " << poCharger->GetName()
            << " for " << fTime << " hours." << endl;

        return true;
    }

    void World::ProcessEvent(Event* poEvent)
    {
        // Get the aircraft involved in the event.
        Aircraft* poAircraft = poEvent->GetAircraft();

        // Execute the event.
        switch (poEvent->GetType())
        {
            case AircraftEvent::TakeOff:
            {
                // Get the flying time for the aircraft.
                float fFlyingTime = poAircraft->GetCurrentRange() / poAircraft->GetAircraftType()->GetCruiseSpeed();

                // Schedule the land event to happen when the aircraft will be out of battery,
                // and get the real flying time in case the simulation time ends sooner.
                fFlyingTime = ScheduleEvent(fFlyingTime, poAircraft, AircraftEvent::Land, true);

                // Get the distance the aircraft will fly in the flying time without exceeding the current range.
                float fDistance = min(fFlyingTime * poAircraft->GetAircraftType()->GetCruiseSpeed(), poAircraft->GetCurrentRange());

                // Fly the aircraft.
                poAircraft->Fly(fDistance);

                // Print that the aircraft is taking off.
                cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
                    << " is taking off and will fly " << to_string(fDistance) << " miles for "
                    << to_string(fFlyingTime) << " hours." << endl;
            }
            break;

            case AircraftEvent::Land:
            {
                // Land the aircraft.
                poAircraft->Land();

                // Schedule the charge event to inmediately charge the aircraft.
                ScheduleEvent(0, poAircraft, AircraftEvent::Charge);

                // Print that the aircraft had landed.
                cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
                    << " has landed." << endl;
            }
            break;

            case AircraftEvent::Charge:
            {
                // Find an available charger for the aircraft or wait in the queue.
                if (!AssignCharger(poAircraft))
                {
                    // If the aircraft is not charging, add the aircraft to the queue.
                    moAircraftsQueue.push(poAircraft);

                    // Print that the aircraft is waiting to be charged.
                    cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
                        << " is waiting for a free charger." << endl;
                }
            }
            break;

            case AircraftEvent::StopCharge:
            {
                // Stop charging the aircraft and get the newly available charger.
                Charger* poCharger = poAircraft->StopCharging();

                // Schedule the take off event to inmediately take off the aircraft.
                ScheduleEvent(0, poAircraft, AircraftEvent::TakeOff);

                // Print that the aircraft is fully charged.
                cout << GetTimeString() << ": Aircraft " << poAircraft->GetName()
                    << " has been charged up to " << poAircraft->GetBatteryCharge()
                    << " kWh, and has been disconnected from " << poCharger->GetName() << "." << endl;

                // Check if there are aircrafts waiting to be charged.
                if (moAircraftsQueue.size() > 0)
                {
                    // Get the first aircraft in the queue.
                    Aircraft* poAircraft = moAircraftsQueue.front();

                    // Try to charge the aircraft.
                    if (ChargeAircraft(poAircraft, poCharger))
                    {
                        // Remove the aircraft from the queue.
                        moAircraftsQueue.pop();
                    }
                }
            }
            break;
        }
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
