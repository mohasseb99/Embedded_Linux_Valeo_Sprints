#ifndef SOCKEET

#define SOCKET

int socket_init();
void handleClient(int clientSocket);
void listenForConnections(int serverSocket);
int send_msg(int clientSocket, char* msg);

#endif
