#include "../inc/FIFO.h"
#include "../inc/logger.h"
#include "iostream"

using namespace std;
 

void FIFO_init(int& fifo_fd){
	int flags;
	// check if FIFO file is already exist
	struct stat st;
    	if (stat(FIFO_PATH, &st) == 0) {
    		log_msg("info", "info: FIFO file is already exist");
        }
        else{
        	if(mkfifo(FIFO_PATH, 0666) != 0){ 	// Creating the named file(FIFO)  // if not 0 returned that means that failed to make fifo
			log_msg("fatal", "Fatal: unable to create FIFO");
			exit(1);
		}
        } 
    
	fifo_fd = open(FIFO_PATH, O_RDONLY);   // Open FIFO for read only
	if(fifo_fd == -1){   // if fifo_fd is equal to -1 that means we can not open file
		log_msg("fatal", "Fatal: can not open FIFO");
		exit(1);
	}
	// we need to get current flags of file then clear O_NONBLOCK so when trying to read fifo we block the calling until some data becomes available.
	/* get current flag settings of file                      */
        if ((flags = fcntl(fifo_fd,F_GETFL)) == -1) {
        	log_msg("error", "Error: can not get flag of FIFO");
        }
        /* clear O_NONBLOCK  and reset file flags                 */
        flags &= ~(O_NONBLOCK);
        if ((fcntl(fifo_fd,F_SETFL,flags)) == -1) {
        	log_msg("error", "Error: can not clear non blocking flag FIFO");
        } 
}

