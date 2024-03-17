#ifndef _EVENT_H_
#define _EVENT_H_

#include "AircraftEvents.h"
#include "aircrafts/Aircraft.h"

#include <cstdint>

namespace SimpleWorld
{
    /**
     * @brief An event that can happen in the SimpleWorld.
     *
     */
    class Event
    {
        /*********** Constructor ***********/
    public:

        /**
         * @brief Construct a new Event object.
         * 
         * @param eType         The type of event.
         * @param poAircraft    The aircraft involved in the event.
         * @param fTime         The time when the event will happen.
         */
        Event(AircraftEvent eType, Aircraft* poAircraft, float fTime);

        /*********** Operators ***********/

        /**
         * @brief Compare two events by their time and Id.
         * 
         * @param other     The other event to compare.
         * @return If this event happens before the other.
         */
        bool operator<(const Event& other) const;

        /*********** Properties ***********/

        /**
         * @brief Gets the time when the event will happen.
         * 
         * @return The time when the event will happen.
         */
        inline float GetTime() const { return mfTime; }

        /**
         * @brief Gets the type of event.
         * 
         * @return The type of event.
         */
        inline AircraftEvent GetType() const { return meType; }

        /**
         * @brief Gets the aircraft involved in the event.
         * 
         * @return The aircraft involved in the event.
         */
        inline Aircraft* GetAircraft() const { return mpoAircraft; }

    private:
        AircraftEvent meType;
        Aircraft* mpoAircraft;
        float mfTime;
        uint32_t muId;
        static uint32_t muNextId;
    };

} // namespace SimpleWorld

#endif // _EVENT_H_
