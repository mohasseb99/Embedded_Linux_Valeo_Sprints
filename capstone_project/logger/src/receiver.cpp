#include "../../lib/MessageQueue.h"
#include <iostream>

int main() {
    try {
        // Receiver creates the message queue
        MessageQueueReceiver receiver("/my_message_queue", 1);

        char received_message[1024];
        unsigned int priority;
        receiver.ReceiveMessageSync(received_message, sizeof(received_message), &priority);
	std::cout << "Received message: " << received_message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with an error code
    }

    return 0;
}

