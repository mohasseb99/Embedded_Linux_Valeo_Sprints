#include "../inc/FIFO.h"
#include <iostream>
#include <cstring>


using namespace std;


int FIFO_init(){
	int flags;
	int fd;
	char * myfifo = FIFO_PATH; 
	fd = open(myfifo, O_WRONLY);   // Open FIFO for write only
	if(fd == -1){   // if fd is equal to -1 that means we can not open file
		cout << "can not open fifo\n";
		return -1;
	} 
        return fd;
}

void FIFO_send(int fd, char** argv){
	write(fd, argv[1], strlen(argv[1])+1);
        write(fd, argv[2], strlen(argv[2])+1);
        close(fd);
}
