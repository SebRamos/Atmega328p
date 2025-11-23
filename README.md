# Atmega328p
This repositroy containts various software-level drivers and interfaces for the ATMega328p. It's purpose is manually implement utilities and libraries that communicate directly with hardware and registers for the purposes of being used by an application at the 'higher-level'. 

This project assumes a stand-alone ATMega328p is used and programmed directly with an aftermarket programmer.

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

## Developement
Various 'To-Dos' are declared in the source but otherwise, a full library the can utilize most of what the ATMega328p can do is sought after.
