add_library(FIFOlib STATIC ../inc/FIFO.h FIFO.cpp)

add_executable(fh fileHandler.cpp)

target_link_libraries(fh FIFOlib)
