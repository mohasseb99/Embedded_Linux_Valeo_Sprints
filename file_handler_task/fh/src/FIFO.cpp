#include "../inc/FIFO.h"
#include "iostream"

using namespace std;

int fd;

int FIFO_init(){
	int flags;
	char * myfifo = FIFO_PATH; 
	if(mkfifo(myfifo, 0666) != 0){ 	// Creating the named file(FIFO)
		cout << "unable to create a fifo, errno=" << errno << "\n";
		return -1;
	}
	signal(SIGINT,FIFO_clear);   // when ^c is pressed we delete FIFO file
	fd = open(myfifo, O_RDONLY);   // Open FIFO for write only
	if(fd == -1){   // if fd is equal to -1 that means we can not open file
		cout << "can not open fifo\n";
		return -1;
	}
	// we need to get current flags of file then clear O_NONBLOCK so when trying to read fifo we block the calling until some data becomes available.
	/* get current flag settings of file                      */
        if ((flags = fcntl(fd,F_GETFL)) == -1) {
        	cout << "can not get file flags\n";
        	return -1;
        }
        /* clear O_NONBLOCK  and reset file flags                 */
        flags &= ~(O_NONBLOCK);
        if ((fcntl(fd,F_SETFL,flags)) == -1) {
        	cout << "can not clear O_NONBLOCK\n";
        	return -1;
        } 
        return fd;
}

void FIFO_clear(int signum){
        cout << "Caught signal\n";
 	close(fd);
 	unlink(FIFO_PATH);           
        exit(1);

}
