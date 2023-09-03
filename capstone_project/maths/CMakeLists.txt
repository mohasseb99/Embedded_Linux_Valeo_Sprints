cmake_minimum_required(VERSION 3.9.1)

project(Maths
	VERSION 1.0
	LANGUAGES CXX)

# Define the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the target architecture to ARM for Raspberry Pi 4
set(CMAKE_SYSTEM_PROCESSOR arm)

# Cross-compile settings for Raspberry Pi 4
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER "/home/mahmoud/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "/home/mahmoud/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++")

# Set the output directories for binaries and libraries
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)  ## here we need to write binary in bin directory
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)    ## here we need to write library files in lib directory

message(${CMAKE_BINARY_DIR})  ## to print path of build

# Include the 'src' directory for the main program
add_subdirectory(src)
