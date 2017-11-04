# RIT-SPEX-HAB-ComputerVision
This code provides horizon detection functionality for RIT SPEX HAB weather balloon.

## Build Instructions
Use the following commands to build the software in this repository.

* mkdir RIT-SPEX-HAB-ComputerVision/build
* cd RIT-SPEX-HAB-ComputerVision/build
* cmake ..
* make

## Running the Executable
Use the following commands to start the horizon detection application.

Please note certain aspects of program execution assume the application is
running out of RIT-SPEX-HAB-ComputerVision/build/bin. Take this into account 
if you are going to add the executable to a init service (eg. init.d).

* cd RIT-SPEX-HAB-ComputerVision/build/bin
* ./RIT\_SPEX\_Horizon \<cam1Index\> \<cam2Index\>

Replace \<cam1Index\> and \<cam2Index\> with respective indecies.

Note: if no camera index arguments are supplied, defaults are 0 and 1.
