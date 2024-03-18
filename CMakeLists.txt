
cmake_minimum_required(VERSION 3.5)
project(simulation)

# Include paths
include_directories(${PROJECT_SOURCE_DIR})

enable_testing()

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_definitions(-std=c++17)
set(COMMON_SOURCES
    aircrafts/Aircraft.cpp
    aircrafts/AircraftType.cpp

    worlds/SimulationWorld.cpp
    worlds/Charger.cpp

    # Simple world
    worlds/SimpleWorld/World.cpp
    worlds/SimpleWorld/Event.cpp
)
set(TARGET_SOURCES main.cpp)
set(TEST_SOURCES
    aircrafts/test_Aircraft.cpp
    aircrafts/test_AircraftType.cpp
)

add_executable(simulation ${COMMON_SOURCES} ${TARGET_SOURCES})
add_executable(test_simulation ${COMMON_SOURCES} ${TEST_SOURCES})

target_link_libraries(test_simulation PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(test_simulation)
