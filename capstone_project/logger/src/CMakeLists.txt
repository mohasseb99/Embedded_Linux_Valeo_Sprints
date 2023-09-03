# Set the path to your Boost library directory
set(BOOST_ROOT /home/mahmoud/boost)

# Disable searching for Boost in default system paths
set(Boost_NO_SYSTEM_PATHS TRUE)

# Specify the Boost include and library directories
#set(Boost_INCLUDE_DIR ${BOOST_ROOT})
#set(Boost_LIBRARY_DIRS ${BOOST_ROOT})

# Find the Boost package
find_package(Boost REQUIRED COMPONENTS log log_setup date_time system thread)


# Include the 'lib' directory for the message queue library
# As lib is not subdirectory of src we need to specifiy path to binary directory and source directory
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib ${CMAKE_BINARY_DIR}/lib)

add_library(LOGGERSlib ../inc/logger.h logger.cpp)
add_library(SOCKETSlib ../inc/sockets.h sockets.cpp)

# Include the Boost headers
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

message(${Boost_INCLUDE_DIR})
message(${Boost_LIBRARY_DIRS})

# Link against the Boost libraries
target_link_libraries(LOGGERSlib PUBLIC Boost::log Boost::log_setup Boost::date_time)

# Create an executable for program
add_executable(logger
    receiver.cpp
)

# Link the library to the executable
target_link_libraries(logger MessageQueueLibrary pthread rt LOGGERSlib SOCKETSlib)
