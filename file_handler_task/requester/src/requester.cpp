#include <iostream>
#include <string>

using namespace std;
 
int main(int argc, char** argv)
{
	bool flag = 1; // here that flag is initialized with 1 if input is not what we want we set it 0
	if(argc < 3 || argc > 3){ // here we check if user enters 2 inputs after app name
		flag = 0;
	}
    	else{
    		if(string(argv[1]) == "-r"){ // checking if command is -r to read specific file
    			cout << "command read\n";
    		}
    		else if(string(argv[1]) == "-ls"){ // checking if command is -ls to read specific file
    			cout << "command ls\n";
    		}
    		else{
    			flag = 0; // if enters here that means that command is not -r or -ls
    		}
    	}
    	if(flag == 0){ // if user enters wrong input we will print commands that we support
    		cout << "commands available is:\n-r : to read specific file and provide path of file\n";
    		cout << "-ls : to list all files in this directory and provide path of directory\n";
    	}
    	
    	return 0;
}
