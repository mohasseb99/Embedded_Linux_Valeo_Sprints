#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <ctime>
#include "../inc/FIFO.h"
#include "../inc/semaphore.h"
#include "../inc/shm.h"
#include "../inc/commands.h"
#include "../inc/logger.h"


using namespace std;

//sem_t* semaphore;

int main(int argc, char** argv)
{
	init_logger();
	if(argc == 1){ // checking if user enters any wrong input // input is fh only
		log_msg("trace", "Trace: Command is correct");
		
    		// initialization of FIFO
    		int fifo_fd;          // to store file descriptor of FIFO 
    		FIFO_init(fifo_fd);   // here we pass fifo_fd by refrence and if managed to access FIFO file it will has value
        	
        	//semaphore = SEMAPHORE_init();
        	//if(semaphore == SEM_FAILED){ return 0;}
		
		// initialization of shared memory
		int shm_fd;         // to store shared memory file descriptor
		char* shm_mem;	    // to access shared memory byte by byte
		int size = 1024;    // to declare size to 1024
		SHM_init(shm_fd, shm_mem, size);   // here we pass arguments by refrence and if function is run successfully we will have value of shm_fd and shm_mem
 		log_msg("info", "info: shared memory file created successfully");   
    		
        	char command[2][250];  // to store what returned from fifo it will store command and path
        	
        	int i = 0;	       // to iterate through commands
        	while(1){
        		i = 0;         // every iteration we reinitialize to zero
        	//	sem_wait(semaphore);
        	//	cout << "took" << endl;
			//for(int j = 0; j < 600000; j++){}
			while(read(fifo_fd, command[i], sizeof(command)) > 0 ){		// to read FIFO until end of file
				char msg[250] = "Trace: Command is correct ";
				log_msg("info", strcat(msg, command[i]));
				cout << command[i] << "\n";
				i++;
			}
			if(i == 2){     // as we read from FIFO two times then pass command and path to be executed
				std::string res = commandExecute(command);	// here we pass command to be executed and store result in string
				strcpy((char *)shm_mem, res.c_str());  		// we copy string to shared memory
				boost::log::core::get()->flush();	
			}
		//	sem_post(semaphore);
		}
    			
    	}
    	else{  // if user passed any argument 
    		cout << "this program does not accept any argument\n./fh to run it\n";
    		log_msg("fatal", "fatal: user entered argument");
    		boost::log::core::get()->flush();
    	}
    	
    	return 0;
}

