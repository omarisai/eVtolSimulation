#ifndef _AIRCRAFTSPECS_H_
#define _AIRCRAFTSPECS_H_

#include <cstdint>

using namespace std;

/**
 * @brief The aircraft company.
 * 
 * @note Why an enum class and not a string for the company name?
 *       Because it's more efficient in terms of memory and performance,
 *       and it's more secure because it's not possible to assign a value
 *       that is not part of the enum. Also is easier to iterate through
 *       the enum values or get the total number of companies.
 * 
 */
enum class AircraftCompany
{
    Alpha,
    Bravo,
    Charlie,
    Delta,
    Echo,

    // Add more companies here...

    TotalCompanies,
};

/**
 * @brief Represents a type of an aircraft.
 * 
 * @note  This class is used to store the specifications of an aircraft type,
 *        but also to calculate some statistics about the aircraft type.
 */
class AircraftType
{
private:
    /********** Constructors **********/

    /**
     * @brief Construct a new Aircraft Specs object
     * 
     * @param eCompany              The aircraft company.
     * @param uiCruiseSpeed         The cruise speed in mph.
     * @param uiBatteryCapacity     The battery capacity in kWh.
     * @param fTimeToCharge         The time to charge in hours.
     * @param fEnergyUse            The energy use at cruise in kWh/mile.
     * @param uiPassengers          The passengers count.
     * @param fFaultProbability     The probability of fault per hour.
     */
    AircraftType(AircraftCompany eCompany,
                uint16_t uiCruiseSpeed,
                uint16_t uiBatteryCapacity,
                float fTimeToCharge,
                float fEnergyUse,
                uint8_t uiPassengers,
                float fFaultProbability);

    /********** Properties **********/

public:
    /**
     * @brief Gets the aircraft company.
     * 
     * @return Company 
     */
    inline AircraftCompany GetCompany() const { return mkeCompany; }

    /**
     * @brief Get the cruise speed in mph.
     * 
     * @return The cruise speed.
     */
    inline uint16_t GetCruiseSpeed() const { return mkuiCruiseSpeed; }

    /**
     * @brief Get the battery capacity in kWh.
     * 
     * @return The battery capacity.
     */
    inline uint16_t GetBatteryCapacity() const { return mkuiBatteryCapacity; }

    /**
     * @brief Get the time to charge in hours.
     * 
     * @return The time to charge.
     */
    inline float GetTimeToCharge() const { return mkfTimeToCharge; }

    /**
     * @brief Get the energy use at cruise in kWh/mile.
     * 
     * @return The energy use.
     */
    inline float GetEnergyUse() const { return mkfEnergyUse; }

    /**
     * @brief Get the passengers count.
     * 
     * @return The passengers count.
     */
    inline uint8_t GetPassengers() const { return mkuiPassengers; }

    /**
     * @brief Get the probability of fault per hour.
     * 
     * @return The probability of fault.
     */
    inline float GetFaultProbability() const { return mkfFaultProbability; }

    /**
     * @brief Get the average flight time per flight in hours.
     * 
     * @return The average flight time. 
     */
    float AverageFlightTimePerFlight() const;

    /**
     * @brief Get the average distance travelled per flight in miles.
     * 
     * @return The average distance travelled. 
     */
    float AverageDistanceTravelledPerFlight() const;

    /**
     * @brief Get the average time charging per charge session in hours.
     * 
     * @return The average time charging. 
     */
    float AverageTimeChargingPerChargeSession() const;

    /**
     * @brief Get the total number of faults.
     * 
     * @return The total number of faults. 
     */
    uint16_t TotalNumberOfFaults() const;

    /**
     * @brief Get the total number of passenger miles.
     * 
     * @return The total number of passenger miles. 
     */
    uint16_t TotalNumberOfPassengerMiles() const;

private:
    /********** Constants **********/
    const AircraftCompany mkeCompany;
    const uint16_t mkuiCruiseSpeed;
    const uint16_t mkuiBatteryCapacity;
    const float mkfTimeToCharge;
    const float mkfEnergyUse;
    const uint8_t mkuiPassengers;
    const float mkfFaultProbability;

    /********** Variables **********/
    uint16_t muiTotalNumberOfFaults;
    uint16_t muiTotalNumberOfPassengerMiles;

    /********** Static Variables **********/
public:
    static const AircraftType mskoAircraftTypes[];
};

#endif // _AIRCRAFTSPECS_H_
