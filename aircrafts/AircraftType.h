#ifndef _AIRCRAFTSPECS_H_
#define _AIRCRAFTSPECS_H_

#include <cstdint>
#include <string>

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
enum class AircraftCompany : uint8_t
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
     * @brief Get the total number of faults.
     * 
     * @return The total number of faults. 
     */
    inline uint16_t TotalNumberOfFaults() const { return muiTotalNumberOfFaults; }

    /**
     * @brief Get the total number of aircrafts of this type.
     * 
     * @return The total number of aircrafts. 
     */
    inline uint8_t TotalAircrafts() const { return muiTotalAircrafts; }

    /**
     * @brief Get the total number of flights.
     * 
     * @return The total number of flights. 
     */
    inline uint16_t TotalFlights() const { return muiTotalFlights; }

    /**
     * @brief Get the total charge sessions.
     * 
     * @return The total charge sessions. 
     */
    inline uint16_t TotalChargeSessions() const { return muiTotalChargeSessions; }

    /**
     * @brief Get the total number of miles travelled by the aircrafts of this type.
     * 
     * @return The total number of miles. 
     */
    inline float TotalNumberOfMiles() const { return mfTotalNumberOfMiles; }

    /**
     * @brief Get the total number of passengers transported by the aircrafts of this type.
     * 
     * @return The total number of passengers. 
     */
    inline uint16_t TotalNumberOfPassengers() const { return mkuiPassengers * muiTotalFlights; }


    /********** Static Methods **********/

    /**
     * @brief Get an aircraft type by company.
     * 
     * @param eCompany  The aircraft company.
     * 
     * @return The pointer to the aircraft type.
     * 
     * @throws std::runtime_error if the company is not valid.
     */
    static AircraftType* GetAircraftType(AircraftCompany eCompany);


    /********** Methods **********/

    /**
     * @brief Register a new aircraft of this type.
     * 
     * @return The Id for the new registered aircraft. 
     */
    inline uint8_t RegisterAircraft() { return muiTotalAircrafts++; }

    /**
     * @brief Get the total number of passenger miles.
     * 
     * @return The total number of passenger miles. 
     */
    float TotalNumberOfPassengerMiles() const;

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
     * @brief Report a flight for the aircraft type.
     * 
     * @param fFlightTime   The flight time in hours.
     * @param fDistance     The distance travelled in miles.
     */ 
    void ReportFlight(float fFlightTime, float fDistance);

    /**
     * @brief Get the average time charging per charge session in hours.
     * 
     * @return The average time charging. 
     */
    float AverageTimeChargingPerChargeSession() const;

    /**
     * @brief Report a charging session for the aircraft type.
     * 
     * @param fTimeCharging   The time charging in hours.
     */
    void ReportChargeSession(float fTimeCharging);

    /**
     * @brief Get the aircraft company name in string format.
     * 
     * @return The company name.
     */
    string CompanyName() const;

private:
    /**
     * @brief Calculate the number of faults that will occur during a flight.
     * 
     * @param fFlightTime   The flight time in hours.
     * 
     * @return The number of faults that will occur during the flight.
     */
    uint16_t CalculateFaultsPerFlight(float fFlightTime) const;


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
    uint16_t muiTotalChargeSessions;
    float mfTotalTimeCharging;
    float mfTotalNumberOfMiles;
    uint8_t muiTotalAircrafts;

    // For the statistics.
    float mfTotalFlightTime;
    uint16_t muiTotalFlights;

    /********** Static Variables **********/
    static AircraftType msoAircraftTypes[];
};

#endif // _AIRCRAFTSPECS_H_
