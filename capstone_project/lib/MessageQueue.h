#ifndef MESSAGE_QUEUE_CLASSES_H
#define MESSAGE_QUEUE_CLASSES_H

#include <mqueue.h>
#include <stdexcept>

class MessageQueueSender {
private:
    mqd_t mq;		// message queue descriptor 
public:
    MessageQueueSender(const char* queueName);
    void SendMessage(const char* message);
    ~MessageQueueSender() noexcept;
};

class MessageQueueReceiver {
private:
    mqd_t mq;		// message queue descriptor
    bool isBlocking;    // to store receiver message queue is blocking or not
    char* queueName;    // to store name of mq to unlink it after finishing
public:
    MessageQueueReceiver(char* queueName, bool isBlocking);
    void ReceiveMessageSync(char* received_message, size_t max_length, unsigned int* priority);
    ssize_t ReceiveMessageAsync(char* received_message, size_t max_length, unsigned int* priority);
    void cleanUpResources();
    ~MessageQueueReceiver() noexcept;
};

#endif

