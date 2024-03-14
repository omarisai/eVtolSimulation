# Table of Contents

- [Description](#description)
- [Problem Statement](#problem-statement)
- [Coding guidelines](#coding-guidelines)


# Description

This is a simple program to simulate the fly of 20 eVTOL aircrafts from different manufacturers
according to the given specifications in the [Problem Statement](#problem-statement) section,
the statistics resulting of the simulation will be printed at the end.

# Problem Statement

There are five companies developing eVTOL aircraft. The vehicle produced by each manufacturer has different characteristics. Six distinct properties are laid out in the below table:

| Company Name     | Cruise Speed (mph) | Battery Capacity (kWh) | Time to Charge (hours) | Energy use at Cruise (kWh/mile) | Passenger Count | Probability of fault per hour |
|------------------|--------------------|-----------------------|------------------------|---------------------------------|-----------------|-------------------------------|
| Alpha Company    | 120                | 320                   | 0.6                    | 1.6                             | 4               | 0.25                          |
| Bravo Company    | 100                | 100                   | 0.2                    | 1.5                             | 5               | 0.10                          |
| Charlie Company  | 160                | 220                   | 0.8                    | 2.2                             | 3               | 0.05                          |
| Delta Company    | 90                 | 120                   | 0.62                   | 0.8                             | 2               | 0.22                          |
| Echo Company     | 30                 | 150                   | 0.3                    | 5.8                             | 2               | 0.61                          |

You will simulate using these vehicle for 3 hours. Of course your simulation should take much less time than that. 20 total vehicles should be deployed, and a random number of each type of vehicle should be used (with the total between all five types being 20).

There are only three chargers available for all 20 vehicles! A single charger can only be used by one vehicle at a time. Assume the chargers can charge the batteries in the Time to Charge time listed for each vehicle. 

Keep track of the following statistics per vehicle type: 
- average flight time per flight
- average distance traveled per flight
- average time charging per charge session
- total number of faults
- total number of passenger miles. 
	For example, if there are 2 vehicles carrying 4 passengers on a vehicle that cruises 	for 1 hour at 100 mph, total number of passenger miles is 2 * 4 * 1 * 100 = 800.

Assume that:
- Each vehicle starts the simulation with a fully-charged battery
- Each vehicle instantaneously reaches Cruise Speed
- Each vehicle is airborne for the full use of the battery, and is immediately in line for the charger after running out of battery power.

Please include the statistics recorded during at least one run of the simulation in your submission.

Please do not hesitate to reach out to ask any questions about the problem! However, if you find yourself making an assumption that we haven’t explained explicitly, you may simply document your assumption. It’s interesting to us to hear what assumptions you made and why.

# Coding guidelines

Some coding guidelines to ensure consistency and readability. 

1. Braces: Place opening braces on a new line, aligned with the corresponding statement or declaration. For example:
   ```cpp
   if (condition)
   {
       // code here
   }
   ```

2. Variable Naming: Use camel case for variable names. Prefix variables with the appropriate type abbreviation, such as `ui` for `uint16_t`. For example:
   ```cpp
   uint16_t uiVariableName;
   MyClass oMyObject;
   MyEnum eMyVariable;
   ```

3. Indentation: Use consistent indentation for switch cases. Indent the case statements within the switch block. For example:
   ```cpp
   switch (variable)
   {
       case 1:
           // code here
           break;
       case 2:
           // code here
           break;
       default:
           // code here
           break;
   }
   ```

4. Member Variables: Prefix member variables in classes and structures with 'm'. For example:
   ```cpp
   class MyClass
   {
   private:
       int mVariable;
   };
   ```

5. Getters: Expose getters using inline functions. For example:
   ```cpp
   class MyClass
   {
   public:
       inline int getVariable() const { return mVariable; }
   private:
       int mVariable;
   };
   ```

6. Comments: Use Doxygen-style comments to document your code. Provide clear and concise explanations for classes, functions, and member variables. For example:
   ```cpp
   /**
    * @brief This is a class that represents a MyClass.
    *
    * This class provides functionality for ...
    */
   class MyClass
   {
   public:
       /**
        * @brief Get the value of the variable.
        *
        * @return The value of the variable.
        */
       inline int getVariable() const { return mVariable; }
   private:
       int mVariable; ///< The value of the variable.
   };
   ```
