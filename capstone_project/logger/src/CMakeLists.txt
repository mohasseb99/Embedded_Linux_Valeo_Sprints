# Find the Boost package
find_package(Boost REQUIRED COMPONENTS log log_setup date_time)


# Include the 'lib' directory for the message queue library
# As lib is not subdirectory of src we need to specifiy path to binary directory and source directory
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib ${CMAKE_BINARY_DIR}/lib)

add_library(LOGGERSlib ../inc/logger.h logger.cpp)
target_include_directories(LOGGERSlib PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(LOGGERSlib PUBLIC Boost::log_setup Boost::log Boost::date_time)

# Create an executable for program
add_executable(logger
    receiver.cpp
)

# Link the library to the executable
target_link_libraries(logger MessageQueueLibrary LOGGERSlib)
