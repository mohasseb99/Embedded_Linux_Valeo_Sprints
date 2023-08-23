cmake_minimum_required(VERSION 3.9.1)

project(fileHandler
	VERSION 1.0
	LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)  ## here we need to write binary in bin directory

set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)    ## here we need to write library files in lib directory


message(${CMAKE_BINARY_DIR})  ## to print path of build

add_subdirectory(src)  

##add_library(WriteInFile STATIC include/WriteInFile.h library/WriteInFile.cpp)

##add_executable(requester src/requester.cpp)

##target_link_libraries(program WriteInFile)
