# Atmega328p
This repository containts various software-level drivers and interfaces for the ATMega328p. It's purpose is manually implement utilities and libraries that communicate directly with hardware and registers for the purposes of being used by an application at the 'higher-level'. 

## Developement
Various 'To-Dos' are declared in the source but otherwise, a full library the can utilize most of what the ATMega328p can do is sought after. As stated previously, a hardware-abstraction layer (HAL) similar to STM that covers most of the hardware drivers within the system-on-chip (SoC) is the end goal.

## Tools
The following tools are commonly used in this project.
| Tool | Purpose |
|---|---|
| avr-gcc | Provides the toolkit for building binaries from source code and linking object files    |
| CMake   | Bundles the AVR toolchain, and creates the makefile with project configs for building   |
| avrdude | Tool used to communicate with programming devices for flashing the SoC                  |
| minicom / Putty | Serial communication device used to provide debug prints from the SoC           |

## CMake Build
**Run the following commands at the project root to build the project**

* This command will create the build directory and configure the toolchain
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=avr.toolchain.cmake
```

* This command will recompile the source and create a .hex file in the 'build' directory
```
cmake --build build
```

* Optionally, you may manually 'Fully Clean' a build by deleting the build directory and re-running both build commands
```
rm -rf build/
```

* Optionally, you may 'Partially Clean' a build by re-running the compile command with the 'clean' flag
```
cmake --build build --clean-first
```

## Programming
Various programmers can be used to flash the SoC. The AVRdude tool is mainly used write a .hex file created by the CMake build configuration into flash. The program shell script may be used to invoke AVRdude with an Arduino programmer.
```
./program.sh
```
Or optionally,
```
avrdude -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:build/AVRProj.hex:i
```