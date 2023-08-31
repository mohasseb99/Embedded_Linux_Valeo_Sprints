add_library(SOCKETSlib ../inc/sockets.h sockets.cpp)

# Create an executable for program
add_executable(nlogger
    native_logger.cpp
)

# Link the library to the executable
target_link_libraries(nlogger SOCKETSlib)
