#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "../../../FIFO"

void FIFO_init(int& fifo_fd);
