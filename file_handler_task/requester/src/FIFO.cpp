#include "../inc/FIFO.h"
#include <iostream>
#include <cstring>
#include "../inc/logger.h"


using namespace std;


void FIFO_init(int& fifo_fd){
	int flags;
	fifo_fd = open(FIFO_PATH, O_WRONLY);   // Open FIFO for write only
	if(fifo_fd == -1){   // if fd is equal to -1 that means we can not open file
		log_msg("Fatal", "fatal: can not open FIFO");
		exit(1);
	} 
	log_msg("info", "info: FIFO is opened");
}

void FIFO_send(int& fifo_fd, char** argv){
	write(fifo_fd, argv[1], strlen(argv[1])+1);
	log_msg("trace", "trace: sent first argument");
	for(int i = 0; i < 60000; i++);    // make delaying between writes
        write(fifo_fd, argv[2], strlen(argv[2])+1);
        log_msg("trace", "trace: sent second argument");
        close(fifo_fd);
        log_msg("info", "info: FIFO is closed");
}
