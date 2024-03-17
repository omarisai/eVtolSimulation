#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_

#include "AircraftType.h"

#include <cstdint>

using namespace std;
class Charger;

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
        // The battery is empty.
        Empty,
        // The battery is charging.
        Charging,
        // The battery is full.
        Full,
        // The battery is discharging (flying).
        Discharging,
    };

    /********** Constructors **********/

    /**
     * @brief Construct a new Aircraft object
     * 
     * @param eCompany              The aircraft company.
     */
    Aircraft(AircraftCompany eCompany);

    /********** Destructor **********/

    /**
     * @brief Destroy the Aircraft object.
     * 
     */
    virtual ~Aircraft() {}


    /********** Properties **********/

    /**
     * @brief Gets if the aircraft is charging.
     * 
     * @return If the aircraft is charging.
     */
    inline bool IsCharging() const { return meBatteryState == BatteryState::Charging; }

    /**
     * @brief Gets the current charger attached to the aircraft.
     * 
     * @return The charger attached to the aircraft. 
     */
    inline Charger* GetCharger() const { return mpoCharger; }

    /**
     * @brief Gets the aircraft Id.
     * 
     * @return The aircraft Id.
     */
    inline uint8_t GetId() const { return muiAircraftId; }


    /********** Methods **********/

    /**
     * @brief Gets the aircraft name composed of the company name and the Id.
     * 
     * @return The aircraft name.
     */
    string GetName() const;

    /**
     * @brief Take off the aircraft.
     * 
     * @return The time the aircraft will be flying in hours.
     */
    float TakeOff();
    
    /**
     * @brief Land the aircraft indefinitely.
     * 
     */
    void Land();

    /**
     * @brief Charge the aircraft.
     * 
     * @param poCharger     The charger to use to charge the aircraft.
     * 
     * @return The time it takes to charge the aircraft in hours.
     */
    float ChargeAircraft(Charger* poCharger);

    /**
     * @brief Stop charging the aircraft and return the charger.
     * 
     * @return The charger that was charging the aircraft.
     */
    Charger* StopCharging();

private:
    AircraftType* mpoAircraftType;
    Charger* mpoCharger;
    BatteryState meBatteryState;
    uint8_t muiAircraftId;
};

#endif // _AIRCRAFT_H_
