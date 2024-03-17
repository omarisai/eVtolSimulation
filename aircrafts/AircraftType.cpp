/**
 * @brief Implementation of the AircraftType class methods,
 *       constructors, and destructor.
 * 
 */

#include "AircraftType.h"

// Loading all the types of aircrafts at build time.
/*static*/ AircraftType AircraftType::msoAircraftTypes[] = {
    AircraftType(AircraftCompany::Alpha,   120/*mph*/, 320/*kWh*/, 0.6 /*hours*/, 1.6/*kWh/mile*/, 4, 0.25),
    AircraftType(AircraftCompany::Bravo,   100/*mph*/, 100/*kWh*/, 0.2 /*hours*/, 1.5/*kWh/mile*/, 5, 0.10),
    AircraftType(AircraftCompany::Charlie, 160/*mph*/, 220/*kWh*/, 0.8 /*hours*/, 2.2/*kWh/mile*/, 3, 0.05),
    AircraftType(AircraftCompany::Delta,    90/*mph*/, 120/*kWh*/, 0.62/*hours*/, 0.8/*kWh/mile*/, 2, 0.22),
    AircraftType(AircraftCompany::Echo,     30/*mph*/, 150/*kWh*/, 0.3 /*hours*/, 5.8/*kWh/mile*/, 2, 0.61),
};

// Check if the number of aircraft types matches the number of companies.
static_assert(sizeof(AircraftType::msoAircraftTypes) / sizeof(AircraftType) == (size_t)AircraftCompany::TotalCompanies,
              "The number of aircraft types does not match the number of companies.");

AircraftType::AircraftType(AircraftCompany eCompany,
                           uint16_t uiCruiseSpeed,
                           uint16_t uiBatteryCapacity,
                           float fTimeToCharge,
                           float fEnergyUse,
                           uint8_t uiPassengers,
                           float fFaultProbability)
    : mkeCompany(eCompany),
      mkuiCruiseSpeed(uiCruiseSpeed),
      mkuiBatteryCapacity(uiBatteryCapacity),
      mkfTimeToCharge(fTimeToCharge),
      mkfEnergyUse(fEnergyUse),
      mkuiPassengers(uiPassengers),
      mkfFaultProbability(fFaultProbability),
      muiTotalNumberOfFaults(0),
      muiTotalNumberOfPassengerMiles(0),
      muiTotalAircrafts(0)
{
    // Nothing to do here.
}

string AircraftType::CompanyName() const
{
    switch (mkeCompany)
    {
        case AircraftCompany::Alpha:   return "Alpha";
        case AircraftCompany::Bravo:   return "Bravo";
        case AircraftCompany::Charlie: return "Charlie";
        case AircraftCompany::Delta:   return "Delta";
        case AircraftCompany::Echo:    return "Echo";
        default:                       return "Unknown";
    }
}