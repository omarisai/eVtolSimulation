#ifndef _AIRCRAFTEVENTS_H_
#define _AIRCRAFTEVENTS_H_

namespace SimpleWorld
{
    /**
     * @brief The type of event that can happen in the world and will be
     *        scheduled to be processed in the future.
     * 
     */
    enum class AircraftEvent
    {
        // The aircraft has to take off.
        TakeOff,
        // The aircraft has to land.
        Land,
        // The aircraft has to start charging.
        Charge,
        // The aircraft has to stop charging.
        StopCharge,
    };
}

#endif // _AIRCRAFTEVENTS_H_
