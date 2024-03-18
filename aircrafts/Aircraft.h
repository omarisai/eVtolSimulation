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
    inline bool IsCharging() const { return mpoCharger != nullptr; }

    /**
     * @brief Gets if the aircraft is flying.
     * 
     * @return If the aircraft is flying.
     */
    inline bool IsFlying() const { return mbIsFlying; }

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

    /**
     * @brief Gets the aircraft type.
     * 
     * @return The aircraft type.
     */
    inline AircraftType* GetAircraftType() const { return mpoAircraftType; }

    /**
     * @brief Gets the battery charge.
     * 
     * @return The battery charge.
     */
    inline float GetBatteryCharge() const { return mfBatteryCharge; }


    /********** Methods **********/

    /**
     * @brief Gets the aircraft name composed of the company name and the Id.
     * 
     * @return The aircraft name.
     */
    string GetName() const;

    /**
     * @brief Gets the current range of the aircraft in miles.
     * 
     * @return The current range of the aircraft in miles.
     */
    float GetCurrentRange() const;

    /**
     * @brief Gets the time it takes to charge the aircraft to full from the current charge.
     * 
     * @return The time it takes to charge the aircraft to full in hours.
     */
    float GetTimeToFullCharge() const;

    /**
    * @brief Fly the aircraft for a given distance.
    * 
    * @param fDistance     The distance to fly in miles.
    * 
    * @return The time the aircraft will be flying in hours.
    * 
    * @throw std::runtime_error if there is not enough battery charge to fly the distance,
    *        if the aircraft is already flying, if the distance is negative, or if the aircraft is charging.
    */
    float Fly(float fDistance);
    
    /**
     * @brief Land the aircraft indefinitely.
     * 
     */
    void Land();

    /**
     * @brief Charge the aircraft.
     * 
     * @param poCharger     The charger to use to charge the aircraft.
     * @param fEnergy       The energy to charge the aircraft in kWh.
     * 
     * @return The time it takes to charge the aircraft in hours.
     * 
     * @throw std::runtime_error if the aircraft is already charging or is flying,
     *        if the energy is negative or exceeds the remaining battery capacity.
     */
    float ChargeAircraft(Charger* poCharger, float fEnergy);

    /**
     * @brief Stop charging the aircraft and return the charger.
     * 
     * @return The charger that was charging the aircraft.
     * 
     * @throw std::runtime_error if the aircraft is not charging.
     */
    Charger* StopCharging();

private:
    AircraftType* mpoAircraftType;
    Charger* mpoCharger;
    bool mbIsFlying;
    float mfBatteryCharge;
    uint8_t muiAircraftId;
};

#endif // _AIRCRAFT_H_
