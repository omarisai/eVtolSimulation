/**
 * @brief Implementation of the Charger class.
 * 
 */

#include "Charger.h"

uint8_t Charger::muiTotalChargers = 0;

Charger::Charger()
    : mbCharging(false),
      muiChargerId(muiTotalChargers++)
{
    // Nothing to do here.
}

void Charger::StartCharging()
{
    mbCharging = true;
}

void Charger::StopCharging()
{
    mbCharging = false;
}

string Charger::GetName() const
{
    return "Charger-" + to_string(muiChargerId);
}
