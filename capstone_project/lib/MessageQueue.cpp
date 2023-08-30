#include "MessageQueue.h"
#include <cstring>
#include <cerrno>
#include <ctime>

MessageQueueSender::MessageQueueSender(const char* queueName) {
    mq = mq_open(queueName, O_WRONLY);    // here we only provide name of message queue as receiver should have created it before
    if (mq == (mqd_t)-1) {  
        int error_code = errno;
        throw std::runtime_error("mq_open failed with error code: " + std::to_string(error_code));   // throwing exception to catch it in application use message queue to log it to logger daemon as this library does not have access to logger
     }
}

void MessageQueueSender::SendMessage(const char* message) {
    if (mq_send(mq, message, strlen(message), 0) == -1) {
        int error_code = errno;
        throw std::runtime_error("mq_send failed with error code: " + std::to_string(error_code));
    }
}

MessageQueueSender::~MessageQueueSender() noexcept {
    mq_close(mq);
}

MessageQueueReceiver::MessageQueueReceiver(char* queueName, bool isBlocking) {
    this->isBlocking = isBlocking;
    this->queueName = queueName;
    struct mq_attr attr;
    attr.mq_flags =  0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;  // size of message
    attr.mq_curmsgs = 0;     // current messages in queue, when creating it equals zero

    mq = mq_open(queueName, O_CREAT | O_RDONLY, 0666, &attr);
    if (mq == (mqd_t)-1) {
        int error_code = errno;
        throw std::runtime_error("mq_open failed with error code: " + std::to_string(error_code));
    }
}

// used if you declared message queue as non-blocking
// returns result to check if result = 0 we know that we recieved message
ssize_t MessageQueueReceiver::ReceiveMessageAsync(char* received_message, size_t max_length, unsigned int* priority) {
    if(!isBlocking){
    	struct timespec timeout;
        // Set a timeout of 1 seconds
        timeout.tv_sec = 0;
        timeout.tv_nsec = 0;
	ssize_t result = mq_timedreceive(mq, received_message, max_length, priority, &timeout);
	if (result == -1 && errno != ETIMEDOUT) { // in non blocking mode if there is no message to recieve it returns -1 and errno is ETIMEDOUT so if errno is not equal ETIMEDOUT that means there is a problem in receiving
	    int error_code = errno;
	    throw std::runtime_error("mq_receive failed with error code: " + std::to_string(error_code));
	}
	return result; 
     }
     else{
     	throw std::runtime_error("incorrect function, you should use Sync function as you declared message queue is blocking");
     }
}

// used if you declared message queue as blocking
void MessageQueueReceiver::ReceiveMessageSync(char* received_message, size_t max_length, unsigned int* priority) {
    if(isBlocking){
	ssize_t result = mq_receive(mq, received_message, max_length, priority);
	if (result == -1) {
	    int error_code = errno;
	    throw std::runtime_error("mq_receive failed with error code: " + std::to_string(error_code));
	}
     }
     else{
     	throw std::runtime_error("incorrect function, you should use Async function as you declared message queue is non blocking");
     }
}

// used as we use while(1) so when we press ctrl+c resources will not be cleaned up
void MessageQueueReceiver::cleanUpResources(){
    mq_close(mq);
    mq_unlink(this->queueName);
}

MessageQueueReceiver::~MessageQueueReceiver() noexcept {
    mq_close(mq);
    mq_unlink(this->queueName);
}
