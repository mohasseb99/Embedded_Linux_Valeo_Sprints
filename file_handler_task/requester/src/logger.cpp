#include "../inc/logger.h"
#include <string>

void init_logger() {
	logging::add_file_log(
        	keywords::file_name = LOGGER_PATH,
        	keywords::open_mode = (std::ios::out | std::ios::app) // Append to existing file
        );
	
	logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::trace
    	);
}

void log_msg(char* sevrity, char* msg){
	if(std::string(sevrity) == "trace"){
		BOOST_LOG_TRIVIAL(trace) << msg;
	}
	else if(std::string(sevrity) == "debug"){
		BOOST_LOG_TRIVIAL(debug) << msg;
	}
	else if(std::string(sevrity) == "info"){
		BOOST_LOG_TRIVIAL(info) << msg;
	}
	else if(std::string(sevrity) == "warning"){
		BOOST_LOG_TRIVIAL(warning) << msg;
	}
	else if(std::string(sevrity) == "error"){
		BOOST_LOG_TRIVIAL(error) << msg;
	}
	else if(std::string(sevrity) == "fatal"){
		BOOST_LOG_TRIVIAL(fatal) << msg;
	}
}
