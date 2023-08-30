#include "../inc/logger.h"
#include <string>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

static int getFileSize(const std::string &filename);
char* logger_file;

void init_logger() {

	// we get time then make a file name with timestamp.txt when first run and give name to logger	
	std::time_t currentTime = std::time(nullptr);
	char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", std::localtime(&currentTime));
	std::string filename = "../../" + std::string(timestamp) + ".txt";
	logger_file = strdup(filename.c_str());
	std::cout << logger_file << std::endl;
	
	logging::add_file_log(
        	keywords::file_name = logger_file,
        	keywords::open_mode = (std::ios::out | std::ios::app) // Append to existing file
        );
	
	logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::trace
    	);
}

void log_msg(char* msg){
	// I tried to make rotation file using boost but it gives me err I can not solve
	if (getFileSize(std::string(logger_file)) >= 1024) {  // if size >= 1024 we create a new logger file
		init_logger();
	}
	// I tried to make timestamp by boost but It gives me errors
	// to get current timestamp to add in message
	std::time_t currentTime = std::time(nullptr);
	char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", std::localtime(&currentTime));
	
	char severity = *msg;  // using first character to know severity level
	std::string msg_sent = std::string(timestamp) + " ";  // we make it to store message without first number and until delimeter ?
	int i = 1; 
	while(msg[i] != '?'){
		msg_sent += msg[i];
		i++;
	}
	
	if(severity == '1'){
		BOOST_LOG_TRIVIAL(trace) << msg_sent.c_str();
	}
	else if(severity == '2'){
		BOOST_LOG_TRIVIAL(debug) << msg_sent.c_str();
	}
	else if(severity == '3'){
		BOOST_LOG_TRIVIAL(info) << msg_sent.c_str();
	}
	else if(severity == '4'){
		BOOST_LOG_TRIVIAL(warning) << msg_sent.c_str();
	}
	else if(severity == '5'){
		BOOST_LOG_TRIVIAL(error) << msg_sent.c_str();
	}
	else if(severity == '6'){
		BOOST_LOG_TRIVIAL(fatal) << msg_sent.c_str();
	}
	boost::log::core::get()->flush();

}

int getFileSize(const std::string &filename) {
    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == 0) {
    	return fileStat.st_size;
    }
}
