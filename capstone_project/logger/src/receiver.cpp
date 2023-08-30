#include "../../lib/MessageQueue.h"
#include <csignal>
#include <iostream>
#include <fstream>
#include "../inc/logger.h"
#include <cstring>

#define CONFIG_PATH "../../../logger_conf.txt"
MessageQueueReceiver receivers[10];  // we make array of receviers as the maximum number of apps can logger deal with
int num_apps = 0;

void cleanupAndExit(int signal);
int readConfigs();
MessageQueueReceiver* receiver = nullptr;

int main() {
    init_logger();
    readConfigs();
    try { 
    	// to capture ctrl+c signal and calling function before terminating
    	signal(SIGINT, cleanupAndExit);
        
        for(int i = 0; i < num_apps; i++){
            log_msg("1Trace: Logger: Message queue opened from logger?");
        }
        char received_message[1024];
        unsigned int priority;
        int result = 1;
        while(1){
            for(int app = 0; app < num_apps; app++){
        	result = receivers[app].ReceiveMessageAsync(received_message, sizeof(received_message), &priority);
        	// checking if result bigger than zero that means we received a message so we print it
		if(result > 0) {
			int i = 0;
			log_msg(received_message);
		}
		// delay to simulate as we are doing another tasks
		for(int i = 0; i < 500000000; i++){}
	    }
	}
	
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with an error code
    }

    return 0;
}

// it is call back function when signal is captured it will call this function to clean up resources
void cleanupAndExit(int signal) {
    for(int i = 0; i < num_apps; i++){
    	receivers[i].cleanUpResources();
    	log_msg("1Trace: Logger: close message queue for application?");
    }
    // Exit the program
    exit(0);
}

int readConfigs(){
    std::ifstream file(CONFIG_PATH);

    // Check if the file is open
    if (!file.is_open()) {
        log_msg("5Error: Logger: can not open config file?");
        return 1;
    }
    log_msg("1Trace: Logger: opened config file successfully?");
    // Read and process each line in the file
    std::string line;
    std::getline(file, line); // as we know first line is comment we do not need it
    std::getline(file, line); // to read nnumber of apps
    try{
    	num_apps = std::stoi(line);
    	std::getline(file, line); // we do not need this line as it is comment
    	for(int i = 0; i < num_apps; i++){
    	    std::getline(file, line);
    	    char * path = strdup(line.c_str());  // to covert from const char * to char *
    	    MessageQueueReceiver rec(path, 0);
    	    receivers[i] = rec;
    	}
    } catch (const std::exception& e){
    	log_msg("5Error: Logger: failed to read number of applications?");
    }

    // Close the file when done (this happens automatically when the stream goes out of scope)
    file.close();
}

