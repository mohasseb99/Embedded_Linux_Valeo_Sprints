#include <fcntl.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FIFO_PATH "../../../FIFO"  // to make it in build directory 

int FIFO_init();
void FIFO_send(int fd, char** argv);

