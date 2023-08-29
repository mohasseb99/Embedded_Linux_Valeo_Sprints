#include <iostream>
#include <sys/stat.h>
#include <string>
#include <string>
#include "../inc/commands.h"
#include "../inc/logger.h"

// to check if file of the given path existed or not
bool fileExists(char* filePath) {
    struct stat info;
    if (stat(filePath, &info) != 0){
    	return false;
    }
    return (info.st_mode & S_IFDIR) == 0; 
}

// to check if given path is directory and existed or not
bool directoryExists(char* dirPath) {
	struct stat info;
        if (stat(dirPath, &info) != 0) {
        	return false; // Error or path doesn't exist
    	}
   	return (info.st_mode & S_IFDIR) != 0; // check if path is directory or not
} 

// function take command to execute then return result
std::string commandExecute(char commands[][250]){
	std::string result = "";  // to store the result of executing command
	
	if(std::string(commands[0]) == "r"){    // if command we want to exectue is r (read file) 
		if(fileExists(commands[1])){   // checking if given path is file or not
			log_msg("info", "info: File is exist");   
			std::string command = "cat " + std::string(commands[1]);   // command: cat file_path
			FILE* fp = popen(command.c_str(), "r");    // use pipe to read result of executing command, popen takes command as c_string 
			if (!fp) {   // if failed to open pipe
        			log_msg("error", "error: can not open pipe");   
        			result = "can not execute command\n";
        			log_msg("error", "error: can not execute command");   
        			return result;   // return that we can not execute command
    			}
    			char buffer[128];   // create a buffer to store what returned from pipe
			while (fgets(buffer, sizeof(buffer), fp) != nullptr) {   // read from pipe until it reached end of pipe
				log_msg("trace", "trace: read from pipe");   
				result += buffer;   // store buffer in result
			}
			
			pclose(fp);   // close pipe
			return result;	 
		}
		else{
			log_msg("error", "error: File needed to be accessed is not existed");   
			result += "File you are trying to access not existed\n";  // if command is r and path not exist we return that result
		}
	}
	else if(std::string(commands[0]) == "ls"){
		if(directoryExists(commands[1])){
			log_msg("info", "info: directory is existed");   
			std::string command = "ls -l " + std::string(commands[1]) + " | grep -v '^d'";  // command: ls -l directory_path | grep -v '^d' here we list all in that directory then filter to non-directory to return all types of files
			FILE* fp = popen(command.c_str(), "r");
			if (!fp) {
        			log_msg("error", "error: can not open pipe");
        			result = "can not execute command\n";
        			log_msg("error", "error: can not execute command");
        			return result;
    			}
    			char buffer[128];
			while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
				log_msg("trace", "trace: read from pipe");
				result += buffer;
			}
			pclose(fp);
			return result;	
		}
		else{
			log_msg("error", "error: Directory needed to be accessed is not existed");   
			result += "Directory you are trying to access not existed\n";
		}
	}
}

