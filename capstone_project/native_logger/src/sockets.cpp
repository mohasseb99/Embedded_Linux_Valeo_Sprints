#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "../inc/sockets.h"
#include <regex>
#include <string>

int socket_init(char* serverIP){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Create a socket  AF_INET-->IPV4  SOCK_STREAM, 0 --> TCP 

    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << errno << std::endl;
        exit(1);
    }

    // Server address information
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8080);             // Port number
    serverAddress.sin_addr.s_addr = inet_addr(serverIP); // Server IP address will be entered from user

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server" << errno << std::endl;
        close(clientSocket);
        exit(1);
    }

    std::cout << "Connected to server" << std::endl;
    return clientSocket;
}

bool isValidIPv4(const std::string &input) {
    std::regex ipPattern("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
    return std::regex_match(input, ipPattern);
}
