#ifndef SOCKEET

#define SOCKET

#include <arpa/inet.h>

int socket_init();
void handleClient(int clientSocket);
void listenForConnections(int serverSocket);
int send_msg(int clientSocket, char* msg);

#endif
