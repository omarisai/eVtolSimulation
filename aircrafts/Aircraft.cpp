/**
 * @brief Implementation of the Aircraft class methods,
 *        constructors, and destructor.
 * 
 */

#include "Aircraft.h"

Aircraft::Aircraft(AircraftCompany eCompany)
    : mkpoAircraftType(&AircraftType::mskoAircraftTypes[(size_t)eCompany])
{
    // Nothing to do here.
}
