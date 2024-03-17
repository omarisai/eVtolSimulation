#ifndef _CHARGER_H_
#define _CHARGER_H_

#include "aircrafts/Aircraft.h"

/**
 * @brief Generic class for the chargers, which will be used to charge the
 *        aircrafts.
 * 
 * @note This is the default charger, but it can be derived to create different
 *       chargers with different properties, for example, a charger that have a
 *       location X, Y in a 2D world.
 * 
 */
class Charger
{
public:
    /********** Constructors **********/

    /**
     * @brief Construct a new Charger object.
     * 
     */
    Charger();

    /********** Destructor **********/

    /**
     * @brief Destroy the Charger object.
     * 
     */
    virtual ~Charger() {}


    /********** Properties **********/

    /**
     * @brief Gets if the charger is charging an aircraft.
     * 
     * @return True if is charging an aircraft, false otherwise.
     */
    inline bool IsCharging() const { return mbCharging; }

    /**
     * @brief Gets the id of the charger.
     * 
     * @return The id of the charger.
     */
    virtual uint8_t GetId() const { return muiChargerId; }


    /********** Methods **********/

    /**
     * @brief Start charging the aircraft.
     *
     */
    virtual void StartCharging();

    /**
     * @brief Stop charging the aircraft.
     * 
     */
    virtual void StopCharging();

    /**
     * @brief Get the name of the charger.
     * 
     * @return The name of the charger.
     */
    virtual string GetName() const;

private:
    bool mbCharging;       // If the charger is charging an aircraft.
    uint8_t muiChargerId;  // The charger id.
    static uint8_t muiTotalChargers; // The total number of chargers.
};

#endif // _CHARGER_H_
