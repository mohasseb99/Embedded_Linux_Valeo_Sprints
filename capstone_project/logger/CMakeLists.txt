cmake_minimum_required(VERSION 3.9.1)

project(logger
	VERSION 1.0
	LANGUAGES CXX)

# Define the C++ standard to use (e.g., C++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)  ## here we need to write binary in bin directory
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)    ## here we need to write library files in lib directory
message(${CMAKE_BINARY_DIR})  ## to print path of build

# Include the 'src' directory for the main program
add_subdirectory(src)
