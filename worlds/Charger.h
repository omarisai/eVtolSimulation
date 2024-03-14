/**
 * @brief Generic class for the chargers, which will be used to charge the
 *        aircrafts.
 * 
 * @note  This is the default charger, but it can be derived to create different
 *       chargers with different properties, for example, a charger that have a
 *       location X, Y in a 2D world.
 * 
 */

#ifndef _CHARGER_H_
#define _CHARGER_H_

#include "Aircraft.h"

class Charger
{
public:
    /********** Types **********/
    enum class State
    {
        Available,
        Charging
    };

    /********** Properties **********/

    /**
     * @brief Gets the state of the charger.
     * 
     * @return State    The state of the charger.
     */
    inline State GetState() const { return meState; }


    /********** Methods **********/

    /**
     * @brief Charge the aircraft.
     * 
     * @param oAircraft     The aircraft to charge.
     * 
     * @return float        The time it takes to charge the aircraft in hours.
     */
    virtual float ChargeAircraft(Aircraft* oAircraft);

    /**
     * @brief Stop charging the aircraft.
     * 
     */
    virtual void StopCharging();

protected:
    State meState;
};

#endif // _CHARGER_H_
