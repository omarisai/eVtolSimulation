/**
 * @brief Contains tests for the Aircraft class.
 *
*/

#include "Aircraft.h"
#include "worlds/Charger.h"

#include <catch2/catch_test_macros.hpp>

// Test the Aircraft::Aircraft() constructor.
TEST_CASE( "Aircraft::Aircraft", )
{
    // Check if we get an exception when creating an aircraft with an invalid company.
    REQUIRE_THROWS(Aircraft(AircraftCompany::TotalCompanies));

    // Check if we get an exception with a negative company.
    REQUIRE_THROWS(Aircraft((AircraftCompany)-1));
}

// Test the Aircraft::GetName() method.
TEST_CASE( "Aircraft::GetName", )
{
    // Create two aircrafts of the same company and check if the names are different.
    Aircraft oAircraft1(AircraftCompany::Alpha);
    Aircraft oAircraft2(AircraftCompany::Alpha);
    REQUIRE(oAircraft1.GetName() != oAircraft2.GetName());

    // Check if poAircraft1 name is "Alpha-" + Id.
    REQUIRE(oAircraft1.GetName() == "Alpha-" + to_string(oAircraft1.GetId()));
}

// Test the Aircraft::GetCurrentRange() method.
TEST_CASE( "Aircraft::GetCurrentRange", )
{
    // Check if a new aircraft has the full range.
    AircraftCompany eCompany = AircraftCompany::Alpha;
    AircraftType oAircraftType = *AircraftType::GetAircraftType(eCompany);
    Aircraft oAircraft(eCompany);
    REQUIRE(oAircraft.GetCurrentRange() == oAircraftType.GetBatteryCapacity() / oAircraftType.GetEnergyUse());

    // Check if the range is reduced half after flying half of the range.
    float fRange = oAircraft.GetCurrentRange();
    oAircraft.Fly(fRange / 2);
    oAircraft.Land();
    REQUIRE(oAircraft.GetCurrentRange() == fRange / 2);

    // Check if the range is zero after flying the full range.
    oAircraft.Fly(fRange / 2);
    REQUIRE(oAircraft.GetCurrentRange() == 0);
}

// Test the Aircraft::GetTimeToFullCharge() method.
TEST_CASE( "Aircraft::GetTimeToFullCharge", )
{
    // Check if the time to full charge is zero when the battery is full.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE(oAircraft.GetTimeToFullCharge() == 0);

    // Check if the time to full charge is correct when the battery is empty.
    oAircraft.Fly(oAircraft.GetCurrentRange());
    REQUIRE(oAircraft.GetTimeToFullCharge() == oAircraft.GetAircraftType()->GetTimeToCharge());

    // Check if the time to full charge is correct when the battery is half full.
    oAircraft.Land();
    Charger oCharger;
    oAircraft.ChargeAircraft(&oCharger, oAircraft.GetAircraftType()->GetBatteryCapacity() / 2);
    REQUIRE(oAircraft.GetTimeToFullCharge() == oAircraft.GetAircraftType()->GetTimeToCharge() / 2);
}

// Test the Aircraft::Fly() method.
TEST_CASE( "Aircraft::Fly", )
{
    // Check if we get an exception when flying an aircraft that is already flying.
    Aircraft oAircraft(AircraftCompany::Alpha);
    const float fHalfRange = oAircraft.GetCurrentRange() / 2;
    oAircraft.Fly(fHalfRange);
    REQUIRE_THROWS(oAircraft.Fly(fHalfRange));

    // Check if we get an exception when flying an aircraft exceeding the range.
    oAircraft = Aircraft(AircraftCompany::Alpha);
    REQUIRE_THROWS(oAircraft.Fly(oAircraft.GetCurrentRange() + 1));

    // Check if we get an exception when trying to fly with a negative distance.
    REQUIRE_THROWS(oAircraft.Fly(-1));

    // Check if flying full range reduces the battery charge to zero.
    oAircraft = Aircraft(AircraftCompany::Alpha);
    oAircraft.Fly(oAircraft.GetCurrentRange());
    REQUIRE(oAircraft.GetBatteryCharge() == 0);

    // Check if we get an exception when trying to fly with zero battery charge.
    oAircraft.Land();
    REQUIRE_THROWS(oAircraft.Fly(1));

    // Check if we get an exception when trying to fly when charging.
    Charger oCharger;
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE_THROWS(oAircraft.Fly(1));
}

// Test the Aircraft::Land() method.
TEST_CASE( "Aircraft::Land", )
{
    // Check if we get an exception when landing an aircraft that is not flying.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE_THROWS(oAircraft.Land());

    // Check if the aircraft is not flying after landing.
    oAircraft.Fly(oAircraft.GetCurrentRange() / 2);
    oAircraft.Land();
    REQUIRE_FALSE(oAircraft.IsFlying());

    // Check if we get an exception when landing an aircraft that is already landed.
    REQUIRE_THROWS(oAircraft.Land());
}

// Test the Aircraft::ChargeAircraft() method.
TEST_CASE( "Aircraft::ChargeAircraft", )
{
    // Check if we get an exception when charging an aircraft that is flying.
    Charger oCharger;
    Aircraft oAircraft = Aircraft(AircraftCompany::Alpha);
    oAircraft.Fly(oAircraft.GetCurrentRange() / 2);
    REQUIRE_THROWS(oAircraft.ChargeAircraft(&oCharger, 0.1f));
    oAircraft.Land();

    // Check if we get an exception when charging an aircraft with negative energy.
    REQUIRE_THROWS(oAircraft.ChargeAircraft(&oCharger, -0.1f));

    // Check if we get an exception when charging an aircraft that is already charging.
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE_THROWS(oAircraft.ChargeAircraft(&oCharger, 0.1f));

    // Check if the battery charge is correct after charging.
    oAircraft = Aircraft(AircraftCompany::Alpha);
    oAircraft.Fly(oAircraft.GetCurrentRange());
    oAircraft.Land();
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE(oAircraft.GetBatteryCharge() == 0.1f);
}

// Test the Aircraft::StopCharging() method.
TEST_CASE( "Aircraft::StopCharging", )
{
    // Check if we get an exception when stopping charging an aircraft that is not charging.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE_THROWS(oAircraft.StopCharging());
    oAircraft.Fly(oAircraft.GetCurrentRange());
    REQUIRE_THROWS(oAircraft.StopCharging());

    // Check if the charger is correct after stopping charging.
    oAircraft.Land();
    Charger oCharger;
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE(oAircraft.StopCharging() == &oCharger);

    // Check if we get an exception when stopping charging an aircraft that is not charging
    // after stopping charging it.
    REQUIRE_THROWS(oAircraft.StopCharging());
}

// Test the Aircraft::GetBatteryCharge() method.
TEST_CASE( "Aircraft::GetBatteryCharge", )
{
    // Check if the battery charge is correct after flying.
    Aircraft oAircraft(AircraftCompany::Alpha);
    const float fHalfRange = oAircraft.GetCurrentRange() / 2;
    oAircraft.Fly(fHalfRange);
    REQUIRE(oAircraft.GetBatteryCharge() == oAircraft.GetAircraftType()->GetBatteryCapacity() / 2);

    // Check if the battery charge is correct after charging.
    oAircraft.Land();
    Charger oCharger;
    float fCharge = oAircraft.GetBatteryCharge();
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE(oAircraft.GetBatteryCharge() == fCharge + 0.1f);
}

// Test the Aircraft::GetAircraftType() method.
TEST_CASE( "Aircraft::GetAircraftType", )
{
    // Check if the aircraft type is correct.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE(oAircraft.GetAircraftType() == AircraftType::GetAircraftType(AircraftCompany::Alpha));
}

// Test the Aircraft::GetId() method.
TEST_CASE( "Aircraft::GetId", )
{
    // Check if the aircraft Id increases with each new aircraft.
    Aircraft oAircraft1(AircraftCompany::Alpha);
    Aircraft oAircraft2(AircraftCompany::Alpha);
    REQUIRE(oAircraft1.GetId() + 1 == oAircraft2.GetId());
}

// Test the Aircraft::IsFlying() method.
TEST_CASE( "Aircraft::IsFlying", )
{
    // Check if the aircraft is not flying after creating it.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE_FALSE(oAircraft.IsFlying());

    // Check if the aircraft is flying after flying it.
    oAircraft.Fly(oAircraft.GetCurrentRange() / 2);
    REQUIRE(oAircraft.IsFlying());

    // Check if the aircraft is not flying after landing it.
    oAircraft.Land();
    REQUIRE_FALSE(oAircraft.IsFlying());
}

// Test the Aircraft::IsCharging() method.
TEST_CASE( "Aircraft::IsCharging", )
{
    // Check if the aircraft is not charging after creating it.
    Aircraft oAircraft(AircraftCompany::Alpha);
    REQUIRE_FALSE(oAircraft.IsCharging());

    // Check if the aircraft is not charging after landing it.
    oAircraft.Fly(oAircraft.GetCurrentRange());
    oAircraft.Land();
    REQUIRE_FALSE(oAircraft.IsCharging());

    // Check if the aircraft is charging after charging it.
    Charger oCharger;
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE(oAircraft.IsCharging());
}

// Test the Aircraft::GetCharger() method.
TEST_CASE( "Aircraft::GetCharger", )
{
    // Check if the charger is correct after charging the aircraft.
    Aircraft oAircraft(AircraftCompany::Alpha);
    oAircraft.Fly(oAircraft.GetCurrentRange());
    oAircraft.Land();
    Charger oCharger;
    oAircraft.ChargeAircraft(&oCharger, 0.1f);
    REQUIRE(oAircraft.GetCharger() == &oCharger);
}

