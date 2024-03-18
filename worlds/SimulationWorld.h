#ifndef _SIMULATION_WORLD_H_
#define _SIMULATION_WORLD_H_

#include "aircrafts/Aircraft.h"
#include "Charger.h"

#include <cstdint>
#include <vector>

using namespace std;

/**
 * @brief Abstract class to represent a simulation world.
 * 
 * @note  This is an abstract class to allow the creation of different
 *       simulation worlds, for example, a world with 2 or 3 spacial
 *       dimensions or different kind of chargers, for example, chargers
 *       not located in the same position.
 * 
 */
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
    SimulationWorld(uint8_t uiMaxAircrafts, uint8_t uiMaxChargers);


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
     * @return The maximum number of aircrafts.
     */
    inline uint32_t GetMaxAircrafts() const { return muiMaxAircrafts; }

    /**
     * @brief Get the maximum number of chargers that can be in the world
     *        at the same time.
     * 
     * @return The maximum number of chargers.
     */
    inline uint32_t GetMaxChargers() const { return muiMaxChargers; }

    /**
     * @brief Get the number of aircrafts in the world.
     * 
     * @return The number of aircrafts.
     */
    inline uint32_t GetAircraftsCount() const { return moAircrafts.size(); }

    /**
     * @brief Get the number of chargers in the world.
     * 
     * @return The number of chargers.
     */
    inline uint32_t GetChargersCount() const { return moChargers.size(); }


    /********** Methods **********/

    /**
     * @brief Run the simulation for a given number of hours.
     * 
     * @param uiHours       The number of hours to run the simulation.
     */
    virtual void RunSimulation(uint16_t uiHours) = 0;

    /**
     * @brief Print the world statistics.
     * 
     */
    virtual void PrintStatistics() const;

protected:
    /********** Methods **********/

    /**
     * @brief Get the aircrafts in the world.
     * 
     * @return The aircrafts.
     * 
     */
    const vector<Aircraft*>& GetAircrafts() const { return moAircrafts; }

    /**
     * @brief Get the chargers in the world.
     * 
     * @return The chargers.
     * 
     */
    const vector<Charger*>& GetChargers() const { return moChargers; }

    /**
     * @brief Add an aircraft to the world.
     * 
     * @param oAircraft     The aircraft to add.
     * 
     * @return If the aircraft was added successfully.
     * 
     */
    bool AddAircraft(Aircraft* oAircraft);

    /**
     * @brief Add a charger to the world.
     * 
     * @param oCharger      The charger to add.
     * 
     * @return If the charger was added successfully.
     * 
     */
    bool AddCharger(Charger* oCharger);

    /**
     * @brief Set the simulation time.
     * 
     * @param uiTime        The simulation time.
     * 
     */
    inline void SetSimulationTime(uint16_t uiTime) { muiSimulationTime = uiTime; }

    /**
     * @brief Get the simulation time.
     * 
     * @return The simulation time.
     * 
     */
    inline uint16_t GetSimulationTime() const { return muiSimulationTime; }

private:
    /********** Variables **********/

    vector<Aircraft*> moAircrafts;
    vector<Charger*> moChargers;
    uint16_t muiSimulationTime;
    uint8_t muiMaxAircrafts;
    uint8_t muiMaxChargers;
};

#endif // _SIMULATION_WORLD_H_
