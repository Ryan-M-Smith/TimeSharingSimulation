#
# Filename: CMakeLists.txt
# Description: CMake build script for the project
# Created: 3/3/25
#

cmake_minimum_required(VERSION 3.20)
project(
        Simulation
        DESCRIPTION "A simple simulation of a time-sharing system with a round-robin scheduler. CS-320 Project 1."
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_REQUIRED_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(PROJ_INCLUDE_DIR include/)  # Set the compiler include path
set(PROJ_SRC_DIR src/)          # Set the source file path

# Fetch all source files
file(GLOB SOURCES ${PROJ_SRC_DIR}/*.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJ_INCLUDE_DIR})

# Add a way to clean all build files
add_custom_target(clean-all
	COMMAND rm -rf CMakeCache.txt CMakeFiles *.cmake ${PROJECT_NAME} Makefile
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)