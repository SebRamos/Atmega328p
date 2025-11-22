# @file:    CMakeLists.txt
# @author:  sramos
# @brief:   Configures CMake build settings and processes

cmake_minimum_required(VERSION 3.0)
project(AVRProj C CXX)


add_executable(${PROJECT_NAME}.elf 
    src/main.cpp)

