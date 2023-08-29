#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../inc/shm.h"
#include "../inc/logger.h"

void SHM_init(int& shm_fd, char*& shm_mem, int& size){
	shm_fd = shm_open(SHM_PATH, O_CREAT | O_RDWR, 0666);   // open a shared memory file if created and if not create one with these permissions
	
	if (shm_fd == -1) {   // checking if succedded to open or not shared memory file
        	log_msg("fatal", "Fatal: can not create shared memory file");
        	exit(1);
    	}
    	
    	if (ftruncate(shm_fd, size) == -1) {    // making size of shared memory file to size and checking if succeeded or not
        	log_msg("fatal", "Fatal: can not allocate size of shared memory file");
        	exit(1);
    	}
    	
    	shm_mem = static_cast<char*>(mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0));   // mmap return void* so we cast it to char *, we make shm file to be write only from this program and shared between other processes 
    	
    	if (shm_mem == MAP_FAILED) {  // checking if failed mapping
        	log_msg("fatal", "Fatal: can not map shared memory file");
        	exit(1);
    	}
}

