#ifndef LOGGER

#define LOGGER

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>


namespace logging = boost::log;
namespace keywords = boost::log::keywords;


#define LOGGER_PATH "../../../run_logs.txt"

void init_logger();
void log_msg(char* sevrity, char* msg);

#endif
