# @file:    avr.toolchain.cmake
# @author:  sramos
# @brief:	Defines toolchain for AVR build files

# avr.toolchain.cmake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSS_COMPILING 1)

# Define the MCU
set(MCU "atmega328p" CACHE STRING "AVR MicroController")

# Path to AVR toolchain
set(AVR_TOOLCHAIN_PATH "/usr/bin")

# Build things
set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN_PATH}/avr-gcc")
set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN_PATH}/avr-g++")
set(CMAKE_OBJCOPY "${AVR_TOOLCHAIN_PATH}/avr-objcopy")
set(CMAKE_OBJDUMP "${AVR_TOOLCHAIN_PATH}/avr-objdump")
set(CMAKE_SIZE "${AVR_TOOLCHAIN_PATH}/avr-size")

# Set AVR-specific flags
set(CMAKE_C_FLAGS "-mmcu=${MCU} -Os -Wall -Wextra" CACHE STRING "C Flags")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -Os -Wall -Wextra -std=c++11" CACHE STRING "C++ Flags")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU} -Wl,--gc-sections" CACHE STRING "Linker Flags")

