/**
 * @brief Implentation of the Event class.
 * 
 */

#include "Event.h"
#include "aircrafts/Aircraft.h"

namespace SimpleWorld
{
    /*static*/ uint32_t Event::muNextId;

    Event::Event(AircraftEvent eType, Aircraft* poAircraft, float fTime)
        : meType(eType),
        mpoAircraft(poAircraft),
        mfTime(fTime),
        muId(muNextId++)
    {
        // Nothing to do here.
    }

    bool Event::operator<(const Event& other) const
    {
        // Less priority if the time is greater or if the time is the same and the Id is greater.
        return this->mfTime > other.mfTime || (this->mfTime == other.mfTime && this->muId > other.muId);
    }

} // namespace SimpleWorld
