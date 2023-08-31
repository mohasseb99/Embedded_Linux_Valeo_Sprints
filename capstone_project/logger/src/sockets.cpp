#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "../inc/logger.h"
#include "../inc/sockets.h"

int socket_init(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  // AF_INET --> IPV4  SOCK_STREAM, 0 --> for tcp connection
    if (serverSocket == -1) {
        log_msg("5Error: Logger: Failed to create socket?");
    }

    sockaddr_in serverAddress;                     // to store server address info
    serverAddress.sin_family = AF_INET;            // IPV4
    serverAddress.sin_addr.s_addr = INADDR_ANY;    // bind to all network interfaces
    serverAddress.sin_port = htons(8080);          // bind to port 8080 and convert it to binary format

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {  // bind the socket to server address
        log_msg("5Error: Logger: Failed to bind socket?");
    }

    if (listen(serverSocket, 5) == -1) {   // listen to incoming connections, maximum 5 in queue
        log_msg("5Error: Logger: Failed to listen for connections?");
    }

    log_msg("3Info: Logger: Listening on port 8080?");
    
    // Create a separate thread for listening and accepting connections
    std::thread(listenForConnections, serverSocket).detach();
    log_msg("3Info: Thread is created to accept connections?");
    	
    return serverSocket;
}

void listenForConnections(int serverSocket) {
    while (true) {
        sockaddr_in clientAddress;   // to store client socket info
        socklen_t clientAddrLen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrLen);  // blocking until conection come
 
        if (clientSocket == -1) {  
            log_msg("5Error: Logger: Failed to accept connection?");
            continue; // Continue to the next iteration
        }

        log_msg("3Info: Logger: client connected?");
   
        // Create a new thread to handle the client
        std::thread(handleClient, clientSocket).detach();
        log_msg("1Trace: Logger: Thread created to handle connection?");
    }
}

void handleClient(int clientSocket) {
    // Handle the client connection
    log_msg("1Trace: Logger: Handling client connection?");
    for(int i = 0; i < 3; i++){
    	if(send_msg(clientSocket, "Ana ally bb3t aywa\n") == -1){
    		return;
    	}
    	for(int j = 0; j < 5000000; j++){}
    }
    // Close the client socket
    close(clientSocket);
    log_msg("1Trace: Logger: client was handled and socket is closed for client?");
}

int send_msg(int clientSocket, char* msg){
    int messageLength = strlen(msg);
    int bytesSend = send(clientSocket, msg, messageLength, 0); 
    if (bytesSend == -1) {
        log_msg("5Error: Logger: Failed to send data?");
	close(clientSocket);
	log_msg("3Info: Logger: Socket with client is closed?");
	return -1;
    }
    return bytesSend;
}
