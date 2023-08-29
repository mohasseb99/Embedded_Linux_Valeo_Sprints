#include <iostream>
#include <string>
#include "../inc/FIFO.h"
#include "../inc/semaphore.h"
#include "../inc/shm.h"
#include "../inc/logger.h"


using namespace std;

 
int main(int argc, char** argv)
{
	init_logger();
	bool flag = 1; // here that flag is initialized with 1 if input is not what we want we set it 0
	if(argc < 3 || argc > 3){ // here we check if user enters 2 inputs after app name
		log_msg("error", "Error: user entered wrong number of arguments");
		flag = 0;
	}
    	else{
    		if(string(argv[1]) == "r" || string(argv[1]) == "ls"){ // checking if command is -r to read specific file or -ls to list files in directory
    			log_msg("trace", "Trace: user entered correct number of arguments and correct command");
    			// initialization of fifo
    			int fifo_fd;		// to store file descriptor of FIFO 
    			FIFO_init(fifo_fd);   // here we pass fifo_fd by refrence and if managed to access FIFO file it will has value
        		
        		//sem_t* semaphore = SEMAPHORE_init();
        		
        		// initialization of shared memory
			int shm_fd;         // to store shared memory file descriptor
			char* shm_mem;	    // to access shared memory byte by byte
			int size = 1024;    // to declare size to 1024
			SHM_init(shm_fd, shm_mem, size);   // here we pass arguments by refrence and if function is run successfully we will have value of shm_fd and shm_mem
			log_msg("info", "info: shared memory file created successfully");   
        		//if (semaphore == SEM_FAILED) {return 0;}
        		
        		//sem_wait(semaphore);
        		//cout << "took1" << endl;
        		// sending arguments by FIFO
        		FIFO_send(fifo_fd, argv);
        		log_msg("trace", "Trace: sending arguments using FIFO");
        		//sem_post(semaphore);
        		//cout << "leave 1" << endl;
        		
        		//sem_wait(semaphore);
        		//cout << "took2" << endl;
        		// wait until server complete writing to shared memory
        		for(int i = 0; i < 600000000; i++){}
        		printf("%s", shm_mem);  // printing returned from shared
        		log_msg("trace", "Trace: recieved from shared memory");
        		cout << endl;
        		//sem_post(semaphore);
        		//cout << "leave2" << endl;
        		
        		//cout << "took semaphore" << endl;
        		//sem_close(semaphore);
    		}
    		else{
    			flag = 0; // if enters here that means that command is not r or ls
    		}
    	}
    	if(flag == 0){ // if user enters wrong input we will print commands that we support
    		cout << "commands available is:\nr : to read specific file and provide path of file\n";
    		cout << "ls : to list all files in this directory and provide path of directory\n";
    	}
    	
    	return 0;
}



