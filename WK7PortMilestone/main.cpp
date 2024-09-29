#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Mutex for synchronized console output
std::mutex coutMutex;

// Function for counting up
void countUp(int limit) {
    for (int i = 1; i <= limit; ++i) {
        {
            std::lock_guard<std::mutex> guard(coutMutex);
            std::cout << "Counting Up: " << i << std::endl;
        }
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Function for counting down
void countDown(int start) {
    for (int i = start; i >= 0; --i) {
        {
            std::lock_guard<std::mutex> guard(coutMutex);
            std::cout << "Counting Down: " << i << std::endl;
        }
        // Simulate processing time
       std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Create and start the counting up thread
    std::thread threadUp(countUp, 20);

    // Wait for the counting up thread to finish
    threadUp.join();

    // Create and start the counting down thread
    std::thread threadDown(countDown, 20);

    // Wait for the counting down thread to finish
    threadDown.join();

    {
        std::lock_guard<std::mutex> guard(coutMutex);
        std::cout << "Both counting operations have completed." << std::endl;
    }

    return 0;
}