# Find the Boost package
find_package(Boost REQUIRED COMPONENTS log log_setup)

add_library(FIFOlib STATIC ../inc/FIFO.h FIFO.cpp)
add_library(SHMlib STATIC ../inc/shm.h SHM.cpp)
add_library(SEMAPHORElib STATIC ../inc/semaphore.h semaphore.cpp)
add_library(COMMANDSlib STATIC ../inc/commands.h commands.cpp)
add_library(LOGGERSlib STATIC ../inc/logger.h logger.cpp)

target_include_directories(LOGGERSlib PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(LOGGERSlib PUBLIC Boost::log_setup Boost::log)


add_executable(fh fileHandler.cpp)

target_link_libraries(fh FIFOlib SEMAPHORElib pthread SHMlib COMMANDSlib LOGGERSlib)
