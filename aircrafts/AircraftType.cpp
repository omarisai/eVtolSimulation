/**
 * @brief Implementation of the AircraftType class methods,
 *       constructors, and destructor.
 * 
 */

#include "AircraftType.h"

#include <stdexcept>

// Loading all the types of aircrafts at build time.
/*static*/ AircraftType AircraftType::msoAircraftTypes[] = {
    AircraftType(AircraftCompany::Alpha,   120/*mph*/, 320/*kWh*/, 0.6 /*hours*/, 1.6/*kWh/mile*/, 4, 0.25),
    AircraftType(AircraftCompany::Bravo,   100/*mph*/, 100/*kWh*/, 0.2 /*hours*/, 1.5/*kWh/mile*/, 5, 0.10),
    AircraftType(AircraftCompany::Charlie, 160/*mph*/, 220/*kWh*/, 0.8 /*hours*/, 2.2/*kWh/mile*/, 3, 0.05),
    AircraftType(AircraftCompany::Delta,    90/*mph*/, 120/*kWh*/, 0.62/*hours*/, 0.8/*kWh/mile*/, 2, 0.22),
    AircraftType(AircraftCompany::Echo,     30/*mph*/, 150/*kWh*/, 0.3 /*hours*/, 5.8/*kWh/mile*/, 2, 0.61),
};

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
      muiTotalChargeSessions(0),
      mfTotalTimeCharging(0.0f),
      mfTotalNumberOfMiles(0.0f),
      muiTotalAircrafts(0),
      mfTotalFlightTime(0.0f),
      muiTotalFlights(0)
{
    // Check if the number of aircraft types matches the number of companies.
    static_assert(sizeof(AircraftType::msoAircraftTypes) / sizeof(AircraftType) == (size_t)AircraftCompany::TotalCompanies,
              "The number of aircraft types does not match the number of companies.");
}

/*static*/ AircraftType* AircraftType::GetAircraftType(AircraftCompany eCompany)
{
    // Throw an exception if the company is invalid.
    if (eCompany >= AircraftCompany::TotalCompanies)
    {
        throw std::runtime_error("Invalid aircraft company.");
    }

    // Return the aircraft type.
    return &AircraftType::msoAircraftTypes[(size_t)eCompany];
}

float AircraftType::TotalNumberOfPassengerMiles() const
{
    return mkuiPassengers * mfTotalNumberOfMiles;
}

float AircraftType::AverageFlightTimePerFlight() const
{
    return muiTotalFlights > 0 ? mfTotalFlightTime / muiTotalFlights : 0.0f;
}

float AircraftType::AverageDistanceTravelledPerFlight() const
{
    return muiTotalFlights > 0 ? mfTotalNumberOfMiles / muiTotalFlights : 0.0f;
}

void AircraftType::ReportFlight(float fDistance, float fTime)
{
    // Update the total number of flights.
    ++muiTotalFlights;

    // Update the total number of miles.
    mfTotalNumberOfMiles += fDistance;

    // Update the total flight time.
    mfTotalFlightTime += fTime;

    // Update the total number of faults.
    muiTotalNumberOfFaults += CalculateFaultsPerFlight(fTime);
}

float AircraftType::AverageTimeChargingPerChargeSession() const
{
    return muiTotalChargeSessions > 0 ? mfTotalTimeCharging / muiTotalChargeSessions : 0.0f;
}

void AircraftType::ReportChargeSession(float fTimeCharging)
{
    // Update the total number of charging sessions.
    ++muiTotalChargeSessions;

    // Update the total time charging.
    mfTotalTimeCharging += fTimeCharging;
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

uint16_t AircraftType::CalculateFaultsPerFlight(float fFlightTime) const
{
    // Calculate the probability of faults that will occur during the flight.
    float fProbabilityOfFaults = mkfFaultProbability * fFlightTime;

    // Get the integer part of the probability of faults.
    uint16_t uiFaults = (uint16_t)fProbabilityOfFaults;

    // Get the decimal part of the probability of faults.
    float fDecimalPart = fProbabilityOfFaults - uiFaults;

    // Get a random number between 0 and 1.
    float fRandom = (float)rand() / RAND_MAX;

    // If the random number is less than the decimal part, add one to the number of faults.
    if (fRandom < fDecimalPart)
    {
        ++uiFaults;
    }

    return uiFaults;
}
