#include "../inc/semaphore.h"
#include <iostream>
#include <fcntl.h>

sem_t* SEMAPHORE_init(){
	sem_t* semaphore = sem_open(SEMAPHORE_PATH, O_CREAT, 0777, 1);  // open sem_file with these permissions and initial value = 1
	if (semaphore == SEM_FAILED) { // if failed
      		perror("sem_open");
      		std::cout << "unable to create a sema, errno=" << errno << "\n";
        	return SEM_FAILED;
    	}
    	return semaphore;
}


