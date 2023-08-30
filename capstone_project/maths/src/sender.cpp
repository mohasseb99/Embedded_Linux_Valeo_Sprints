#include "../../lib/MessageQueue.h"
#include <iostream>
#include <string>
#include <sstream>
#define MQ_PATH "/maths_logger"

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
bool isNumber(const std::string& str);
double calculate(const std::string& operation, const double& operand1, const double& operand2);

int main(int argc, char* argv[]) {
    try {
            // initialize sender message queue 
            MessageQueueSender sender(MQ_PATH);
        
	    bool flag = 0;
	    std::string operation; 
	    double operand1, operand2;
	    double result;
	
	    if(argc == 4){
	    	if(std::string(argv[1]) == "add" || std::string(argv[1]) == "sub" || std::string(argv[1]) == "mul" || std::string(argv[1]) == "div")		
	    	{
	    	    if( isNumber(std::string(argv[2])) && isNumber(std::string(argv[3])) ){
	    	    	sender.SendMessage("1MathsApp: Trace: user entered correct command?");  // we write number before message so logger can know which severity message is
	    	    	operation = argv[1];
	    	    	operand1 = std::stod(argv[2]);
	    	    	operand2 = std::stod(argv[3]);
	    	    	flag = 1;
	    	    }
	    	    else{
	    	    	sender.SendMessage("5MathsApp: Error: user does not entered numbers only after operation?"); // we use ? as delimeter so the reciver can know the end of the message
	    	    	flag = 0;
	    	    } 
	    	}
	    	else{
	    	    sender.SendMessage("5MathsApp: Error: user entered wrong operation?");
	    	    flag = 0;
	    	}
	    }
	    else if(argc == 2 && std::string(argv[1]) == "--help"){
	        sender.SendMessage("1MathsApp: Trace: user entered help?");
	    	flag = 0;
	    }
	    else{
	    	sender.SendMessage("5MathsApp: Error: user entered wrong number of arguments?");
	    	flag = 0;
	    }
	    
	    if (flag == 0) {
	        sender.SendMessage("3MathsApp: Info: print help for user?");
		std::cout << "Usage: " << argv[0] << " <operation ex: add, sub, mul, div> <operand1> <operand2>\n";
	    }
	    else{
	    	result = calculate(operation, operand1, operand2);
	    	std::cout << "Result = " << result << "\n";
	    	sender.SendMessage("3MathsApp: Info: print result for user?");
	    }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0; // Exit with an error code
    }

    
    return 0;
}

// Function to perform addition
double add(double a, double b) {
    return a + b;
}

// Function to perform subtraction
double subtract(double a, double b) {
    return a - b;
}

// Function to perform multiplication
double multiply(double a, double b) {
    return a * b;
}

// Function to perform division
double divide(double a, double b) {
    return a / b;
}

// Function to check if entered arguments is number or not
bool isNumber(const std::string& str) {
    // Use stringstream to try to convert the string to a number
    std::istringstream iss(str);
    double value;
    iss >> value;

    // Check if the conversion was successful and if there are no remaining characters
    return !iss.fail() && iss.eof();
}

// Function that takes operation, operand1 and operand2 and returns result of calculation
double calculate(const std::string& operation, const double& operand1, const double& operand2){
    double result;
    
    if (operation == "add") {
        result = add(operand1, operand2);
    } else if (operation == "sub") {
        result = subtract(operand1, operand2);
    } else if (operation == "mul") {
        result = multiply(operand1, operand2);
    } else if (operation == "div") {
        result = divide(operand1, operand2);
    } 
    
    return result;
}
