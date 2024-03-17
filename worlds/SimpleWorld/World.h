#ifndef _SIMPLE_WORLD_H_
#define _SIMPLE_WORLD_H_

#include "worlds/SimulationWorld.h"
#include "aircrafts/Aircraft.h"
#include "AircraftEvents.h"
#include "Event.h"

#include <queue>

using namespace std;

namespace SimpleWorld
{
    /**
     * @brief This class represents a simple world where the only dimension is
     *        the time, with aircrafts that can travel without changing their
     *        position and chargers located in the only position. 
     * 
     */
    class World : public SimulationWorld
    {
    public:
        /********** Constructors **********/

        /**
         * @brief Construct a new Simple World object.
         * 
         * @param uiMaxAircrafts     The maximum number of aircrafts that can be
         *                           in the world at the same time.
         * @param uiMaxChargers      The maximum number of chargers that can be
         *                           in the world at the same time.
         */
        World(uint8_t uiMaxAircrafts, uint8_t uiMaxChargers);

        /********** Destructor **********/

        /**
         * @brief Destroy the Simple World object.
         * 
         */
        ~World();

        /********** Methods **********/

        /**
         * @brief Run the simulation for a given number of hours using the Event-Driven method.
         * 
         * @param uiHours       The number of hours to run the simulation.
         */
        void RunSimulation(uint16_t uiHours) override;

        /**
         * @brief Print the statistics of the world.
         * 
         */
        void PrintStatistics() const override;

    private:
        /**
         * @brief Schedule an event.
         * 
         * @param fTime             The time when the event will happen from now.
         * @param poAircraft        The aircraft involved in the event.
         * @param peAircraftEvent   The type of event that will happen.
         * @param force             If the event must happen to get the aircraft into a state that makes sense.
         * 
         * @return The real time when the event will happen from now.
         */
        float ScheduleEvent(float fTime, Aircraft* poAircraft, AircraftEvent peAircraftEvent, bool force = false);

        /**
         * @brief Tries to assign a charger to an aircraft.
         * 
         * @param poAircraft  The aircraft to charge.
         * 
         * @return If the aircraft was assigned to a charger.
         */
        bool AssignCharger(Aircraft* poAircraft);

        /**
         * @brief Charge an aircraft using a charger.
         *
         * @param poAircraft    The aircraft to charge.
         * @param poCharger     The charger to use.
         */
        void ChargeAircraft(Aircraft* poAircraft, Charger* poCharger);

        /**
         * @brief Process an event.
         * 
         * @param poEvent     The event to process.
         */
        void ProcessEvent(Event* poEvent);

        /**
         * @brief Get the current time as a string.
         * 
         * @return The current time as a string.
         */
        string GetTimeString() const;

        /********** Variables **********/
        float mfCurrentTime; // The current time in the world.
        priority_queue<Event> moEvents; // The events that will happen in the world.
        queue<Aircraft*> moAircraftsQueue; // The queue of aircrafts waiting to be charged.
    };
}

#endif // _SIMPLE_WORLD_H_
