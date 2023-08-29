#include <fcntl.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FIFO_PATH "../../../FIFO"  // to make it in build directory 

void FIFO_init(int& fifo_fd);

void FIFO_send(int& fifo_fd, char** argv);
