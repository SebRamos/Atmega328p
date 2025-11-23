# Atmega328p
Some utilities for the Atmega 328p.

# CMake Build
Run the following commands at the project root to build the project:

Run this command when adding new files to the project:
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=avr.toolchain.cmake

Run this command whenever files are edited and/or modified:
cmake --build build
