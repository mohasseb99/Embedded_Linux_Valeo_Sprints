#include <iostream>
#include <string>
#include "../inc/FIFO.h"

using namespace std;


extern int fd;    // to store file descriptor as we need it in multiple functions
  
int main(int argc, char** argv)
{
	if(argc == 1){ // checking if user enters any wrong input // input is fh only
    		cout << "done\n";
    		fd = FIFO_init();   // file discreptor to store file of fifo
        	if(fd == -1){    // if fd = -1 initialization fild else it has file decriptor 
        		cout << "initialization failed\n";
        		return 0;
        	}
        	char command[2][150];  // to store what returned from fifo  // I made it 2d array as we will store command and path
        	int i = 0;
        	while(1){
			while( read(fd, command[i], sizeof(command)) > 0 ){
				cout << "command:  \n" << command[i] << "\n";
				i++;	
			}

			i = 0;
		}
    			
    	}
    	else{
    		cout << "this program does not accept any argument\n";
    	}
    	
    	return 0;
}


