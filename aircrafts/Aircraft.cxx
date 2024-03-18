/**
 * @brief Contains tests for the Aircraft class.
 *
*/

#include "Aircraft.h"
#include "worlds/Charger.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Aircraft::GetName()", )
{
    // Create two aircrafts of the same company and check if the names are different.
    Aircraft oAircraft1(AircraftCompany::Alpha);
    Aircraft oAircraft2(AircraftCompany::Alpha);
    REQUIRE(oAircraft1.GetName() != oAircraft2.GetName());

    // Check if poAircraft1 name is "Alpha-" + Id.
    REQUIRE(oAircraft1.GetName() == "Alpha-" + to_string(oAircraft1.GetId()));
}
