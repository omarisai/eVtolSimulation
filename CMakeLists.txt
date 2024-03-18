
cmake_minimum_required(VERSION 3.5)
project(simulation)

# Include paths
include_directories(${PROJECT_SOURCE_DIR})

add_executable(test_simulation
    main.cpp
    aircrafts/Aircraft.cpp
    aircrafts/AircraftType.cpp

    worlds/SimulationWorld.cpp
    worlds/Charger.cpp

    # Simple world
    worlds/SimpleWorld/World.cpp
    worlds/SimpleWorld/Event.cpp
)
