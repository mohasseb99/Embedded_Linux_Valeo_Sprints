#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "../inc/sockets.h"


int main(int argc, char* argv[]) {
    bool flag = 1;
    
    if(argc == 2){
        if( isValidIPv4 ( std::string(argv[1]) ) ){  // checking if given input is valid IPV4
            int clientSocket = socket_init(argv[1]);
            
            // Receive and process data from the server
	    char buffer[1024];
	    int bytesRead = 99;  // initial value bigger than zero to start receiving
	    int totalBytesReceived = 0; // to track total bytes received
	    while(bytesRead != 0){
	    	bytesRead = recv(clientSocket, buffer + totalBytesReceived, sizeof(buffer) - totalBytesReceived, 0);	
    		if (bytesRead == -1) {
        	    std::cerr << "Error receiving data" << std::endl;
	            close(clientSocket);
	            break;
    		}
	    	else if(bytesRead == 0){
	    	    std::cout << "server closed socket and ended connection" << std::endl;
		    // Close the client socket
		    close(clientSocket); 
		    break;
		}
		totalBytesReceived += bytesRead;
		
		// Check if you have received the complete message
	        // For example, if messages are newline-terminated if we do not do that it will print byte by byte so we want to print until delimeter which is \n
	        while (true) {
	            size_t newlinePos = 0;
	            for (size_t i = 0; i < totalBytesReceived; ++i) {
	                if (buffer[i] == '\n') {
	                    newlinePos = i;
	                    break;
	                }
	            }
         
	            if (newlinePos > 0) {
	                // Process the complete message
	                std::cout << "Received message: " << std::string(buffer, buffer + newlinePos) << std::endl;

	                // Shift the remaining data to the beginning of the buffer
	                totalBytesReceived -= (newlinePos + 1);
	                memmove(buffer, buffer + newlinePos + 1, totalBytesReceived);
	            } else {
	                // we do not have complete message(until delimeter) so we go to receive
	                break;
	            }
	        }
	    }
	    
	    
        }
        else{
            flag = 0;
        }
    }
    else{
        flag = 0;
    }
    
    if(flag == 0){
    	std::cout << "Usage: " << argv[0] << " valid IPV4 ex: 'num.num.num.num' \n";
    }
    
    return 0;
}

