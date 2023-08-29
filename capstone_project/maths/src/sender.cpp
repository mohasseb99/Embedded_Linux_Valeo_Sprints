#include "../../lib/MessageQueue.h"
#include <iostream>

int main() {
    try {
        // Sender
        MessageQueueSender sender("/my_message_queue");
        sender.SendMessage("Hello, ya 3m!");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with an error code
    }

    return 0;
}

