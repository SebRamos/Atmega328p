# @file:    CMakeLists.txt
# @author:  sramos
# @brief:   Configures CMake build settings and processes

cmake_minimum_required(VERSION 3.0)
project(AVRProj C CXX)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex 
    COMMENT "Converting .elf to .hex"
)
