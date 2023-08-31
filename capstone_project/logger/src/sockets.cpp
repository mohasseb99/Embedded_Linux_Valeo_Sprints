#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "../inc/logger.h"
#include "../inc/sockets.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>

namespace fs = std::filesystem;

int socket_init(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  // AF_INET --> IPV4  SOCK_STREAM, 0 --> for tcp connection
    if (serverSocket == -1) {
        log_msg("5Error: Logger: Failed to create socket?");
        return -1;
    }

    sockaddr_in serverAddress;                     // to store server address info
    serverAddress.sin_family = AF_INET;            // IPV4
    serverAddress.sin_addr.s_addr = INADDR_ANY;    // bind to all network interfaces
    serverAddress.sin_port = htons(8080);          // bind to port 8080 and convert it to binary format

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {  // bind the socket to server address
        log_msg("5Error: Logger: Failed to bind socket?");
        return -1;
    }

    if (listen(serverSocket, 10) == -1) {   // listen to incoming connections, maximum 10 in queue
        log_msg("5Error: Logger: Failed to listen for connections?");
        return -1;
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
    log_msg("1Trace: Logger: Handling client connection?"); // Handle the client connection
    
    std::string logDirectory = "../../../";   // Specify the directory containing log files
    std::string logFilePattern = "log_.*\\.txt"; // Define a pattern for log file names "log_*.txt"
    std::regex pattern(logFilePattern);
    std::vector<fs::path> filePaths;  // Create a vector to store file paths
    
    for (const auto& entry : fs::directory_iterator(logDirectory)) {   // Iterate through files in the directory
        if (entry.is_regular_file()) {   // Checks if the current directory entry is a regular file not a directory
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, pattern) ) {  // Check if the file name matches the pattern
                filePaths.push_back(entry.path()); // add them to vector to sort them
            }
        }
    }
    
    // sorting files related to their names
    std::sort(filePaths.begin(), filePaths.end(), [](const fs::path& a, const fs::path& b) {
        // Sort by filename (lexicographical order)
        return a.filename().string() < b.filename().string();
    });
    
    for (const auto& filePath : filePaths) {
    	log_msg("1Trace: Logger: Reading log file?");
        std::string filename = filePath.filename().string();
            
        send_msg(clientSocket, strdup((filename+"\n").c_str()));
        std::ifstream logFile(filePath.string());  // Open and read the log file
        std::string line;	
        while (std::getline(logFile, line)) {
            line += "\n";
            if(send_msg(clientSocket, strdup(line.c_str()) ) == -1){
    	        log_msg("5Error: Logger: Failed to send log?");
    		return;
    	    }
        }
        logFile.close();  
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
