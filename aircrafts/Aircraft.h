#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_

#include "AircraftType.h"

#include <cstdint>

using namespace std;

/**
 * @brief The Aircraft class. Encapsulates all the common aircraft
 *       properties and methods.
 * 
 *       It represents an aircraft in a simulation world where the
 *       only existing aircrafts are eVTOLs.
 * 
 */
class Aircraft
{
public:
    /********** Types **********/

    /**
     * @brief The aircraft battery state.
     * 
     */
    enum class BatteryState
    {
        Empty,
        Charging,
        Full,
        Discharging,
    };

    /********** Constructors **********/

    /**
     * @brief Construct a new Aircraft object
     * 
     * @param eCompany              The aircraft company.
     */
    Aircraft(AircraftCompany eCompany);


    /********** Methods **********/

    /**
     * @brief Create an aircraft.
     * 
     * @param AircraftType*         The aircraft type.
     * 
     * @return The new created aircraft.
     */
    Aircraft* CreateAircraft(AircraftType* poAircraftType);

    /**
     * @brief Take off the aircraft.
     * 
     * @return The time the aircraft will be flying in hours.
     */
    float TakeOff();
    
    /**
     * @brief Land the aircraft.
     * 
     */
    void Land();

    /**
     * @brief Charge the aircraft.
     * 
     * @return The time it takes to charge the aircraft in hours.
     */
    float ChargeAircraft();

private:
    const AircraftType* mkpoAircraftType;
    BatteryState meBatteryState;
};

#endif // _AIRCRAFT_H_
