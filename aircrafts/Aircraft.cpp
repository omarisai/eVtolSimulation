/**
 * @brief Implementation of the Aircraft class methods,
 *        constructors, and destructor.
 * 
 */

#include "Aircraft.h"
#include "worlds/Charger.h"

Aircraft::Aircraft(AircraftCompany eCompany)
    : mpoAircraftType(&AircraftType::msoAircraftTypes[(size_t)eCompany]),
      mpoCharger(nullptr),
      meBatteryState(BatteryState::Full),
      muiAircraftId(mpoAircraftType->muiTotalAircrafts++)
{
    // Nothing to do here.
}

string Aircraft::GetName() const
{
    return mpoAircraftType->CompanyName() + "-" + to_string(muiAircraftId);
}

float Aircraft::TakeOff()
{
    // The aircraft changes its state to discharging.
    meBatteryState = BatteryState::Discharging;

    // Get the distance the aircraft can fly.
    float fDistance = mpoAircraftType->GetBatteryCapacity() / mpoAircraftType->GetEnergyUse();

    // The time the aircraft will be flying in hours.
    return fDistance / mpoAircraftType->GetCruiseSpeed();
}

void Aircraft::Land()
{
    // The aircraft changes its battery state to empty.
    meBatteryState = BatteryState::Empty;
}

float Aircraft::ChargeAircraft(Charger* poCharger)
{
    // The aircraft changes its state to charging.
    meBatteryState = BatteryState::Charging;

    // Charge the aircraft.
    mpoCharger = poCharger;
    mpoCharger->StartCharging();

    // The time it takes to charge the aircraft in hours.
    return mpoAircraftType->GetTimeToCharge();
}

Charger* Aircraft::StopCharging()
{
    // The aircraft changes its state to full.
    meBatteryState = BatteryState::Full;

    // Stop charging the aircraft.
    Charger* poCharger = mpoCharger;
    mpoCharger->StopCharging();
    mpoCharger = nullptr;

    // Return the charger that was charging the aircraft.
    return poCharger;
}
