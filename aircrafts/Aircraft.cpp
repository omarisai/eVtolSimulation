/**
 * @brief Implementation of the Aircraft class methods,
 *        constructors, and destructor.
 * 
 */

#include "Aircraft.h"
#include "worlds/Charger.h"

#include <stdexcept>

Aircraft::Aircraft(AircraftCompany eCompany)
{
    // Throw an exception if the company is invalid.
    if (eCompany >= AircraftCompany::TotalCompanies)
    {
        throw std::runtime_error("Invalid aircraft company.");
    }

    // Set the aircraft type.
    mpoAircraftType = &AircraftType::msoAircraftTypes[(size_t)eCompany];

    // The aircraft is not flying.
    mbIsFlying = false;

    // The aircraft is not charging.
    mpoCharger = nullptr;

    // The battery is fully charged.
    mfBatteryCharge = mpoAircraftType->GetBatteryCapacity();

    // Set the aircraft Id.
    muiAircraftId = mpoAircraftType->muiTotalAircrafts++;
}

string Aircraft::GetName() const
{
    return mpoAircraftType->CompanyName() + "-" + to_string(muiAircraftId);
}

float Aircraft::GetCurrentRange() const
{
    return mfBatteryCharge / mpoAircraftType->GetEnergyUse();
}

float Aircraft::GetTimeToFullCharge() const
{
    // Get how much charge the aircraft needs to be fully charged.
    float fChargeNeeded = mpoAircraftType->GetBatteryCapacity() - mfBatteryCharge;

    // Return the time it will take to fully charge the aircraft.
    return mpoAircraftType->GetTimeToCharge() * fChargeNeeded / mpoAircraftType->GetBatteryCapacity();
}

float Aircraft::Fly(float fDistance)
{
    // Throw an exception if the aircraft is already flying.
    if (mbIsFlying)
    {
        throw std::runtime_error("The aircraft is already flying.");
    }

    // Throw an exception if the distance is negative.
    if (fDistance < 0)
    {
        throw std::runtime_error("The distance is negative.");
    }

    // Throw an exception if there is not enough battery charge to fly.
    if (fDistance > GetCurrentRange())
    {
        throw std::runtime_error("Not enough battery charge to fly the distance.");
    }

    // Consume the battery charge.
    mfBatteryCharge -= fDistance * mpoAircraftType->GetEnergyUse();

    // The aircraft changes its state to flying.
    mbIsFlying = true;

    // The time the aircraft will be flying in hours.
    return fDistance / mpoAircraftType->GetCruiseSpeed();
}

void Aircraft::Land()
{
    // Throw an exception if the aircraft is not flying.
    if (!mbIsFlying)
    {
        throw std::runtime_error("The aircraft is not flying.");
    }

    // The aircraft changes its state to not flying.
    mbIsFlying = false;
}

float Aircraft::ChargeAircraft(Charger* poCharger, float fEnergy)
{
    // Throw an exception if the aircraft is already charging.
    if (mpoCharger != nullptr)
    {
        throw std::runtime_error("The aircraft is already charging.");
    }

    // Throw an exception if the aircraft is flying.
    if (mbIsFlying)
    {
        throw std::runtime_error("The aircraft is flying.");
    }

    // Throw an exception if the energy is negative.
    if (fEnergy < 0)
    {
        throw std::runtime_error("The energy is negative.");
    }

    // Throw an exception if the energy exceeds the remaining battery capacity.
    if (fEnergy > mpoAircraftType->GetBatteryCapacity() - mfBatteryCharge)
    {
        throw std::runtime_error("The energy exceeds the remaining battery capacity.");
    }

    // Charge the aircraft.
    mpoCharger = poCharger;
    mpoCharger->StartCharging();

    // Charge the aircraft.
    mfBatteryCharge += fEnergy;

    // Get the time it will take to charge the aircraft in hours.
    float fTimeToCharge = mpoAircraftType->GetTimeToCharge() * fEnergy / mpoAircraftType->GetBatteryCapacity();

    // Return the time it will take to charge the aircraft in hours.
    return fTimeToCharge;
}

Charger* Aircraft::StopCharging()
{
    // Throw an exception if the aircraft is not charging.
    if (mpoCharger == nullptr)
    {
        throw std::runtime_error("The aircraft is not charging.");
    }

    // Stop charging the aircraft.
    Charger* poCharger = mpoCharger;
    mpoCharger->StopCharging();
    mpoCharger = nullptr;

    // Return the charger that was charging the aircraft.
    return poCharger;
}
