#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#define FIFO_PATH "../../../FIFO"

int FIFO_init();
void FIFO_clear(int signum);

