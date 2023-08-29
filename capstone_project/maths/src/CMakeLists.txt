# Include the 'lib' directory for the message queue library
# As lib is not subdirectory of src we need to specifiy path to binary directory and source directory
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib ${CMAKE_BINARY_DIR}/lib)

# Create an executable for program
add_executable(maths
    sender.cpp
)

# Link the library to the executable
target_link_libraries(maths MessageQueueLibrary)
