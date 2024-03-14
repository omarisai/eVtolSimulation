/**
 * @brief The Aircraft class. Encapsulates all the common aircraft
 *       properties and methods.
 * 
 *       It represents an aircraft in a simulation world where the
 *       only existing aircrafts are eVTOLs.
 * 
 */

#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_

#include <cstdint>

using namespace std;

class Aircraft
{
public:
    /********** Types **********/

    /**
     * @brief The aircraft company.
     * 
     * @note Does it worth to create derived classes for each company?
     *       It depends on what are the differences processing the data,
     *       or if some companies aircrafts have different properties
     *       not shared with the others, in this case I consider it doesn't
     *       worth to create derived classes so far.
     * 
     * @note Why an enum class and not a string for the company name?
     *       Because it's more efficient in terms of memory and performance,
     *       and it's more secure because it's not possible to assign a value
     *       that is not part of the enum. Also is easier to iterate through
     *       the enum values.
     * 
     */
    enum class AircraftCompany
    {
        AlphaCompany,
        BravoCompany,
        CharlieCompany,
        DeltaCompany,
        EchoCompany,

        // Add more companies here...

        TotalCompanies,
    };


    /********** Constructors **********/

    /**
     * @brief Construct a new Aircraft object
     * 
     * @param eCompany              The aircraft company.
     * @param uiCruiseSpeed         The cruise speed in mph.
     * @param uiBatteryCapacity     The battery capacity in kWh.
     * @param fTimeToCharge         The time to charge in hours.
     * @param fEnergyUse            The energy use at cruise in kWh/mile.
     * @param uiPassengers          The passengers count.
     * @param fFaultProbability     The probability of fault per hour.
     */
    Aircraft(AircraftCompany eCompany, uint16_t uiCruiseSpeed, uint16_t uiBatteryCapacity, float fTimeToCharge,
        float fEnergyUse, uint8_t uiPassengers, float fFaultProbability);
    
    /**
     * @brief Destroy the Aircraft object
     * 
     */
    ~Aircraft();


    /********** Properties **********/

    /**
     * @brief Geta the Cruise Speed value in mph.
     * 
     * @return uint16_t 
     */
    inline uint16_t GetCruiseSpeed() const { return muiCruiseSpeed; }

    /**
     * @brief Gets the Battery Capacity value in kWh.
     * 
     * @return uint16_t 
     */
    inline uint16_t GetBatteryCapacity() const { return muiBatteryCapacity; }

    /**
     * @brief Gets the Time to Charge value in hours.
     * 
     * @return float 
     */
    inline float GetTimeToCharge() const { return mfTimeToCharge; }

    /**
     * @brief Gets the Energy Use value in kWh/mile.
     * 
     * @return float 
     */
    inline float GetEnergyUse() const { return mfEnergyUse; }

    /**
     * @brief Gets the Passengers count.
     * 
     * @return uint8_t 
     */
    inline uint8_t GetPassengers() const { return muiPassengers; }

    /**
     * @brief Gets the Fault Probability value.
     * 
     * @return float 
     */
    inline float GetFaultProbability() const { return mfFaultProbability; }


    /********** Methods **********/

    //TODO: Add methods here...

protected:
    uint16_t muiCruiseSpeed;
    uint16_t muiBatteryCapacity;
    float mfTimeToCharge;
    float mfEnergyUse;
    uint8_t muiPassengers;
    float mfFaultProbability;
};

#endif // _AIRCRAFT_H_
