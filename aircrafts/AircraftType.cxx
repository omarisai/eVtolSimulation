/**
 * @brief Contains tests for the AircraftType class.
 * 
*/

#include "Aircraft.h"

#include <catch2/catch_test_macros.hpp>

// Test the AircraftType::CompanyName() method.
// Check if we can print all the company names, as this can fail if the enum gets updated.
TEST_CASE( "AircraftType::CompanyName()" )
{
    // Iterate through all the companies and check the name is different to "Unknown".
    for (size_t i = 0; i < (size_t)AircraftCompany::TotalCompanies; i++)
    {
        AircraftType& oAircraftType = AircraftType::msoAircraftTypes[i];
        REQUIRE(oAircraftType.CompanyName() != "Unknown");
    }
}
