#ifndef _SIMPLE_WORLD_H_
#define _SIMPLE_WORLD_H_

#include "SimulationWorld.h"

/**
 * @brief This class represents a simple world where the only dimension is
 *        the time, with aircrafts that can travel without changing their
 *        position and chargers located in the only position. 
 * 
 */
class SimpleWorld : public SimulationWorld
{
public:
    /********** Constructors **********/

    /**
     * @brief Construct a new Simple World object.
     * 
     * @param uiMaxAircrafts     The maximum number of aircrafts that can be
     *                           in the world at the same time.
     * @param uiMaxChargers      The maximum number of chargers that can be
     *                           in the world at the same time.
     */
    SimpleWorld(uint8_t uiMaxAircrafts, uint8_t uiMaxChargers);

    /********** Destructor **********/

    /**
     * @brief Destroy the Simple World object.
     * 
     */
    ~SimpleWorld();

    /********** Methods **********/

    /**
     * @brief Run the simulation for a given number of hours using the Event-Driven method.
     * 
     * @param uiHours       The number of hours to run the simulation.
     */
    void RunSimulation(uint16_t uiHours) override;

    /**
     * @brief Print the statistics of the world.
     * 
     */
    void PrintStatistics() const override;
};

#endif // _SIMPLE_WORLD_H_
