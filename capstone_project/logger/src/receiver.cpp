#include "../../lib/MessageQueue.h"
#include <csignal>
#include <iostream>

void cleanupAndExit(int signal);
MessageQueueReceiver* receiver = nullptr;

int main() {
    try { 
    	// to capture ctrl+c signal and calling function before terminating
    	signal(SIGINT, cleanupAndExit);
        // Receiver creates the message queue
        receiver = new MessageQueueReceiver("/maths_logger", 0);

        char received_message[1024];
        unsigned int priority;
        for(long long i = 0; i < 5000000000; i++){}
        int result = 1;
        while(1){
        	result = receiver->ReceiveMessageAsync(received_message, sizeof(received_message), &priority);
        	// checking if result bigger than zero that means we received a message so we print it
		if(result > 0) {
			int i = 0;
			// as in message queue if we send a message that is smaller than the last one it prints the remaining of the last message so we use ? as delimeter
			while(received_message[i] != '?'){
				std::cout << received_message[i];
				i++;
			}
			std::cout << std::endl;
		}
		// delay to simulate as we are doing another tasks
		for(int i = 0; i < 500000000; i++){}
	}
	
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with an error code
    }

    return 0;
}

// it is call back function when signal is captured it will call this function to clean up resources
void cleanupAndExit(int signal) {
    receiver->cleanUpResources();
    // Exit the program
    exit(0);
}

