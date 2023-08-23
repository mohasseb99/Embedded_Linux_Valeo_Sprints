add_library(FIFOlib STATIC ../inc/FIFO.h FIFO.cpp)

add_executable(requester requester.cpp)

target_link_libraries(requester FIFOlib)
