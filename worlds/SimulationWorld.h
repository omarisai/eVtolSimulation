/**
 * @brief Abstract class to represent a simulation world.
 * 
 * @note  This is an abstract class to allow the creation of different
 *       simulation worlds, for example, a world with a different number
 *       of dimensions or different kind of chargers, for example, chargers
 *       not located in the same position.
 * 
 */

#ifndef _SIMULATION_WORLD_H_
#define _SIMULATION_WORLD_H_

#include "Aircraft.h"
#include "Charger.h"

#include <cstdint>
#include <vector>

using namespace std;


class SimulationWorld
{
public:
    /********** Constructors **********/

    /**
     * @brief Construct a new Simulation World object.
     * 
     * @param uiMaxAircrafts     The maximum number of aircrafts that can be
     *                           in the world at the same time.
     * @param uiMaxChargers      The maximum number of chargers that can be
     *                           in the world at the same time.
     */
    SimulationWorld(uint32_t uiMaxAircrafts, uint32_t uiMaxChargers);


    /********** Destructor **********/

    /**
     * @brief Destroy the Simulation World object.
     * 
     */
    virtual ~SimulationWorld();


    /********** Properties **********/

    /**
     * @brief Get the maximum number of aircrafts that can be in the world
     *        at the same time.
     * 
     * @return uint32_t     The maximum number of aircrafts.
     */
    inline uint32_t GetMaxAircrafts() const { return muiMaxAircrafts; }

    /**
     * @brief Get the maximum number of chargers that can be in the world
     *        at the same time.
     * 
     * @return uint32_t     The maximum number of chargers.
     */
    inline uint32_t GetMaxChargers() const { return muiMaxChargers; }

    /**
     * @brief Get the number of aircrafts in the world.
     * 
     * @return uint32_t     The number of aircrafts.
     */
    inline uint32_t GetAircraftsCount() const { return moAircrafts.size(); }


    /********** Methods **********/

    /**
     * @brief Add an aircraft to the world.
     * 
     * @param oAircraft     The aircraft to add.
     * 
     * @return true         If the aircraft was added successfully.
     * 
     */
    bool AddAircraft(const Aircraft* oAircraft);

    /**
     * @brief Remove an aircraft from the world.
     * 
     * @param oAircraft     The aircraft to remove.
     * 
     * @return true         If the aircraft was removed successfully.
     * 
     */
    bool RemoveAircraft(const Aircraft* oAircraft);

    /**
     * @brief Add a charger to the world.
     * 
     * @param oCharger      The charger to add.
     * 
     * @return true         If the charger was added successfully.
     * 
     */
    bool AddCharger(const Charger* oCharger);

    /**
     * @brief Remove a charger from the world.
     * 
     * @param oCharger      The charger to remove.
     * 
     * @return true         If the charger was removed successfully.
     * 
     */
    bool RemoveCharger(const Charger* oCharger);

    /**
     * @brief Generate the world.
     * 
     */
    virtual void Generate() = 0;

    /**
     * @brief Run the simulation for a given number of hours.
     * 
     * @param uiHours       The number of hours to run the simulation.
     */
    virtual void RunSimulation(uint16_t uiHours) = 0;

private:
    uint32_t muiMaxAircrafts;
    uint32_t muiMaxChargers;
    vector<const Aircraft*> moAircrafts;
    vector<const Charger*> moChargers;
};

#endif // _SIMULATION_WORLD_H_
